#ifndef LIBROS_H
#define LIBROS_H

#include "principalformplugin.h"
#include "principalbanco.h"
#include "libros_global.h"


class LIBROSSHARED_EXPORT banco: public QObject, public PrincipalFormPlugin
{
    Q_OBJECT
	Q_INTERFACES(PrincipalFormPlugin)
public:
    banco();
    QString name();
    QString description();
    QStringList dependencies();
    QWidget *widget();
    QString menuGroup();
    QString menuName();
};

#endif // LIBROS_H
