#ifndef LIBROAUTORRECORD_H
#define LIBROAUTORRECORD_H

#include "om/libroautorrecordbase.h"
    
/*!
  Record de la tabla LibroAutor.

  Esta clase puede ser editada por el usuario y así personalizarla.
  
  Para mayor información ver RecordBase.
*/

class QANTMVSHARED_EXPORT LibroAutorRecord :  public LibroAutorRecordBase
{
Q_OBJECT

private:

public:
	LibroAutorRecord(QObject *qparent=NULL,
				  RecordBase *rparent=NULL);
	LibroAutorRecord(const LibroAutorRecord &other);
	~LibroAutorRecord();
};

Q_DECLARE_METATYPE(LibroAutorRecord*);

#endif // LIBROAUTORRECORD_H
