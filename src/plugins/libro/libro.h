#ifndef LIBRO_H
#define LIBRO_H

#include "principalformplugin.h"
#include "fprincipallibro.h"
#include "libro_global.h"


class LIBROSHARED_EXPORT libro: public QObject, public PrincipalFormPlugin
{
    Q_OBJECT
	Q_INTERFACES(PrincipalFormPlugin)
public:
    libro();
    QString name();
    QString description();
    QStringList dependencies();
    QWidget *widget();
    QString menuGroup();
    QString menuName();
};

#endif // LIBRO_H
