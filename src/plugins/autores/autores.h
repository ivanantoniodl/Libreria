#ifndef AUTORES_H
#define AUTORES_H

#include "principalformplugin.h"
#include "autores_global.h"
#include "fautores.h"

class AUTORESSHARED_EXPORT autores: public QObject, public PrincipalFormPlugin
{
    Q_OBJECT
	Q_INTERFACES(PrincipalFormPlugin)
public:
    autores();
    QString name();
    QString description();
    QStringList dependencies();
    QWidget *widget();
    QString menuGroup();
    QString menuName();
};

#endif // AUTORES_H
