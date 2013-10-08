#ifndef MAQUINARECORD_H
#define MAQUINARECORD_H

#include "om/maquinarecordbase.h"
    
/*!
  Record de la tabla Maquina.

  Esta clase puede ser editada por el usuario y así personalizarla.
  
  Para mayor información ver RecordBase.
*/

class QANTMVSHARED_EXPORT MaquinaRecord :  public MaquinaRecordBase
{
Q_OBJECT

private:

public:
	MaquinaRecord(QObject *qparent=NULL,
				  RecordBase *rparent=NULL);
	MaquinaRecord(const MaquinaRecord &other);
	~MaquinaRecord();
};

Q_DECLARE_METATYPE(MaquinaRecord*);

#endif // MAQUINARECORD_H
