#ifndef EMPRESAMODEL_H
#define EMPRESAMODEL_H

#include "om/empresamodelbase.h"
#include "empresarecord.h"

/*!
  Modelo de la tabla Empresa.

  Esta clase puede ser editada por el usuario y así personalizarla.

  Para mayor información ver ModelBase.
*/

class QANTMVSHARED_EXPORT EmpresaModel : public EmpresaModelBase
{
Q_OBJECT
public:
	//! Representa que configuración de consulta se esta utilizando. Para mas configuraciones agregarlas aqui.
	enum ConsConfEnum
	{
		Default//,CustomEnum
	};
	EmpresaModel(QObject *parent=NULL,
				 ConsConfEnum conf=Default);
	~EmpresaModel();

	QVariant headerData(int section, Qt::Orientation orientation,
							int role) const;

protected:
	QVariant getRecordValue(RecordBase*,int column=-1) const;
	void configureInternalSelectQuery();
};

#endif // EMPRESAMODEL_H
