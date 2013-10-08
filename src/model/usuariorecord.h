#ifndef USUARIORECORD_H
#define USUARIORECORD_H

#include "om/usuariorecordbase.h"
    
/*!
  Record de la tabla Usuario.

  Esta clase puede ser editada por el usuario y así personalizarla.
  
  Para mayor información ver RecordBase.
*/

class QANTMVSHARED_EXPORT UsuarioRecord :  public UsuarioRecordBase
{
Q_OBJECT

private:

public:
	UsuarioRecord(QObject *qparent=NULL,
				  RecordBase *rparent=NULL);
	UsuarioRecord(const UsuarioRecord &other);
	~UsuarioRecord();
};

Q_DECLARE_METATYPE(UsuarioRecord*);

#endif // USUARIORECORD_H
