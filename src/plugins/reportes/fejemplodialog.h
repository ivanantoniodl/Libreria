#ifndef FEJEMPLODIALOG_H
#define FEJEMPLODIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "reportplugin.h"
#include "reports/genorpt.h"

#include "reportes_global.h"

#include "odsreports/configodsreport.h"


namespace Ui {
    class FEjemploDialog;
}

class REPORTESSHARED_EXPORT FEjemploDialog : public QDialog, public ReportPlugin
{
    Q_OBJECT

public:
    explicit FEjemploDialog(QWidget *parent = 0);
    ~FEjemploDialog();

	QString name()      { return "Reporte1"; }
	QString description() { return tr("Ejemplo de reporte con dialog"); }
	QStringList dependencies() { return QStringList(); }
	void openReport();

private slots:
	void on_pushButton_clicked();

    void on_btnODS_clicked();

private:
    Ui::FEjemploDialog *ui;
	genORPT *generador;
};

#endif // FEJEMPLODIALOG_H
