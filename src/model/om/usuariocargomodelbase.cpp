#include "usuariocargomodelbase.h"

UsuarioCargoRecordConfigureQueryBase::UsuarioCargoRecordConfigureQueryBase(RecordConfigureQueryBase *rparent):
	RecordConfigureQueryBase(rparent)
{
	lstTables.prepend("UsuarioCargo");
	

	
}

void UsuarioCargoRecordConfigureQueryBase::idUsuarioCargo()
{
	addAttributeToQuery("idUsuarioCargo");
}

void UsuarioCargoRecordConfigureQueryBase::Cargo()
{
	addAttributeToQuery("Cargo");
}



//!Establece todos los atributos para la consulta.
void UsuarioCargoRecordConfigureQueryBase::allAttributes()
{
	UsuarioCargoRecordBase r;
	foreach( QString att, r.getAttributesList() )
		addAttributeToQuery(att);
}



//UsuarioCargoRecordConfigureQuery
//********************************************************************************

UsuarioCargoRecordConfigureQuery::UsuarioCargoRecordConfigureQuery(QString TableName,
						 RecordConfigureQueryBase* rparent):
	TSqlGenerator(TableName),UsuarioCargoRecordConfigureQueryBase(rparent)
{}

void UsuarioCargoRecordConfigureQuery::lstAttributesToQueryReady(QString c)
{
	addAttributeToSelect(&rb,c);
}

//UsuarioCargoModelBase
//********************************************************************************

/*! Contruye UsuarioCargoModelBase
    Se conectan las señales del registro por defecto para que cuando este configure consultas el modelo lo pueda realizar.
\param parent Padre del modelo.
*/
UsuarioCargoModelBase::UsuarioCargoModelBase(QObject *parent,
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
void UsuarioCargoModelBase::addSelectQueryToRecords(QSqlQuery query)
{
	query.first();

	//no se cuenta el ultimo ya que ese es solo para saber si hay mas datos a consultar
	for ( int c=0; c<actualQuerySize-( actualQuerySize==(limit+1)?1:0 ); c++ )
	{
		int pos=0;
		UsuarioCargoRecordBase *p=new UsuarioCargoRecordBase(this,NULL,DB);
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

void UsuarioCargoModelBase::configureInternalSelectQuery()
{
	r.allAttributes();
}

/*! Devuelve el registro por defecto del modelo.
\return Record por defecto del modelo.
*/
RecordBase *UsuarioCargoModelBase::defaultRecordBase() { return &ra; }

TSqlGenerator *UsuarioCargoModelBase::tsqlGenerator() { return &r; }

/*! Devuelve el registro por defecto para generar código SQL de la consulta.
\return UsuarioCargoRecord por defecto del modelo.
*/
UsuarioCargoRecordConfigureQuery *UsuarioCargoModelBase::configureQuery()
{
	fastConfiguration=true;
	return &r;
}

UsuarioCargoModelBase *UsuarioCargoModelBase::getModelRecords(QList<int> lstIndexes)
{
	if ( modelSelectedRecords != NULL )
		delete modelSelectedRecords;

	modelSelectedRecords = new UsuarioCargoModelBase(Parent,DB);
	foreach ( int i, lstIndexes )
	{
		if ( i < lstRecord.size() )
			modelSelectedRecords->lstRecord.append( getRecord( i ) );
	}

	return modelSelectedRecords;
}

QList<UsuarioCargoRecordBase*> UsuarioCargoModelBase::getRecords()
{
	return ModelBase::getTRecords<UsuarioCargoRecordBase>();
}

RecordBase *UsuarioCargoModelBase::getNewRecord()
{
	UsuarioCargoRecordBase *r = new UsuarioCargoRecordBase(this,NULL,DB);
	connect( r,SIGNAL(hasValuesWithOutSave(bool,RecordBase*)),
			this, SLOT(record_hasRecordsWithOutSave(bool,RecordBase*)));
	return r;
}


	


