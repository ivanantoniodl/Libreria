#ifndef LIBROAUTORMODEL_H
#define LIBROAUTORMODEL_H

#include "om/libroautormodelbase.h"
#include "libroautorrecord.h"

/*!
  Modelo de la tabla LibroAutor.

  Esta clase puede ser editada por el usuario y así personalizarla.

  Para mayor información ver ModelBase.
*/

class QANTMVSHARED_EXPORT LibroAutorModel : public LibroAutorModelBase
{
Q_OBJECT
public:
	//! Representa que configuración de consulta se esta utilizando. Para mas configuraciones agregarlas aqui.
	enum ConsConfEnum
	{
		Default//,CustomEnum
	};
	LibroAutorModel(QObject *parent=NULL,
				 ConsConfEnum conf=Default);
	~LibroAutorModel();

	QVariant headerData(int section, Qt::Orientation orientation,
							int role) const;

protected:
	QVariant getRecordValue(RecordBase*,int column=-1) const;
	void configureInternalSelectQuery();
};

#endif // LIBROAUTORMODEL_H
