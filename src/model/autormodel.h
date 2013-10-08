#ifndef AUTORMODEL_H
#define AUTORMODEL_H

#include "om/autormodelbase.h"
#include "autorrecord.h"

/*!
  Modelo de la tabla Autor.

  Esta clase puede ser editada por el usuario y así personalizarla.

  Para mayor información ver ModelBase.
*/

class QANTMVSHARED_EXPORT AutorModel : public AutorModelBase
{
Q_OBJECT
public:
	//! Representa que configuración de consulta se esta utilizando. Para mas configuraciones agregarlas aqui.
	enum ConsConfEnum
	{
		Default//,CustomEnum
	};
	AutorModel(QObject *parent=NULL,
				 ConsConfEnum conf=Default);
	~AutorModel();

	QVariant headerData(int section, Qt::Orientation orientation,
							int role) const;

protected:
	QVariant getRecordValue(RecordBase*,int column=-1) const;
	void configureInternalSelectQuery();
};

#endif // AUTORMODEL_H
