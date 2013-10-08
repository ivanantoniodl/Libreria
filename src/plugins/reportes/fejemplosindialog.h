#ifndef FEJEMPLOSINDIALOG_H
#define FEJEMPLOSINDIALOG_H

#include <QMessageBox>

#include "reportplugin.h"

#include "reports/genorpt.h"
#include "reportes_global.h"

class REPORTESSHARED_EXPORT FEjemploSinDialog: public QDialog, public ReportPlugin
{
	Q_OBJECT
public:
	FEjemploSinDialog();

	QString name()      { return "Reporte2"; }
	QString description() { return tr("Ejemplo de reporte sin dialog"); }
	QStringList dependencies() { return QStringList(); }
	void openReport();
};

#endif // FEJEMPLOSINDIALOG_H
