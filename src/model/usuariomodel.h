#ifndef USUARIOMODEL_H
#define USUARIOMODEL_H

#include "om/usuariomodelbase.h"
#include "usuariorecord.h"

/*!
  Modelo de la tabla Usuario.

  Esta clase puede ser editada por el usuario y así personalizarla.

  Para mayor información ver ModelBase.
*/

class QANTMVSHARED_EXPORT UsuarioModel : public UsuarioModelBase
{
Q_OBJECT
public:
	//! Representa que configuración de consulta se esta utilizando. Para mas configuraciones agregarlas aqui.
	enum ConsConfEnum
	{
		Default//,CustomEnum
	};
	UsuarioModel(QObject *parent=NULL,
				 ConsConfEnum conf=Default);
	~UsuarioModel();

	QVariant headerData(int section, Qt::Orientation orientation,
							int role) const;

protected:
	QVariant getRecordValue(RecordBase*,int column=-1) const;
	void configureInternalSelectQuery();
};

#endif // USUARIOMODEL_H
