#include "rolpermisomodelbase.h"

RolPermisoRecordConfigureQueryBase::RolPermisoRecordConfigureQueryBase(RecordConfigureQueryBase *rparent):
	RecordConfigureQueryBase(rparent)
{
	lstTables.prepend("RolPermiso");
	RPERMISO_ = NULL;
RROL_ = NULL;


	
}

void RolPermisoRecordConfigureQueryBase::idRolPermiso()
{
	addAttributeToQuery("idRolPermiso");
}

void RolPermisoRecordConfigureQueryBase::Permiso_idPermiso()
{
	addAttributeToQuery("Permiso_idPermiso");
}

void RolPermisoRecordConfigureQueryBase::Rol_idRol()
{
	addAttributeToQuery("Rol_idRol");
}

void RolPermisoRecordConfigureQueryBase::Permiso()
{
	addAttributeToQuery("Permiso");
}



//!Establece todos los atributos para la consulta.
void RolPermisoRecordConfigureQueryBase::allAttributes()
{
	RolPermisoRecordBase r;
	foreach( QString att, r.getAttributesList() )
		addAttributeToQuery(att);
}

PermisoRecordConfigureQueryBase *RolPermisoRecordConfigureQueryBase::RPermiso_()
{
	if ( RPERMISO_ == NULL )
		RPERMISO_ = new PermisoRecordConfigureQueryBase(this);
	return RPERMISO_;
}

RolRecordConfigureQueryBase *RolPermisoRecordConfigureQueryBase::RRol_()
{
	if ( RROL_ == NULL )
		RROL_ = new RolRecordConfigureQueryBase(this);
	return RROL_;
}



//RolPermisoRecordConfigureQuery
//********************************************************************************

RolPermisoRecordConfigureQuery::RolPermisoRecordConfigureQuery(QString TableName,
						 RecordConfigureQueryBase* rparent):
	TSqlGenerator(TableName),RolPermisoRecordConfigureQueryBase(rparent)
{}

void RolPermisoRecordConfigureQuery::lstAttributesToQueryReady(QString c)
{
	addAttributeToSelect(&rb,c);
}

//RolPermisoModelBase
//********************************************************************************

/*! Contruye RolPermisoModelBase
    Se conectan las señales del registro por defecto para que cuando este configure consultas el modelo lo pueda realizar.
\param parent Padre del modelo.
*/
RolPermisoModelBase::RolPermisoModelBase(QObject *parent,
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
void RolPermisoModelBase::addSelectQueryToRecords(QSqlQuery query)
{
	query.first();

	//no se cuenta el ultimo ya que ese es solo para saber si hay mas datos a consultar
	for ( int c=0; c<actualQuerySize-( actualQuerySize==(limit+1)?1:0 ); c++ )
	{
		int pos=0;
		RolPermisoRecordBase *p=new RolPermisoRecordBase(this,NULL,DB);
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

void RolPermisoModelBase::configureInternalSelectQuery()
{
	r.allAttributes();
}

/*! Devuelve el registro por defecto del modelo.
\return Record por defecto del modelo.
*/
RecordBase *RolPermisoModelBase::defaultRecordBase() { return &ra; }

TSqlGenerator *RolPermisoModelBase::tsqlGenerator() { return &r; }

/*! Devuelve el registro por defecto para generar código SQL de la consulta.
\return RolPermisoRecord por defecto del modelo.
*/
RolPermisoRecordConfigureQuery *RolPermisoModelBase::configureQuery()
{
	fastConfiguration=true;
	return &r;
}

RolPermisoModelBase *RolPermisoModelBase::getModelRecords(QList<int> lstIndexes)
{
	if ( modelSelectedRecords != NULL )
		delete modelSelectedRecords;

	modelSelectedRecords = new RolPermisoModelBase(Parent,DB);
	foreach ( int i, lstIndexes )
	{
		if ( i < lstRecord.size() )
			modelSelectedRecords->lstRecord.append( getRecord( i ) );
	}

	return modelSelectedRecords;
}

QList<RolPermisoRecordBase*> RolPermisoModelBase::getRecords()
{
	return ModelBase::getTRecords<RolPermisoRecordBase>();
}

RecordBase *RolPermisoModelBase::getNewRecord()
{
	RolPermisoRecordBase *r = new RolPermisoRecordBase(this,NULL,DB);
	connect( r,SIGNAL(hasValuesWithOutSave(bool,RecordBase*)),
			this, SLOT(record_hasRecordsWithOutSave(bool,RecordBase*)));
	return r;
}


	


