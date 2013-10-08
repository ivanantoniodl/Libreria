#ifndef PERMISORECORD_H
#define PERMISORECORD_H

#include "om/permisorecordbase.h"
    
/*!
  Record de la tabla Permiso.

  Esta clase puede ser editada por el usuario y así personalizarla.
  
  Para mayor información ver RecordBase.
*/

class QANTMVSHARED_EXPORT PermisoRecord :  public PermisoRecordBase
{
Q_OBJECT

private:

public:
	PermisoRecord(QObject *qparent=NULL,
				  RecordBase *rparent=NULL);
	PermisoRecord(const PermisoRecord &other);
	~PermisoRecord();
};

Q_DECLARE_METATYPE(PermisoRecord*);

#endif // PERMISORECORD_H
