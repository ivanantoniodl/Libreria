#ifndef PERMISOMODEL_H
#define PERMISOMODEL_H

#include "om/permisomodelbase.h"
#include "permisorecord.h"

/*!
  Modelo de la tabla Permiso.

  Esta clase puede ser editada por el usuario y así personalizarla.

  Para mayor información ver ModelBase.
*/

class QANTMVSHARED_EXPORT PermisoModel : public PermisoModelBase
{
Q_OBJECT
public:
	//! Representa que configuración de consulta se esta utilizando. Para mas configuraciones agregarlas aqui.
	enum ConsConfEnum
	{
		Default//,CustomEnum
	};
	PermisoModel(QObject *parent=NULL,
				 ConsConfEnum conf=Default);
	~PermisoModel();

	QVariant headerData(int section, Qt::Orientation orientation,
							int role) const;

protected:
	QVariant getRecordValue(RecordBase*,int column=-1) const;
	void configureInternalSelectQuery();
};

#endif // PERMISOMODEL_H
