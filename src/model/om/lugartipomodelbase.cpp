#include "lugartipomodelbase.h"

LugarTipoRecordConfigureQueryBase::LugarTipoRecordConfigureQueryBase(RecordConfigureQueryBase *rparent):
	RecordConfigureQueryBase(rparent)
{
	lstTables.prepend("LugarTipo");
	

	
}

void LugarTipoRecordConfigureQueryBase::idLugarTipo()
{
	addAttributeToQuery("idLugarTipo");
}

void LugarTipoRecordConfigureQueryBase::Tipo()
{
	addAttributeToQuery("Tipo");
}



//!Establece todos los atributos para la consulta.
void LugarTipoRecordConfigureQueryBase::allAttributes()
{
	LugarTipoRecordBase r;
	foreach( QString att, r.getAttributesList() )
		addAttributeToQuery(att);
}



//LugarTipoRecordConfigureQuery
//********************************************************************************

LugarTipoRecordConfigureQuery::LugarTipoRecordConfigureQuery(QString TableName,
						 RecordConfigureQueryBase* rparent):
	TSqlGenerator(TableName),LugarTipoRecordConfigureQueryBase(rparent)
{}

void LugarTipoRecordConfigureQuery::lstAttributesToQueryReady(QString c)
{
	addAttributeToSelect(&rb,c);
}

//LugarTipoModelBase
//********************************************************************************

/*! Contruye LugarTipoModelBase
    Se conectan las señales del registro por defecto para que cuando este configure consultas el modelo lo pueda realizar.
\param parent Padre del modelo.
*/
LugarTipoModelBase::LugarTipoModelBase(QObject *parent,
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
void LugarTipoModelBase::addSelectQueryToRecords(QSqlQuery query)
{
	query.first();

	//no se cuenta el ultimo ya que ese es solo para saber si hay mas datos a consultar
	for ( int c=0; c<actualQuerySize-( actualQuerySize==(limit+1)?1:0 ); c++ )
	{
		int pos=0;
		LugarTipoRecordBase *p=new LugarTipoRecordBase(this,NULL,DB);
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

void LugarTipoModelBase::configureInternalSelectQuery()
{
	r.allAttributes();
}

/*! Devuelve el registro por defecto del modelo.
\return Record por defecto del modelo.
*/
RecordBase *LugarTipoModelBase::defaultRecordBase() { return &ra; }

TSqlGenerator *LugarTipoModelBase::tsqlGenerator() { return &r; }

/*! Devuelve el registro por defecto para generar código SQL de la consulta.
\return LugarTipoRecord por defecto del modelo.
*/
LugarTipoRecordConfigureQuery *LugarTipoModelBase::configureQuery()
{
	fastConfiguration=true;
	return &r;
}

LugarTipoModelBase *LugarTipoModelBase::getModelRecords(QList<int> lstIndexes)
{
	if ( modelSelectedRecords != NULL )
		delete modelSelectedRecords;

	modelSelectedRecords = new LugarTipoModelBase(Parent,DB);
	foreach ( int i, lstIndexes )
	{
		if ( i < lstRecord.size() )
			modelSelectedRecords->lstRecord.append( getRecord( i ) );
	}

	return modelSelectedRecords;
}

QList<LugarTipoRecordBase*> LugarTipoModelBase::getRecords()
{
	return ModelBase::getTRecords<LugarTipoRecordBase>();
}

RecordBase *LugarTipoModelBase::getNewRecord()
{
	LugarTipoRecordBase *r = new LugarTipoRecordBase(this,NULL,DB);
	connect( r,SIGNAL(hasValuesWithOutSave(bool,RecordBase*)),
			this, SLOT(record_hasRecordsWithOutSave(bool,RecordBase*)));
	return r;
}


	


