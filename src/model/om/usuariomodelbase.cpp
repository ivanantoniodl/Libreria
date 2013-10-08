#include "usuariomodelbase.h"

UsuarioRecordConfigureQueryBase::UsuarioRecordConfigureQueryBase(RecordConfigureQueryBase *rparent):
	RecordConfigureQueryBase(rparent)
{
	lstTables.prepend("Usuario");
	REMPRESA_ = NULL;
RROL_ = NULL;
RUSUARIOCARGO_ = NULL;


	
}

void UsuarioRecordConfigureQueryBase::idUsuario()
{
	addAttributeToQuery("idUsuario");
}

void UsuarioRecordConfigureQueryBase::Empresa_idEmpresa()
{
	addAttributeToQuery("Empresa_idEmpresa");
}

void UsuarioRecordConfigureQueryBase::Rol_idRol()
{
	addAttributeToQuery("Rol_idRol");
}

void UsuarioRecordConfigureQueryBase::UsuarioCargo_idUsuarioCargo()
{
	addAttributeToQuery("UsuarioCargo_idUsuarioCargo");
}

void UsuarioRecordConfigureQueryBase::Nombres()
{
	addAttributeToQuery("Nombres");
}

void UsuarioRecordConfigureQueryBase::Apellidos()
{
	addAttributeToQuery("Apellidos");
}

void UsuarioRecordConfigureQueryBase::Usuario()
{
	addAttributeToQuery("Usuario");
}

void UsuarioRecordConfigureQueryBase::FechaHora()
{
	addAttributeToQuery("FechaHora");
}

void UsuarioRecordConfigureQueryBase::Turno()
{
	addAttributeToQuery("Turno");
}



//!Establece todos los atributos para la consulta.
void UsuarioRecordConfigureQueryBase::allAttributes()
{
	UsuarioRecordBase r;
	foreach( QString att, r.getAttributesList() )
		addAttributeToQuery(att);
}

EmpresaRecordConfigureQueryBase *UsuarioRecordConfigureQueryBase::REmpresa_()
{
	if ( REMPRESA_ == NULL )
		REMPRESA_ = new EmpresaRecordConfigureQueryBase(this);
	return REMPRESA_;
}

RolRecordConfigureQueryBase *UsuarioRecordConfigureQueryBase::RRol_()
{
	if ( RROL_ == NULL )
		RROL_ = new RolRecordConfigureQueryBase(this);
	return RROL_;
}

UsuarioCargoRecordConfigureQueryBase *UsuarioRecordConfigureQueryBase::RUsuarioCargo_()
{
	if ( RUSUARIOCARGO_ == NULL )
		RUSUARIOCARGO_ = new UsuarioCargoRecordConfigureQueryBase(this);
	return RUSUARIOCARGO_;
}



//UsuarioRecordConfigureQuery
//********************************************************************************

UsuarioRecordConfigureQuery::UsuarioRecordConfigureQuery(QString TableName,
						 RecordConfigureQueryBase* rparent):
	TSqlGenerator(TableName),UsuarioRecordConfigureQueryBase(rparent)
{}

void UsuarioRecordConfigureQuery::lstAttributesToQueryReady(QString c)
{
	addAttributeToSelect(&rb,c);
}

//UsuarioModelBase
//********************************************************************************

/*! Contruye UsuarioModelBase
    Se conectan las señales del registro por defecto para que cuando este configure consultas el modelo lo pueda realizar.
\param parent Padre del modelo.
*/
UsuarioModelBase::UsuarioModelBase(QObject *parent,
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
void UsuarioModelBase::addSelectQueryToRecords(QSqlQuery query)
{
	query.first();

	//no se cuenta el ultimo ya que ese es solo para saber si hay mas datos a consultar
	for ( int c=0; c<actualQuerySize-( actualQuerySize==(limit+1)?1:0 ); c++ )
	{
		int pos=0;
		UsuarioRecordBase *p=new UsuarioRecordBase(this,NULL,DB);
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

void UsuarioModelBase::configureInternalSelectQuery()
{
	r.allAttributes();
}

/*! Devuelve el registro por defecto del modelo.
\return Record por defecto del modelo.
*/
RecordBase *UsuarioModelBase::defaultRecordBase() { return &ra; }

TSqlGenerator *UsuarioModelBase::tsqlGenerator() { return &r; }

/*! Devuelve el registro por defecto para generar código SQL de la consulta.
\return UsuarioRecord por defecto del modelo.
*/
UsuarioRecordConfigureQuery *UsuarioModelBase::configureQuery()
{
	fastConfiguration=true;
	return &r;
}

UsuarioModelBase *UsuarioModelBase::getModelRecords(QList<int> lstIndexes)
{
	if ( modelSelectedRecords != NULL )
		delete modelSelectedRecords;

	modelSelectedRecords = new UsuarioModelBase(Parent,DB);
	foreach ( int i, lstIndexes )
	{
		if ( i < lstRecord.size() )
			modelSelectedRecords->lstRecord.append( getRecord( i ) );
	}

	return modelSelectedRecords;
}

QList<UsuarioRecordBase*> UsuarioModelBase::getRecords()
{
	return ModelBase::getTRecords<UsuarioRecordBase>();
}

RecordBase *UsuarioModelBase::getNewRecord()
{
	UsuarioRecordBase *r = new UsuarioRecordBase(this,NULL,DB);
	connect( r,SIGNAL(hasValuesWithOutSave(bool,RecordBase*)),
			this, SLOT(record_hasRecordsWithOutSave(bool,RecordBase*)));
	return r;
}


	


