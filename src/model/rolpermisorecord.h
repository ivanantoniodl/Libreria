#ifndef ROLPERMISORECORD_H
#define ROLPERMISORECORD_H

#include "om/rolpermisorecordbase.h"
    
/*!
  Record de la tabla RolPermiso.

  Esta clase puede ser editada por el usuario y así personalizarla.
  
  Para mayor información ver RecordBase.
*/

class QANTMVSHARED_EXPORT RolPermisoRecord :  public RolPermisoRecordBase
{
Q_OBJECT

private:

public:
	RolPermisoRecord(QObject *qparent=NULL,
				  RecordBase *rparent=NULL);
	RolPermisoRecord(const RolPermisoRecord &other);
	~RolPermisoRecord();
};

Q_DECLARE_METATYPE(RolPermisoRecord*);

#endif // ROLPERMISORECORD_H
