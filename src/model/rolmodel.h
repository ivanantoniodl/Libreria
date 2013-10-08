#ifndef ROLMODEL_H
#define ROLMODEL_H

#include "om/rolmodelbase.h"
#include "rolrecord.h"

/*!
  Modelo de la tabla Rol.

  Esta clase puede ser editada por el usuario y así personalizarla.

  Para mayor información ver ModelBase.
*/

class QANTMVSHARED_EXPORT RolModel : public RolModelBase
{
Q_OBJECT
public:
	//! Representa que configuración de consulta se esta utilizando. Para mas configuraciones agregarlas aqui.
	enum ConsConfEnum
	{
		Default//,CustomEnum
	};
	RolModel(QObject *parent=NULL,
				 ConsConfEnum conf=Default);
	~RolModel();

	QVariant headerData(int section, Qt::Orientation orientation,
							int role) const;

protected:
	QVariant getRecordValue(RecordBase*,int column=-1) const;
	void configureInternalSelectQuery();
};

#endif // ROLMODEL_H
