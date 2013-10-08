#ifndef REPORTESPLUGINSCOLLECTIONS_H
#define REPORTESPLUGINSCOLLECTIONS_H

#include "plugincollection.h"
#include "reportes_global.h"

class REPORTESSHARED_EXPORT ReportesPluginsCollections: public QObject, public PluginCollection
{
	Q_OBJECT
	Q_INTERFACES(PluginCollection)
public:
    ReportesPluginsCollections();
};

#endif // REPORTESPLUGINSCOLLECTIONS_H
