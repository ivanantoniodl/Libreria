#ifndef EDITORIALLIBRORECORD_H
#define EDITORIALLIBRORECORD_H

#include "om/editoriallibrorecordbase.h"
    
/*!
  Record de la tabla EditorialLibro.

  Esta clase puede ser editada por el usuario y así personalizarla.
  
  Para mayor información ver RecordBase.
*/

class QANTMVSHARED_EXPORT EditorialLibroRecord :  public EditorialLibroRecordBase
{
Q_OBJECT

private:

public:
	EditorialLibroRecord(QObject *qparent=NULL,
				  RecordBase *rparent=NULL);
	EditorialLibroRecord(const EditorialLibroRecord &other);
	~EditorialLibroRecord();
};

Q_DECLARE_METATYPE(EditorialLibroRecord*);

#endif // EDITORIALLIBRORECORD_H
