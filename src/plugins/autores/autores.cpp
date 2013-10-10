#include <QtGui>
#include "autores.h"



autores::autores():
    PrincipalFormPlugin(PrincipalFormPlugin::TypeWidget)
{
}


QString autores::name()
{
    return tr("autores");
}


QString autores::description()
{
    return tr("Catálogo de autores");
}


QStringList autores::dependencies()
{
    return QStringList();
}


QWidget *autores::widget()
{
    return new fautores();
}


QString autores::menuGroup()
{
    return tr("Administración");
}


QString autores::menuName()
{
    return tr("autores");
}



Q_EXPORT_PLUGIN2(autores, autores)
