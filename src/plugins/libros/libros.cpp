#include <QtGui>
#include "libros.h"



libros::libros():
    PrincipalFormPlugin(PrincipalFormPlugin::TypeWidget)
{
}


QString libros::name()
{
    return tr("Libros");
}


QString libros::description()
{
    return tr("Catálogo de libros");
}


QStringList libros::dependencies()
{
    return QStringList();
}


QWidget *libros::widget()
{
    return new flibros();
}


QString libros::menuGroup()
{
    return tr("Administración");
}


QString libros::menuName()
{
    return tr("Libros");
}



Q_EXPORT_PLUGIN2(libros, libros)
