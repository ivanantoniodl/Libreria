#ifndef LUGARMODEL_H
#define LUGARMODEL_H

#include "om/lugarmodelbase.h"
#include "lugarrecord.h"

/*!
  Modelo de la tabla Lugar.

  Esta clase puede ser editada por el usuario y así personalizarla.

  Para mayor información ver ModelBase.
*/

class QANTMVSHARED_EXPORT LugarModel : public LugarModelBase
{
Q_OBJECT
public:
	//! Representa que configuración de consulta se esta utilizando. Para mas configuraciones agregarlas aqui.
	enum ConsConfEnum
	{
		Default//,CustomEnum
	};
	LugarModel(QObject *parent=NULL,
				 ConsConfEnum conf=Default);
	~LugarModel();

	QVariant headerData(int section, Qt::Orientation orientation,
							int role) const;

protected:
	QVariant getRecordValue(RecordBase*,int column=-1) const;
	void configureInternalSelectQuery();
};

#endif // LUGARMODEL_H
