#ifndef GRUPOPERMISOMODEL_H
#define GRUPOPERMISOMODEL_H

#include "om/grupopermisomodelbase.h"
#include "grupopermisorecord.h"

/*!
  Modelo de la tabla GrupoPermiso.

  Esta clase puede ser editada por el usuario y así personalizarla.

  Para mayor información ver ModelBase.
*/

class QANTMVSHARED_EXPORT GrupoPermisoModel : public GrupoPermisoModelBase
{
Q_OBJECT
public:
	//! Representa que configuración de consulta se esta utilizando. Para mas configuraciones agregarlas aqui.
	enum ConsConfEnum
	{
		Default//,CustomEnum
	};
	GrupoPermisoModel(QObject *parent=NULL,
				 ConsConfEnum conf=Default);
	~GrupoPermisoModel();

	QVariant headerData(int section, Qt::Orientation orientation,
							int role) const;

protected:
	QVariant getRecordValue(RecordBase*,int column=-1) const;
	void configureInternalSelectQuery();
};

#endif // GRUPOPERMISOMODEL_H
