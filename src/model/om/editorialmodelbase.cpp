#include "editorialmodelbase.h"

EditorialRecordConfigureQueryBase::EditorialRecordConfigureQueryBase(RecordConfigureQueryBase *rparent):
	RecordConfigureQueryBase(rparent)
{
	lstTables.prepend("Editorial");
	

	
}

void EditorialRecordConfigureQueryBase::id()
{
	addAttributeToQuery("id");
}

void EditorialRecordConfigureQueryBase::Nombre()
{
	addAttributeToQuery("Nombre");
}

void EditorialRecordConfigureQueryBase::Direccion()
{
	addAttributeToQuery("Direccion");
}



//!Establece todos los atributos para la consulta.
void EditorialRecordConfigureQueryBase::allAttributes()
{
	EditorialRecordBase r;
	foreach( QString att, r.getAttributesList() )
		addAttributeToQuery(att);
}



//EditorialRecordConfigureQuery
//********************************************************************************

EditorialRecordConfigureQuery::EditorialRecordConfigureQuery(QString TableName,
						 RecordConfigureQueryBase* rparent):
	TSqlGenerator(TableName),EditorialRecordConfigureQueryBase(rparent)
{}

void EditorialRecordConfigureQuery::lstAttributesToQueryReady(QString c)
{
	addAttributeToSelect(&rb,c);
}

//EditorialModelBase
//********************************************************************************

/*! Contruye EditorialModelBase
    Se conectan las señales del registro por defecto para que cuando este configure consultas el modelo lo pueda realizar.
\param parent Padre del modelo.
*/
EditorialModelBase::EditorialModelBase(QObject *parent,
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
void EditorialModelBase::addSelectQueryToRecords(QSqlQuery query)
{
	query.first();

	//no se cuenta el ultimo ya que ese es solo para saber si hay mas datos a consultar
	for ( int c=0; c<actualQuerySize-( actualQuerySize==(limit+1)?1:0 ); c++ )
	{
		int pos=0;
		EditorialRecordBase *p=new EditorialRecordBase(this,NULL,DB);
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

void EditorialModelBase::configureInternalSelectQuery()
{
	r.allAttributes();
}

/*! Devuelve el registro por defecto del modelo.
\return Record por defecto del modelo.
*/
RecordBase *EditorialModelBase::defaultRecordBase() { return &ra; }

TSqlGenerator *EditorialModelBase::tsqlGenerator() { return &r; }

/*! Devuelve el registro por defecto para generar código SQL de la consulta.
\return EditorialRecord por defecto del modelo.
*/
EditorialRecordConfigureQuery *EditorialModelBase::configureQuery()
{
	fastConfiguration=true;
	return &r;
}

EditorialModelBase *EditorialModelBase::getModelRecords(QList<int> lstIndexes)
{
	if ( modelSelectedRecords != NULL )
		delete modelSelectedRecords;

	modelSelectedRecords = new EditorialModelBase(Parent,DB);
	foreach ( int i, lstIndexes )
	{
		if ( i < lstRecord.size() )
			modelSelectedRecords->lstRecord.append( getRecord( i ) );
	}

	return modelSelectedRecords;
}

QList<EditorialRecordBase*> EditorialModelBase::getRecords()
{
	return ModelBase::getTRecords<EditorialRecordBase>();
}

RecordBase *EditorialModelBase::getNewRecord()
{
	EditorialRecordBase *r = new EditorialRecordBase(this,NULL,DB);
	connect( r,SIGNAL(hasValuesWithOutSave(bool,RecordBase*)),
			this, SLOT(record_hasRecordsWithOutSave(bool,RecordBase*)));
	return r;
}


	


