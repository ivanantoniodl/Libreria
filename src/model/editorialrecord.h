#ifndef EDITORIALRECORD_H
#define EDITORIALRECORD_H

#include "om/editorialrecordbase.h"
    
/*!
  Record de la tabla Editorial.

  Esta clase puede ser editada por el usuario y así personalizarla.
  
  Para mayor información ver RecordBase.
*/

class QANTMVSHARED_EXPORT EditorialRecord :  public EditorialRecordBase
{
Q_OBJECT

private:

public:
	EditorialRecord(QObject *qparent=NULL,
				  RecordBase *rparent=NULL);
	EditorialRecord(const EditorialRecord &other);
	~EditorialRecord();
};

Q_DECLARE_METATYPE(EditorialRecord*);

#endif // EDITORIALRECORD_H
