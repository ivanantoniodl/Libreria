#ifndef GRUPOPERMISORECORD_H
#define GRUPOPERMISORECORD_H

#include "om/grupopermisorecordbase.h"
    
/*!
  Record de la tabla GrupoPermiso.

  Esta clase puede ser editada por el usuario y así personalizarla.
  
  Para mayor información ver RecordBase.
*/

class QANTMVSHARED_EXPORT GrupoPermisoRecord :  public GrupoPermisoRecordBase
{
Q_OBJECT

private:

public:
	GrupoPermisoRecord(QObject *qparent=NULL,
				  RecordBase *rparent=NULL);
	GrupoPermisoRecord(const GrupoPermisoRecord &other);
	~GrupoPermisoRecord();
};

Q_DECLARE_METATYPE(GrupoPermisoRecord*);

#endif // GRUPOPERMISORECORD_H
