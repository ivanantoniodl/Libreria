#include <QtGui>
#include "configusuarios.h"

ConfigUsers::ConfigUsers()
{
	addPage( new FUsersAdminPage );
	addPage( new FRolAdminPage );
    addPage( new FUsuarioCargosPage );
}

QIcon ConfigUsers::icon()
{
    return QIcon(":/pics/usuarios.png");
}

Q_EXPORT_PLUGIN2(ConfigUsers, ConfigUsers)
