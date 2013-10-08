#ifndef LIBRORECORD_H
#define LIBRORECORD_H

#include "om/librorecordbase.h"
    
/*!
  Record de la tabla Libro.

  Esta clase puede ser editada por el usuario y así personalizarla.
  
  Para mayor información ver RecordBase.
*/

class QANTMVSHARED_EXPORT LibroRecord :  public LibroRecordBase
{
Q_OBJECT

private:

public:
	LibroRecord(QObject *qparent=NULL,
				  RecordBase *rparent=NULL);
	LibroRecord(const LibroRecord &other);
	~LibroRecord();
};

Q_DECLARE_METATYPE(LibroRecord*);

#endif // LIBRORECORD_H
