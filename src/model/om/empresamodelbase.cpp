#include "empresamodelbase.h"

EmpresaRecordConfigureQueryBase::EmpresaRecordConfigureQueryBase(RecordConfigureQueryBase *rparent):
	RecordConfigureQueryBase(rparent)
{
	lstTables.prepend("Empresa");
	

	
}

void EmpresaRecordConfigureQueryBase::idEmpresa()
{
	addAttributeToQuery("idEmpresa");
}

void EmpresaRecordConfigureQueryBase::Nombre()
{
	addAttributeToQuery("Nombre");
}



//!Establece todos los atributos para la consulta.
void EmpresaRecordConfigureQueryBase::allAttributes()
{
	EmpresaRecordBase r;
	foreach( QString att, r.getAttributesList() )
		addAttributeToQuery(att);
}



//EmpresaRecordConfigureQuery
//********************************************************************************

EmpresaRecordConfigureQuery::EmpresaRecordConfigureQuery(QString TableName,
						 RecordConfigureQueryBase* rparent):
	TSqlGenerator(TableName),EmpresaRecordConfigureQueryBase(rparent)
{}

void EmpresaRecordConfigureQuery::lstAttributesToQueryReady(QString c)
{
	addAttributeToSelect(&rb,c);
}

//EmpresaModelBase
//********************************************************************************

/*! Contruye EmpresaModelBase
    Se conectan las señales del registro por defecto para que cuando este configure consultas el modelo lo pueda realizar.
\param parent Padre del modelo.
*/
EmpresaModelBase::EmpresaModelBase(QObject *parent,
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
void EmpresaModelBase::addSelectQueryToRecords(QSqlQuery query)
{
	query.first();

	//no se cuenta el ultimo ya que ese es solo para saber si hay mas datos a consultar
	for ( int c=0; c<actualQuerySize-( actualQuerySize==(limit+1)?1:0 ); c++ )
	{
		int pos=0;
		EmpresaRecordBase *p=new EmpresaRecordBase(this,NULL,DB);
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

void EmpresaModelBase::configureInternalSelectQuery()
{
	r.allAttributes();
}

/*! Devuelve el registro por defecto del modelo.
\return Record por defecto del modelo.
*/
RecordBase *EmpresaModelBase::defaultRecordBase() { return &ra; }

TSqlGenerator *EmpresaModelBase::tsqlGenerator() { return &r; }

/*! Devuelve el registro por defecto para generar código SQL de la consulta.
\return EmpresaRecord por defecto del modelo.
*/
EmpresaRecordConfigureQuery *EmpresaModelBase::configureQuery()
{
	fastConfiguration=true;
	return &r;
}

EmpresaModelBase *EmpresaModelBase::getModelRecords(QList<int> lstIndexes)
{
	if ( modelSelectedRecords != NULL )
		delete modelSelectedRecords;

	modelSelectedRecords = new EmpresaModelBase(Parent,DB);
	foreach ( int i, lstIndexes )
	{
		if ( i < lstRecord.size() )
			modelSelectedRecords->lstRecord.append( getRecord( i ) );
	}

	return modelSelectedRecords;
}

QList<EmpresaRecordBase*> EmpresaModelBase::getRecords()
{
	return ModelBase::getTRecords<EmpresaRecordBase>();
}

RecordBase *EmpresaModelBase::getNewRecord()
{
	EmpresaRecordBase *r = new EmpresaRecordBase(this,NULL,DB);
	connect( r,SIGNAL(hasValuesWithOutSave(bool,RecordBase*)),
			this, SLOT(record_hasRecordsWithOutSave(bool,RecordBase*)));
	return r;
}


	


