#ifndef PERMISOS_H
#define PERMISOS_H

#include <QString>
#include <QtGui/QWidget>
#include "rolpermisomodel.h"
#include "usuariomodel.h"
#include "grupopermisomodel.h"
#include "permisomodel.h"
#include "common_global.h"

class COMMONSHARED_EXPORT perm
{
public:
    perm(int permiso);
    bool permisoW;
    bool permisoR;
    bool valido;
};

class COMMONSHARED_EXPORT Permisos
{
public:
    Permisos();
    static perm validar(QWidget *formulario, QString etiqueta, QString grupo);
    static perm validar(QWidget *formulario, QString nombreAccion, QString etiqueta, QString grupo);
private:
    static perm validar(QString nombreFormulario, QString etiqueta, QString grupo);
};

#endif // PERMISOS_H
