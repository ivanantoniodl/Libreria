#ifndef ROLPERMISOMODEL_H
#define ROLPERMISOMODEL_H

#include "om/rolpermisomodelbase.h"
#include "rolpermisorecord.h"

/*!
  Modelo de la tabla RolPermiso.

  Esta clase puede ser editada por el usuario y así personalizarla.

  Para mayor información ver ModelBase.
*/

class QANTMVSHARED_EXPORT RolPermisoModel : public RolPermisoModelBase
{
Q_OBJECT
public:
	//! Representa que configuración de consulta se esta utilizando. Para mas configuraciones agregarlas aqui.
	enum ConsConfEnum
	{
		Default//,CustomEnum
	};
	RolPermisoModel(QObject *parent=NULL,
				 ConsConfEnum conf=Default);
	~RolPermisoModel();

	QVariant headerData(int section, Qt::Orientation orientation,
							int role) const;

	static int staticBuscarPermiso(QString usuario, QString nombreFormulario, QString grupo);

protected:
	QVariant getRecordValue(RecordBase*,int column=-1) const;
	void configureInternalSelectQuery();
};

#endif // ROLPERMISOMODEL_H
