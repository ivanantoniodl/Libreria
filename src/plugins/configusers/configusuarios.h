#ifndef CONFIGUSUARIOS_H
#define CONFIGUSUARIOS_H

#include <QObject>
#include "configplugin.h"

#include "fusersadminpage.h"
#include "froladminpage.h"
#include "fusuariocargospage.h"
#include "configusers_global.h"

class CONFIGUSERSSHARED_EXPORT ConfigUsers : public QObject, public ConfigPlugin
{
	Q_OBJECT
	Q_INTERFACES(ConfigPlugin)

public:
	ConfigUsers();
	QString name() { return "Configuracion de usuarios"; }
	QStringList dependencies() { return QStringList(); }
	QString description() {	 return "Configura los usuarios"; }

	QString shortTitle() { return "Usuarios"; }
	QIcon icon();
};

#endif // CONFIGLUGAR_H
