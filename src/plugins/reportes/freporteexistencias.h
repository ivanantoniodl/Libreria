#ifndef FREPORTEEXISTENCIAS_H
#define FREPORTEEXISTENCIAS_H

#include <QDialog>
#include <QMessageBox>
#include "reportplugin.h"
#include "reports/genorpt.h"
#include "reportes_global.h"

namespace Ui {
    class freporteexistencias;
}

class REPORTESSHARED_EXPORT freporteexistencias : public QDialog, public ReportPlugin
{
    Q_OBJECT

public:
    explicit freporteexistencias(QWidget *parent = 0);
    ~freporteexistencias();
	QString name()      { return "Reporte De Existencias"; }
	QString description() { return tr("Lista Los Productos Con Una Existencia Limite"); }
	QStringList dependencies() { return QStringList(); }
	void openReport();


private slots:
	void on_btnVerReporte_clicked();

private:
    Ui::freporteexistencias *ui;
	genORPT *generador;
};

#endif // FREPORTEEXISTENCIAS_H
