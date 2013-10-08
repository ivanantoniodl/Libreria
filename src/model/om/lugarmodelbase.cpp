#include "lugarmodelbase.h"

LugarRecordConfigureQueryBase::LugarRecordConfigureQueryBase(RecordConfigureQueryBase *rparent):
	RecordConfigureQueryBase(rparent)
{
	lstTables.prepend("Lugar");
	REMPRESA_ = NULL;
RLUGARTIPO_ = NULL;


	
}

void LugarRecordConfigureQueryBase::idLugar()
{
	addAttributeToQuery("idLugar");
}

void LugarRecordConfigureQueryBase::Empresa_idEmpresa()
{
	addAttributeToQuery("Empresa_idEmpresa");
}

void LugarRecordConfigureQueryBase::LugarTipo_idLugarTipo()
{
	addAttributeToQuery("LugarTipo_idLugarTipo");
}

void LugarRecordConfigureQueryBase::Nombre()
{
	addAttributeToQuery("Nombre");
}

void LugarRecordConfigureQueryBase::Direccion()
{
	addAttributeToQuery("Direccion");
}

void LugarRecordConfigureQueryBase::Telefono()
{
	addAttributeToQuery("Telefono");
}

void LugarRecordConfigureQueryBase::NumPlaca()
{
	addAttributeToQuery("NumPlaca");
}



//!Establece todos los atributos para la consulta.
void LugarRecordConfigureQueryBase::allAttributes()
{
	LugarRecordBase r;
	foreach( QString att, r.getAttributesList() )
		addAttributeToQuery(att);
}

EmpresaRecordConfigureQueryBase *LugarRecordConfigureQueryBase::REmpresa_()
{
	if ( REMPRESA_ == NULL )
		REMPRESA_ = new EmpresaRecordConfigureQueryBase(this);
	return REMPRESA_;
}

LugarTipoRecordConfigureQueryBase *LugarRecordConfigureQueryBase::RLugarTipo_()
{
	if ( RLUGARTIPO_ == NULL )
		RLUGARTIPO_ = new LugarTipoRecordConfigureQueryBase(this);
	return RLUGARTIPO_;
}



//LugarRecordConfigureQuery
//********************************************************************************

LugarRecordConfigureQuery::LugarRecordConfigureQuery(QString TableName,
						 RecordConfigureQueryBase* rparent):
	TSqlGenerator(TableName),LugarRecordConfigureQueryBase(rparent)
{}

void LugarRecordConfigureQuery::lstAttributesToQueryReady(QString c)
{
	addAttributeToSelect(&rb,c);
}

//LugarModelBase
//********************************************************************************

/*! Contruye LugarModelBase
    Se conectan las señales del registro por defecto para que cuando este configure consultas el modelo lo pueda realizar.
\param parent Padre del modelo.
*/
LugarModelBase::LugarModelBase(QObject *parent,
					 QSqlDatabase db) :
			ModelBase(parent,db)
{
	
	tableName=ra.tableName();
	modelSelectedRecords=NULL;
	r.setTableName(ra.tableName());
	r.setSQLDatabase(&db);
}

/*! Encargado de llenar la lista de registros del modelo con el resultado de la consulta.
\param query Query de donde tomar los datos.
*/
void LugarModelBase::addSelectQueryToRecords(QSqlQuery query)
{
	query.first();

	//no se cuenta el ultimo ya que ese es solo para saber si hay mas datos a consultar
	for ( int c=0; c<actualQuerySize-( actualQuerySize==(limit+1)?1:0 ); c++ )
	{
		int pos=0;
		LugarRecordBase *p=new LugarRecordBase(this,NULL,DB);
		setRecordEnabledBackup( p,false );
		foreach ( confInsertValue *iv, lstCIV )
			setAttributeValue(p,iv,query.value(pos++));
		setRecordEnabledBackup( p,true );
		
		connect( p,SIGNAL(hasValuesWithOutSave(bool,RecordBase*)),
				this, SLOT(record_hasRecordsWithOutSave(bool,RecordBase*)));

		lstRecord.append(p);
		query.next();
	}
}

void LugarModelBase::configureInternalSelectQuery()
{
	r.allAttributes();
}

/*! Devuelve el registro por defecto del modelo.
\return Record por defecto del modelo.
*/
RecordBase *LugarModelBase::defaultRecordBase() { return &ra; }

TSqlGenerator *LugarModelBase::tsqlGenerator() { return &r; }

/*! Devuelve el registro por defecto para generar código SQL de la consulta.
\return LugarRecord por defecto del modelo.
*/
LugarRecordConfigureQuery *LugarModelBase::configureQuery()
{
	fastConfiguration=true;
	return &r;
}

LugarModelBase *LugarModelBase::getModelRecords(QList<int> lstIndexes)
{
	if ( modelSelectedRecords != NULL )
		delete modelSelectedRecords;

	modelSelectedRecords = new LugarModelBase(Parent,DB);
	foreach ( int i, lstIndexes )
	{
		if ( i < lstRecord.size() )
			modelSelectedRecords->lstRecord.append( getRecord( i ) );
	}

	return modelSelectedRecords;
}

QList<LugarRecordBase*> LugarModelBase::getRecords()
{
	return ModelBase::getTRecords<LugarRecordBase>();
}

RecordBase *LugarModelBase::getNewRecord()
{
	LugarRecordBase *r = new LugarRecordBase(this,NULL,DB);
	connect( r,SIGNAL(hasValuesWithOutSave(bool,RecordBase*)),
			this, SLOT(record_hasRecordsWithOutSave(bool,RecordBase*)));
	return r;
}


	


