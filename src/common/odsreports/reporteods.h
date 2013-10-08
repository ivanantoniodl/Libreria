#ifndef REPORTEODS_H
#define REPORTEODS_H

#include <QObject>
#include <QDomDocument>
#include <QStringList>
#include <QString>
#include <QProcess>
#include <QHash>

class reporteODS : public QObject
{
    Q_OBJECT
public:
    explicit reporteODS(QObject *parent = 0);
    void setTemplatePath(QString TemplateDir);
    bool getODSInformation();
    bool setHeaders(QStringList headers);
    void toString(int position);
    void toDate(int position);
    void toFloat(int position);
    void toCurrency(int position);
    bool appendRowValue(QStringList values);
    bool save(QString filename);

private:
    // ods data types
    enum dataType {
        odsString,
        odsFloat,
        odsDate,
        odsCurrency
    };
    QString templatePath;
    QDomDocument documentODS;
    QProcess process;
    QString fileName;
    QHash<int, int> positionDataType;

    void openDocument();

signals:

public slots:
    void updateOutputTextEdit();
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void processError(QProcess::ProcessError error);
};

#endif // REPORTEODS_H
