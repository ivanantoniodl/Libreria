#ifndef LIBROS_H
#define LIBROS_H

#include "principalformplugin.h"
#include "libros_global.h"
#include "flibros.h"

class LIBROSSHARED_EXPORT libros: public QObject, public PrincipalFormPlugin
{
    Q_OBJECT
	Q_INTERFACES(PrincipalFormPlugin)
public:
    libros();
    QString name();
    QString description();
    QStringList dependencies();
    QWidget *widget();
    QString menuGroup();
    QString menuName();
};

#endif // LIBROS_H
