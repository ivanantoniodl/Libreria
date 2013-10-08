#ifndef LUGARTIPORECORD_H
#define LUGARTIPORECORD_H

#include "om/lugartiporecordbase.h"
    
/*!
  Record de la tabla LugarTipo.

  Esta clase puede ser editada por el usuario y así personalizarla.
  
  Para mayor información ver RecordBase.
*/

class QANTMVSHARED_EXPORT LugarTipoRecord :  public LugarTipoRecordBase
{
Q_OBJECT

private:

public:
	LugarTipoRecord(QObject *qparent=NULL,
				  RecordBase *rparent=NULL);
	LugarTipoRecord(const LugarTipoRecord &other);
	~LugarTipoRecord();
};

Q_DECLARE_METATYPE(LugarTipoRecord*);

#endif // LUGARTIPORECORD_H
