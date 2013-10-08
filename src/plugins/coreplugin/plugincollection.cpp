#include "plugincollection.h"

PluginCollection::PluginCollection()
{
}

PluginCollection::~PluginCollection()
{}

void PluginCollection::addPlugin( IPlugin* plugin)
{
	lstPlugins.append(plugin);
}
