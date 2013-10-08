#include <QtGui>
#include "configlugar.h"

ConfigLugar::ConfigLugar()
{
	addPage( new ConfigLugarPage );
	addPage( new FMaquinasPage );
	addPage( new FLugaresConfigPage );
	addPage( new FLugarTipoPage );
}

QIcon ConfigLugar::icon()
{
    return QIcon(":/pics/place.png");
}

Q_EXPORT_PLUGIN2(ConfigLugar, ConfigLugar)
