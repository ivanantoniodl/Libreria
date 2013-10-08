#ifndef VALIDADOR_H
#define VALIDADOR_H

#include "common_global.h"

class QRegExp;
class QRegExpValidator;
class QValidator;

class COMMONSHARED_EXPORT TValidator
{
private:
	static QValidator *vcodigo;
	static QValidator *vdireccion;
	static QValidator *vtelefono;
	static QValidator *vmail;
	static QValidator *vnit;
	static QValidator *vnombre;
	static QValidator *vplaca;
public:
	static QValidator* codigo();
    static QValidator* direccion();
    static QValidator* telefono();
    static QValidator* mail();
    static QValidator* nit();
    static QValidator* nombre();
    static QValidator* placa();
};

#endif // VALIDADOR_H
