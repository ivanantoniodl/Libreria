#ifndef EMPRESARECORD_H
#define EMPRESARECORD_H

#include "om/empresarecordbase.h"
    
/*!
  Record de la tabla Empresa.

  Esta clase puede ser editada por el usuario y así personalizarla.
  
  Para mayor información ver RecordBase.
*/

class QANTMVSHARED_EXPORT EmpresaRecord :  public EmpresaRecordBase
{
Q_OBJECT

private:

public:
	EmpresaRecord(QObject *qparent=NULL,
				  RecordBase *rparent=NULL);
	EmpresaRecord(const EmpresaRecord &other);
	~EmpresaRecord();
};

Q_DECLARE_METATYPE(EmpresaRecord*);

#endif // EMPRESARECORD_H
