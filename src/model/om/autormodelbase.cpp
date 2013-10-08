#include "autormodelbase.h"

AutorRecordConfigureQueryBase::AutorRecordConfigureQueryBase(RecordConfigureQueryBase *rparent):
	RecordConfigureQueryBase(rparent)
{
	lstTables.prepend("Autor");
	

	
}

void AutorRecordConfigureQueryBase::id()
{
	addAttributeToQuery("id");
}

void AutorRecordConfigureQueryBase::Nombre()
{
	addAttributeToQuery("Nombre");
}

void AutorRecordConfigureQueryBase::Direccion()
{
	addAttributeToQuery("Direccion");
}



//!Establece todos los atributos para la consulta.
void AutorRecordConfigureQueryBase::allAttributes()
{
	AutorRecordBase r;
	foreach( QString att, r.getAttributesList() )
		addAttributeToQuery(att);
}



//AutorRecordConfigureQuery
//********************************************************************************

AutorRecordConfigureQuery::AutorRecordConfigureQuery(QString TableName,
						 RecordConfigureQueryBase* rparent):
	TSqlGenerator(TableName),AutorRecordConfigureQueryBase(rparent)
{}

void AutorRecordConfigureQuery::lstAttributesToQueryReady(QString c)
{
	addAttributeToSelect(&rb,c);
}

//AutorModelBase
//********************************************************************************

/*! Contruye AutorModelBase
    Se conectan las señales del registro por defecto para que cuando este configure consultas el modelo lo pueda realizar.
\param parent Padre del modelo.
*/
AutorModelBase::AutorModelBase(QObject *parent,
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
void AutorModelBase::addSelectQueryToRecords(QSqlQuery query)
{
	query.first();

	//no se cuenta el ultimo ya que ese es solo para saber si hay mas datos a consultar
	for ( int c=0; c<actualQuerySize-( actualQuerySize==(limit+1)?1:0 ); c++ )
	{
		int pos=0;
		AutorRecordBase *p=new AutorRecordBase(this,NULL,DB);
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

void AutorModelBase::configureInternalSelectQuery()
{
	r.allAttributes();
}

/*! Devuelve el registro por defecto del modelo.
\return Record por defecto del modelo.
*/
RecordBase *AutorModelBase::defaultRecordBase() { return &ra; }

TSqlGenerator *AutorModelBase::tsqlGenerator() { return &r; }

/*! Devuelve el registro por defecto para generar código SQL de la consulta.
\return AutorRecord por defecto del modelo.
*/
AutorRecordConfigureQuery *AutorModelBase::configureQuery()
{
	fastConfiguration=true;
	return &r;
}

AutorModelBase *AutorModelBase::getModelRecords(QList<int> lstIndexes)
{
	if ( modelSelectedRecords != NULL )
		delete modelSelectedRecords;

	modelSelectedRecords = new AutorModelBase(Parent,DB);
	foreach ( int i, lstIndexes )
	{
		if ( i < lstRecord.size() )
			modelSelectedRecords->lstRecord.append( getRecord( i ) );
	}

	return modelSelectedRecords;
}

QList<AutorRecordBase*> AutorModelBase::getRecords()
{
	return ModelBase::getTRecords<AutorRecordBase>();
}

RecordBase *AutorModelBase::getNewRecord()
{
	AutorRecordBase *r = new AutorRecordBase(this,NULL,DB);
	connect( r,SIGNAL(hasValuesWithOutSave(bool,RecordBase*)),
			this, SLOT(record_hasRecordsWithOutSave(bool,RecordBase*)));
	return r;
}


	


