#ifndef LUGARRECORD_H
#define LUGARRECORD_H

#include "om/lugarrecordbase.h"
    
/*!
  Record de la tabla Lugar.

  Esta clase puede ser editada por el usuario y así personalizarla.
  
  Para mayor información ver RecordBase.
*/

class QANTMVSHARED_EXPORT LugarRecord :  public LugarRecordBase
{
Q_OBJECT

private:

public:
	LugarRecord(QObject *qparent=NULL,
				  RecordBase *rparent=NULL);
	LugarRecord(const LugarRecord &other);
	~LugarRecord();
};

Q_DECLARE_METATYPE(LugarRecord*);

#endif // LUGARRECORD_H
