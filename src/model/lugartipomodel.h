#ifndef LUGARTIPOMODEL_H
#define LUGARTIPOMODEL_H

#include "om/lugartipomodelbase.h"
#include "lugartiporecord.h"

/*!
  Modelo de la tabla LugarTipo.

  Esta clase puede ser editada por el usuario y así personalizarla.

  Para mayor información ver ModelBase.
*/

class QANTMVSHARED_EXPORT LugarTipoModel : public LugarTipoModelBase
{
Q_OBJECT
public:
	//! Representa que configuración de consulta se esta utilizando. Para mas configuraciones agregarlas aqui.
	enum ConsConfEnum
	{
		Default//,CustomEnum
	};
	LugarTipoModel(QObject *parent=NULL,
				 ConsConfEnum conf=Default);
	~LugarTipoModel();

	QVariant headerData(int section, Qt::Orientation orientation,
							int role) const;

protected:
	QVariant getRecordValue(RecordBase*,int column=-1) const;
	void configureInternalSelectQuery();
};

#endif // LUGARTIPOMODEL_H
