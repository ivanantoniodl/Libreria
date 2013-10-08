#include "maquinamodel.h"

QString MaquinaModel::CurrentDBUser="";
QString MaquinaModel::CurrentDBHost="";
LugarRecord *MaquinaModel::CurrentLugarRecord=NULL;
EmpresaRecord *MaquinaModel::CurrentEmpresaRecord=NULL;

MaquinaModel::MaquinaModel(QObject *parent,
						   ConsConfEnum conf) :
MaquinaModelBase(parent)
{
	Q_UNUSED(conf)	//delete
	//setConsConf( conf ); //uncomment
}

MaquinaModel::~MaquinaModel()
{
}

/*! Configura una consulta

  Ver ModelBase para mayor información.

  Implementada de ModelBase::configurarQuery().
*/
void MaquinaModel::configureInternalSelectQuery()
{
	switch (getConsConf())
	{
	case Default:
		break;
//	case CustomEnum:
//		r.setIdPersona();
//		r.setNombre();
//		r.setLugar_idLugar();
//		r.RLugar_idLugar()->setNombre();
		break;
	}
}

/*! Devuelve el valor de un atributo de registro.
	Si al ejecutarse este método esta:

	\code
	return ModelBase::getRecordValue(record,column);
	\endcode

	se mostrarán las columnas tal y como se configuro la consulta, de lo contrario se mostrarán las columnas personalizadas.

	Ver ModelBase para mayor información.

	Implementada de ModelBase::getRecordValue().
*/
QVariant MaquinaModel::getRecordValue(RecordBase *record,int column) const
{
	return ModelBase::getRecordValue(record,column); //delete

//	MaquinaRecord *r=(MaquinaRecord*)record;
//	switch (getConsConf())
//	{
//	case Default:
//		return ModelBase::getRecordValue(record,column);
//	case CustomEnum:
//		switch (column)
//		{
////	case 0:	return r->idPersona();
////	case 1: return r->Nombre();
////	case 2: return QString::number(r->RLugar_idLugar()->idLugar())+", "+
////			r->RLugar_idLugar()->Nombre();
//		};
//		break;
//	};
//	return QVariant();
}

/*! Configura el nombre de las cabeceras de las columnas.

  Ver ModelBase para mayor información.

  Reimplementado de QAbstractItemModel::headerData().
*/
QVariant MaquinaModel::headerData(int section,
								  Qt::Orientation orientation,
								  int role) const
{
	return MaquinaModelBase::headerData(section,
									orientation,
									role); //delete

//	if (role != Qt::DisplayRole)
//		return QVariant();
//	if ( orientation == Qt::Vertical )
//		return section+1;

//	switch (getConsConf())
//	{
//	case Default:
//		return MaquinaModelBase::headerData(section,
//										orientation,
//										role);
//	case CustomEnum:
//		switch ( section )
//		{
////	case 0: return "idPersona";
////	case 1: return "Name";
////	case 2: return "idLugar";
////	case 3: return "Lugar";
//		};
//		break;
//	};
//	return QVariant();
}

QString MaquinaModel::currentDBUser()
{
    if ( CurrentDBUser.isEmpty() )
    {
        QSqlQuery query("SELECT SUBSTRING_INDEX(USER(),'@',1)");
        query.first();
        CurrentDBUser = query.value(0).toString();
    }
    return CurrentDBUser;
}

QString MaquinaModel::currentDBHost()
{
    if ( CurrentDBUser.isEmpty() )
    {
        QSqlQuery query("SELECT SUBSTRING_INDEX(USER(), '@', -1)");
        query.first();
        CurrentDBHost = query.value(0).toString();
    }
    return CurrentDBHost;
}

LugarRecord* MaquinaModel::currentLugarRecord()
{
    if ( CurrentLugarRecord == NULL )
    {
        QSettings settings;
        settings.beginGroup("Lugar");
        int idlugar = settings.value("idLugar").toInt();
        settings.endGroup();

        LugarRecord *record = new LugarRecord;
        record->setIdLugar( idlugar );
        TSqlError error;
        error = record->select();
        if ( ! error.isError() )
            CurrentLugarRecord = record;
    }
    return CurrentLugarRecord;
}

EmpresaRecord* MaquinaModel::currentEmpresaRecord()
{
    if ( CurrentEmpresaRecord == NULL )
    {
        QSettings settings;
        settings.beginGroup("Empresa");
        int idEmpresa = settings.value("idEmpresa").toInt();
        settings.endGroup();

        EmpresaRecord *record = new EmpresaRecord;
        record->setIdEmpresa( idEmpresa );
        TSqlError error;
        error = record->select();
        if ( ! error.isError() )
            CurrentEmpresaRecord = record;
    }
    return CurrentEmpresaRecord;
}

