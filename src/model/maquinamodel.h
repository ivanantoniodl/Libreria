#ifndef MAQUINAMODEL_H
#define MAQUINAMODEL_H

#include "om/maquinamodelbase.h"
#include "maquinarecord.h"

#include "lugarrecord.h"
#include "empresarecord.h"

/*!
  Modelo de la tabla Maquina.

  Esta clase puede ser editada por el usuario y así personalizarla.

  Para mayor información ver ModelBase.
*/

class QANTMVSHARED_EXPORT MaquinaModel : public MaquinaModelBase
{
friend class ConfigLugarPage;
friend class FEmpresasPage;
Q_OBJECT
private:
    static QString CurrentDBUser;
    static QString CurrentDBHost;
    static LugarRecord *CurrentLugarRecord;
    static EmpresaRecord *CurrentEmpresaRecord;
public:
	//! Representa que configuración de consulta se esta utilizando. Para mas configuraciones agregarlas aqui.
	enum ConsConfEnum
	{
		Default//,CustomEnum
	};
	MaquinaModel(QObject *parent=NULL,
				 ConsConfEnum conf=Default);
	~MaquinaModel();

	QVariant headerData(int section, Qt::Orientation orientation,
							int role) const;

protected:
	QVariant getRecordValue(RecordBase*,int column=-1) const;
	void configureInternalSelectQuery();

public:
    static QString currentDBUser();
    static QString currentDBHost();
    static LugarRecord* currentLugarRecord();
    static EmpresaRecord* currentEmpresaRecord();
};

#endif // MAQUINAMODEL_H
