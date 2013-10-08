#ifndef LIBROMODEL_H
#define LIBROMODEL_H

#include "om/libromodelbase.h"
#include "librorecord.h"

/*!
  Modelo de la tabla Libro.

  Esta clase puede ser editada por el usuario y así personalizarla.

  Para mayor información ver ModelBase.
*/

class QANTMVSHARED_EXPORT LibroModel : public LibroModelBase
{
Q_OBJECT
public:
	//! Representa que configuración de consulta se esta utilizando. Para mas configuraciones agregarlas aqui.
	enum ConsConfEnum
	{
		Default//,CustomEnum
	};
	LibroModel(QObject *parent=NULL,
				 ConsConfEnum conf=Default);
	~LibroModel();

	QVariant headerData(int section, Qt::Orientation orientation,
							int role) const;

protected:
	QVariant getRecordValue(RecordBase*,int column=-1) const;
	void configureInternalSelectQuery();
};

#endif // LIBROMODEL_H
