#include <QtGui>
#include "reportespluginscollections.h"

#include "fejemplodialog.h"
#include "fejemplosindialog.h"
#include "freporteexistencias.h"

ReportesPluginsCollections::ReportesPluginsCollections()
{
	addPlugin( new FEjemploDialog );
	addPlugin( new FEjemploSinDialog );
	addPlugin(new freporteexistencias);
}

Q_EXPORT_PLUGIN2(reportes, ReportesPluginsCollections)
