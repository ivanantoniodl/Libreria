#include "permisomodelbase.h"

PermisoRecordConfigureQueryBase::PermisoRecordConfigureQueryBase(RecordConfigureQueryBase *rparent):
	RecordConfigureQueryBase(rparent)
{
	lstTables.prepend("Permiso");
	RGRUPOPERMISO_ = NULL;


	
}

void PermisoRecordConfigureQueryBase::idPermiso()
{
	addAttributeToQuery("idPermiso");
}

void PermisoRecordConfigureQueryBase::GrupoPermiso_idGrupoPermiso()
{
	addAttributeToQuery("GrupoPermiso_idGrupoPermiso");
}

void PermisoRecordConfigureQueryBase::Formulario()
{
	addAttributeToQuery("Formulario");
}

void PermisoRecordConfigureQueryBase::Etiqueta()
{
	addAttributeToQuery("Etiqueta");
}



//!Establece todos los atributos para la consulta.
void PermisoRecordConfigureQueryBase::allAttributes()
{
	PermisoRecordBase r;
	foreach( QString att, r.getAttributesList() )
		addAttributeToQuery(att);
}

GrupoPermisoRecordConfigureQueryBase *PermisoRecordConfigureQueryBase::RGrupoPermiso_()
{
	if ( RGRUPOPERMISO_ == NULL )
		RGRUPOPERMISO_ = new GrupoPermisoRecordConfigureQueryBase(this);
	return RGRUPOPERMISO_;
}



//PermisoRecordConfigureQuery
//********************************************************************************

PermisoRecordConfigureQuery::PermisoRecordConfigureQuery(QString TableName,
						 RecordConfigureQueryBase* rparent):
	TSqlGenerator(TableName),PermisoRecordConfigureQueryBase(rparent)
{}

void PermisoRecordConfigureQuery::lstAttributesToQueryReady(QString c)
{
	addAttributeToSelect(&rb,c);
}

//PermisoModelBase
//********************************************************************************

/*! Contruye PermisoModelBase
    Se conectan las señales del registro por defecto para que cuando este configure consultas el modelo lo pueda realizar.
\param parent Padre del modelo.
*/
PermisoModelBase::PermisoModelBase(QObject *parent,
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
void PermisoModelBase::addSelectQueryToRecords(QSqlQuery query)
{
	query.first();

	//no se cuenta el ultimo ya que ese es solo para saber si hay mas datos a consultar
	for ( int c=0; c<actualQuerySize-( actualQuerySize==(limit+1)?1:0 ); c++ )
	{
		int pos=0;
		PermisoRecordBase *p=new PermisoRecordBase(this,NULL,DB);
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

void PermisoModelBase::configureInternalSelectQuery()
{
	r.allAttributes();
}

/*! Devuelve el registro por defecto del modelo.
\return Record por defecto del modelo.
*/
RecordBase *PermisoModelBase::defaultRecordBase() { return &ra; }

TSqlGenerator *PermisoModelBase::tsqlGenerator() { return &r; }

/*! Devuelve el registro por defecto para generar código SQL de la consulta.
\return PermisoRecord por defecto del modelo.
*/
PermisoRecordConfigureQuery *PermisoModelBase::configureQuery()
{
	fastConfiguration=true;
	return &r;
}

PermisoModelBase *PermisoModelBase::getModelRecords(QList<int> lstIndexes)
{
	if ( modelSelectedRecords != NULL )
		delete modelSelectedRecords;

	modelSelectedRecords = new PermisoModelBase(Parent,DB);
	foreach ( int i, lstIndexes )
	{
		if ( i < lstRecord.size() )
			modelSelectedRecords->lstRecord.append( getRecord( i ) );
	}

	return modelSelectedRecords;
}

QList<PermisoRecordBase*> PermisoModelBase::getRecords()
{
	return ModelBase::getTRecords<PermisoRecordBase>();
}

RecordBase *PermisoModelBase::getNewRecord()
{
	PermisoRecordBase *r = new PermisoRecordBase(this,NULL,DB);
	connect( r,SIGNAL(hasValuesWithOutSave(bool,RecordBase*)),
			this, SLOT(record_hasRecordsWithOutSave(bool,RecordBase*)));
	return r;
}


	


