#ifndef AUTORRECORD_H
#define AUTORRECORD_H

#include "om/autorrecordbase.h"
    
/*!
  Record de la tabla Autor.

  Esta clase puede ser editada por el usuario y así personalizarla.
  
  Para mayor información ver RecordBase.
*/

class QANTMVSHARED_EXPORT AutorRecord :  public AutorRecordBase
{
Q_OBJECT

private:

public:
	AutorRecord(QObject *qparent=NULL,
				  RecordBase *rparent=NULL);
	AutorRecord(const AutorRecord &other);
	~AutorRecord();
};

Q_DECLARE_METATYPE(AutorRecord*);

#endif // AUTORRECORD_H
