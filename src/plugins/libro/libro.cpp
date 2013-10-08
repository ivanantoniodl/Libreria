#include <QtGui>
#include "libro.h"


libro::libro():
    PrincipalFormPlugin(PrincipalFormPlugin::TypeWidget)
{
}


QString libro::name()
{
    return tr("Libro");
}


QString libro::description()
{
    return tr("Catálogo de libros");
}


QStringList libro::dependencies()
{
    return QStringList();
}


QWidget *libro::widget()
{
    return new fprincipallibro();
}


QString libro::menuGroup()
{
    return tr("Administración");
}


QString libro::menuName()
{
    return tr("Libros");
}



Q_EXPORT_PLUGIN2(libro, libro)
