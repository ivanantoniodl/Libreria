#ifndef CONFIGLUGAR_H
#define CONFIGLUGAR_H

#include <QObject>
#include "configplugin.h"
#include "lugarmodel.h"
#include "maquinamodel.h"

#include "configlugarpage.h"
#include "flugaresconfigpage.h"
#include "flugartipopage.h"
#include "fmaquinaspage.h"
#include "configlugar_global.h"

class CONFIGLUGARSHARED_EXPORT ConfigLugar : public QObject, public ConfigPlugin
{
	Q_OBJECT
	Q_INTERFACES(ConfigPlugin)

public:
	ConfigLugar();
	QString name() { return "ConfigurarLugar"; }
	QStringList dependencies() { return QStringList(); }
	QString description() {	 return "Configura el lugar en la maquina actual"; }

	QString shortTitle() { return "Lugar"; }
	QIcon icon();
};

#endif // CONFIGLUGAR_H
