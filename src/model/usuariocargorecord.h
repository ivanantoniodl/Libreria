#ifndef USUARIOCARGORECORD_H
#define USUARIOCARGORECORD_H

#include "om/usuariocargorecordbase.h"
    
/*!
  Record de la tabla UsuarioCargo.

  Esta clase puede ser editada por el usuario y así personalizarla.
  
  Para mayor información ver RecordBase.
*/

class QANTMVSHARED_EXPORT UsuarioCargoRecord :  public UsuarioCargoRecordBase
{
Q_OBJECT

private:

public:
	UsuarioCargoRecord(QObject *qparent=NULL,
				  RecordBase *rparent=NULL);
	UsuarioCargoRecord(const UsuarioCargoRecord &other);
	~UsuarioCargoRecord();
};

Q_DECLARE_METATYPE(UsuarioCargoRecord*);

#endif // USUARIOCARGORECORD_H
