#include "configodsreport.h"

#include <QApplication>
#include <QDialog>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QRegExp>

configOdsReport::configOdsReport(QObject *parent) :
    QObject(parent)
{
    reporte = new reporteODS(this);
    reporte->setTemplatePath( QApplication::applicationDirPath()+"/reportes/odstemplate" );
    reporte->getODSInformation();
}

bool configOdsReport::agregarCabecera(QStringList cabeceras)
{
    return reporte->setHeaders(cabeceras);
}

bool configOdsReport::agregarFila(QStringList fila)
{
    return reporte->appendRowValue(fila);
}

bool configOdsReport::exportar()
{
    QString initialName = QDir::homePath();
    QString fileName = QFileDialog::getSaveFileName((QWidget *)this->parent(), "Elija un nombre",
                                         initialName,"Hojas de Calculo (*.ods)");
    fileName = QDir::toNativeSeparators(fileName);
    if (fileName.isEmpty())
        return false;
    QRegExp rx("*.ods");
    rx.setPatternSyntax(QRegExp::Wildcard);
    if (!rx.exactMatch(fileName))
        fileName.append(".ods");
    if (QFile::exists(fileName))
    {
        if (!QFile::remove(fileName))
        {
           QMessageBox::critical((QWidget *)this->parent(),"Error","El archivo no se puede eliminar, revise los permisos del archivo");
           return false;
        }
        if (!reporte->save(fileName))
            return false;
    }
    else
        if (!reporte->save(fileName))
            return false;
    return true;
}

void configOdsReport::forzarFilaACadena(int fila)
{
    reporte->toString(fila);
}

void configOdsReport::forzarFilaAFecha(int fila)
{
    reporte->toDate(fila);
}

void configOdsReport::forzarFilaAMoneda(int fila)
{
    reporte->toCurrency(fila);
}
void configOdsReport::forzarFilaANumero(int fila)
{
    reporte->toFloat(fila);
}
