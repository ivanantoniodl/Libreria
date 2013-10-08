#include "grupopermisomodelbase.h"

GrupoPermisoRecordConfigureQueryBase::GrupoPermisoRecordConfigureQueryBase(RecordConfigureQueryBase *rparent):
	RecordConfigureQueryBase(rparent)
{
	lstTables.prepend("GrupoPermiso");
	

	
}

void GrupoPermisoRecordConfigureQueryBase::idGrupoPermiso()
{
	addAttributeToQuery("idGrupoPermiso");
}

void GrupoPermisoRecordConfigureQueryBase::Nombre()
{
	addAttributeToQuery("Nombre");
}



//!Establece todos los atributos para la consulta.
void GrupoPermisoRecordConfigureQueryBase::allAttributes()
{
	GrupoPermisoRecordBase r;
	foreach( QString att, r.getAttributesList() )
		addAttributeToQuery(att);
}



//GrupoPermisoRecordConfigureQuery
//********************************************************************************

GrupoPermisoRecordConfigureQuery::GrupoPermisoRecordConfigureQuery(QString TableName,
						 RecordConfigureQueryBase* rparent):
	TSqlGenerator(TableName),GrupoPermisoRecordConfigureQueryBase(rparent)
{}

void GrupoPermisoRecordConfigureQuery::lstAttributesToQueryReady(QString c)
{
	addAttributeToSelect(&rb,c);
}

//GrupoPermisoModelBase
//********************************************************************************

/*! Contruye GrupoPermisoModelBase
    Se conectan las señales del registro por defecto para que cuando este configure consultas el modelo lo pueda realizar.
\param parent Padre del modelo.
*/
GrupoPermisoModelBase::GrupoPermisoModelBase(QObject *parent,
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
void GrupoPermisoModelBase::addSelectQueryToRecords(QSqlQuery query)
{
	query.first();

	//no se cuenta el ultimo ya que ese es solo para saber si hay mas datos a consultar
	for ( int c=0; c<actualQuerySize-( actualQuerySize==(limit+1)?1:0 ); c++ )
	{
		int pos=0;
		GrupoPermisoRecordBase *p=new GrupoPermisoRecordBase(this,NULL,DB);
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

void GrupoPermisoModelBase::configureInternalSelectQuery()
{
	r.allAttributes();
}

/*! Devuelve el registro por defecto del modelo.
\return Record por defecto del modelo.
*/
RecordBase *GrupoPermisoModelBase::defaultRecordBase() { return &ra; }

TSqlGenerator *GrupoPermisoModelBase::tsqlGenerator() { return &r; }

/*! Devuelve el registro por defecto para generar código SQL de la consulta.
\return GrupoPermisoRecord por defecto del modelo.
*/
GrupoPermisoRecordConfigureQuery *GrupoPermisoModelBase::configureQuery()
{
	fastConfiguration=true;
	return &r;
}

GrupoPermisoModelBase *GrupoPermisoModelBase::getModelRecords(QList<int> lstIndexes)
{
	if ( modelSelectedRecords != NULL )
		delete modelSelectedRecords;

	modelSelectedRecords = new GrupoPermisoModelBase(Parent,DB);
	foreach ( int i, lstIndexes )
	{
		if ( i < lstRecord.size() )
			modelSelectedRecords->lstRecord.append( getRecord( i ) );
	}

	return modelSelectedRecords;
}

QList<GrupoPermisoRecordBase*> GrupoPermisoModelBase::getRecords()
{
	return ModelBase::getTRecords<GrupoPermisoRecordBase>();
}

RecordBase *GrupoPermisoModelBase::getNewRecord()
{
	GrupoPermisoRecordBase *r = new GrupoPermisoRecordBase(this,NULL,DB);
	connect( r,SIGNAL(hasValuesWithOutSave(bool,RecordBase*)),
			this, SLOT(record_hasRecordsWithOutSave(bool,RecordBase*)));
	return r;
}


	


