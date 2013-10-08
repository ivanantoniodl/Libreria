#ifndef PLUGINCOLLECTION_H
#define PLUGINCOLLECTION_H

#include <QtCore>
#include "iplugin.h"
#include "core_global.h"

class MainWindow;

class CORESHARED_EXPORT PluginCollection
{
friend class MainWindow;
private:
	QList<IPlugin*> lstPlugins;
public:
    PluginCollection();
    virtual ~PluginCollection();

	void addPlugin( IPlugin* );
};

Q_DECLARE_INTERFACE(PluginCollection,"PluginCollection")

#endif // PLUGINCOLLECTION_H
