#include "reporteods.h"

#include <QDebug>
#include <QFile>
#include <QDir>
#include <QDesktopServices>
#include <QUrl>

reporteODS::reporteODS(QObject *parent) :
    QObject(parent)
{
    connect(&process, SIGNAL(readyReadStandardError()),
            this, SLOT(updateOutputTextEdit()));
    connect(&process, SIGNAL(finished(int, QProcess::ExitStatus)),
            this, SLOT(processFinished(int, QProcess::ExitStatus)));
    connect(&process, SIGNAL(error(QProcess::ProcessError)),
            this, SLOT(processError(QProcess::ProcessError)));
    positionDataType.clear();
}

void reporteODS::setTemplatePath(QString TemplateDir)
{
    templatePath = TemplateDir;
    //qDebug()<<templatePath;
}

bool reporteODS::getODSInformation()
{
    QFile file(templatePath+"/content_TEMPLATE.xml");
   // qDebug()<<templatePath+"/content.xml";
    if (!file.open(QIODevice::ReadOnly))
        return false;
    if (!documentODS.setContent(&file))
    {
        file.close();
        return false;
    }
    file.close();
    if (documentODS.isNull())
    {
        return false;
//        qDebug()<<"es nulo";
    }
    return true;
}

bool reporteODS::setHeaders(QStringList headers)
{
    int i;
    QDomElement table= documentODS.documentElement().firstChildElement("office:body")
                        .firstChildElement("office:spreadsheet").firstChildElement("table:table");
    if (table.isNull())
        return false;
    QDomElement tableColumnInfo = table.firstChildElement("table:table-column");
    int numColumns=tableColumnInfo.attribute("table:number-columns-repeated","0").toInt();
    if (numColumns < headers.count())
        tableColumnInfo.setAttribute("table:number-columns-repeated",QString::number(headers.count()));
    //row creation
    QDomElement tableRow=documentODS.createElement("table:table-row");
    tableRow.setAttribute("table:style-name","ro1");
    //cell creation
    for (i = 0; i < headers.count(); i++)
    {
        QDomElement tableCell=documentODS.createElement("table:table-cell");
        tableCell.setAttribute("office:value-type","string");
        QDomElement textNode=documentODS.createElement("text:p");
        QDomText textHeader=documentODS.createTextNode(headers.at(i));
        textNode.appendChild(textHeader);
        tableCell.appendChild(textNode);
        tableRow.appendChild(tableCell);
    }
    table.appendChild(tableRow);
    return true;
}

/**
@param position
    ingresar el numero de columna que se desea se fuerce a ser una cadena de texto, antes de ejecutar
    appendRowValue, de lo contrario no aplicará los valores
*/
void reporteODS::toString(int position)
{
    positionDataType[position]=odsString;
}

void reporteODS::toDate(int position)
{
    positionDataType[position]=odsDate;
}

void reporteODS::toFloat(int position)
{
    positionDataType[position]=odsFloat;
}

void reporteODS::toCurrency(int position)
{
    positionDataType[position]=odsCurrency;
}

bool reporteODS::appendRowValue(QStringList values)
{
    int i;
    QDomElement table= documentODS.documentElement().firstChildElement("office:body")
                        .firstChildElement("office:spreadsheet").firstChildElement("table:table");
    if (table.isNull())
        return false;

    //row creation
    QDomElement tableRow=documentODS.createElement("table:table-row");
    tableRow.setAttribute("table:style-name","ro1");
    //cell creation
    for (i = 0; i < values.count(); i++)
    {
        int type=odsString;
        bool isNumber=true;
        float value=0;
        if (positionDataType.contains(i))
        {
            type=positionDataType[i];
            if (positionDataType[i]==odsFloat || positionDataType[i]==odsCurrency)
            {
                value=values.at(i).toFloat(&isNumber);
                if (! isNumber)
                    type=odsString;
            }
//            switch (positionDataType[i])
//            {
//            case odsString:
//                type = odsString;
//                break;
//            }
//            if (positionDataType[i]==odsString)
//                isNumber=false;
//            else
//                value=values.at(i).toFloat(&isNumber);
        }
        QDomElement tableCell=documentODS.createElement("table:table-cell");
        switch (type)
        {
        case odsString:
            tableCell.setAttribute("office:value-type","string");
            break;
        case odsFloat:
            tableCell.setAttribute("office:value-type","float");
            tableCell.setAttribute("office:value",value);
            break;
        case odsDate:
            tableCell.setAttribute("office:value-type","date");
            tableCell.setAttribute("office:date-value",values.at(i));
            break;
        case odsCurrency:
            tableCell.setAttribute("office:value-type","currency");
            tableCell.setAttribute("office:currency","GTQ");
            tableCell.setAttribute("office:value",value);
            break;
        }
//        if (isNumber)
//        {
//            tableCell.setAttribute("office:value-type","float");
//            tableCell.setAttribute("office:value",value);
//        }
//        else
//            tableCell.setAttribute("office:value-type","string");
        QDomElement textNode=documentODS.createElement("text:p");
        QDomText textHeader;
        if (type==odsCurrency)
        {
            QLocale::setDefault(QLocale(QLocale::Spanish, QLocale::Guatemala));
            QString currencyString = QString("%L1").arg(value,0,'f',2);
            textHeader=documentODS.createTextNode("Q"+currencyString);
        }
        else
            textHeader=documentODS.createTextNode(values.at(i));
        textNode.appendChild(textHeader);
        tableCell.appendChild(textNode);
        tableRow.appendChild(tableCell);
    }
    table.appendChild(tableRow);
    return true;
}

bool reporteODS::save(QString filename)
{
    QFile file(templatePath+"/content.xml");
    // qDebug()<<templatePath+"/content.xml";
    if (!file.open(QIODevice::WriteOnly))
        return false;
    if (!file.flush())
        return false;
    QTextStream ts(&file);
    documentODS.save(ts,3);
    file.close();
    QDir::setCurrent(templatePath);
    QStringList args;
    args<<"-r"<<filename<<"Configurations2/"<<"META-INF/"
            <<"Thumbnails/"<<"content.xml"
            <<"meta.xml"<<"mimetype"<<"settings.xml"
            <<"styles.xml";
    process.start("zip",args);
    positionDataType.clear();
    return true;
}

void reporteODS::updateOutputTextEdit()
{
    QByteArray newData = process.readAllStandardError();
    QString text = QString::fromLocal8Bit(newData);
    qDebug()<<text;
}

void reporteODS::processFinished(int exitCode,
                                    QProcess::ExitStatus exitStatus)
{
    if (exitStatus == QProcess::CrashExit) {
        qDebug()<<"Zip program crashed";
    } else if (exitCode != 0) {
        qDebug()<<"Conversion failed";
    } else {
        qDebug()<<"File created";
        QDesktopServices::openUrl(QUrl(fileName));
    }
}

void reporteODS::processError(QProcess::ProcessError error)
{
    if (error == QProcess::FailedToStart) {
        qDebug()<<"Conversion program not found";
    }
}
