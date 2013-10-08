#ifndef ROLRECORD_H
#define ROLRECORD_H

#include "om/rolrecordbase.h"
    
/*!
  Record de la tabla Rol.

  Esta clase puede ser editada por el usuario y así personalizarla.
  
  Para mayor información ver RecordBase.
*/

class QANTMVSHARED_EXPORT RolRecord :  public RolRecordBase
{
Q_OBJECT

private:

public:
	RolRecord(QObject *qparent=NULL,
				  RecordBase *rparent=NULL);
	RolRecord(const RolRecord &other);
	~RolRecord();
};

Q_DECLARE_METATYPE(RolRecord*);

#endif // ROLRECORD_H
