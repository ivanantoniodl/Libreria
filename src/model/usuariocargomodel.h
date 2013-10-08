#ifndef USUARIOCARGOMODEL_H
#define USUARIOCARGOMODEL_H

#include "om/usuariocargomodelbase.h"
#include "usuariocargorecord.h"

/*!
  Modelo de la tabla UsuarioCargo.

  Esta clase puede ser editada por el usuario y así personalizarla.

  Para mayor información ver ModelBase.
*/

class QANTMVSHARED_EXPORT UsuarioCargoModel : public UsuarioCargoModelBase
{
Q_OBJECT
public:
	//! Representa que configuración de consulta se esta utilizando. Para mas configuraciones agregarlas aqui.
	enum ConsConfEnum
	{
		Default//,CustomEnum
	};
	UsuarioCargoModel(QObject *parent=NULL,
				 ConsConfEnum conf=Default);
	~UsuarioCargoModel();

	QVariant headerData(int section, Qt::Orientation orientation,
							int role) const;

protected:
	QVariant getRecordValue(RecordBase*,int column=-1) const;
	void configureInternalSelectQuery();
};

#endif // USUARIOCARGOMODEL_H
