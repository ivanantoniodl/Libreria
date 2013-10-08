#include "configplugin.h"

ConfigPlugin::ConfigPlugin()
{}

ConfigPlugin::~ConfigPlugin()
{}

void ConfigPlugin::addPage(ConfigPage *page)
{
	 lstPages.append(page);
}


