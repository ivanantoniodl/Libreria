#include "maquinamodelbase.h"

MaquinaRecordConfigureQueryBase::MaquinaRecordConfigureQueryBase(RecordConfigureQueryBase *rparent):
	RecordConfigureQueryBase(rparent)
{
	lstTables.prepend("Maquina");
	RLUGAR_ = NULL;


	
}

void MaquinaRecordConfigureQueryBase::idMaquina()
{
	addAttributeToQuery("idMaquina");
}

void MaquinaRecordConfigureQueryBase::Ip()
{
	addAttributeToQuery("Ip");
}

void MaquinaRecordConfigureQueryBase::Lugar_idLugar()
{
	addAttributeToQuery("Lugar_idLugar");
}



//!Establece todos los atributos para la consulta.
void MaquinaRecordConfigureQueryBase::allAttributes()
{
	MaquinaRecordBase r;
	foreach( QString att, r.getAttributesList() )
		addAttributeToQuery(att);
}

LugarRecordConfigureQueryBase *MaquinaRecordConfigureQueryBase::RLugar_()
{
	if ( RLUGAR_ == NULL )
		RLUGAR_ = new LugarRecordConfigureQueryBase(this);
	return RLUGAR_;
}



//MaquinaRecordConfigureQuery
//********************************************************************************

MaquinaRecordConfigureQuery::MaquinaRecordConfigureQuery(QString TableName,
						 RecordConfigureQueryBase* rparent):
	TSqlGenerator(TableName),MaquinaRecordConfigureQueryBase(rparent)
{}

void MaquinaRecordConfigureQuery::lstAttributesToQueryReady(QString c)
{
	addAttributeToSelect(&rb,c);
}

//MaquinaModelBase
//********************************************************************************

/*! Contruye MaquinaModelBase
    Se conectan las señales del registro por defecto para que cuando este configure consultas el modelo lo pueda realizar.
\param parent Padre del modelo.
*/
MaquinaModelBase::MaquinaModelBase(QObject *parent,
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
void MaquinaModelBase::addSelectQueryToRecords(QSqlQuery query)
{
	query.first();

	//no se cuenta el ultimo ya que ese es solo para saber si hay mas datos a consultar
	for ( int c=0; c<actualQuerySize-( actualQuerySize==(limit+1)?1:0 ); c++ )
	{
		int pos=0;
		MaquinaRecordBase *p=new MaquinaRecordBase(this,NULL,DB);
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

void MaquinaModelBase::configureInternalSelectQuery()
{
	r.allAttributes();
}

/*! Devuelve el registro por defecto del modelo.
\return Record por defecto del modelo.
*/
RecordBase *MaquinaModelBase::defaultRecordBase() { return &ra; }

TSqlGenerator *MaquinaModelBase::tsqlGenerator() { return &r; }

/*! Devuelve el registro por defecto para generar código SQL de la consulta.
\return MaquinaRecord por defecto del modelo.
*/
MaquinaRecordConfigureQuery *MaquinaModelBase::configureQuery()
{
	fastConfiguration=true;
	return &r;
}

MaquinaModelBase *MaquinaModelBase::getModelRecords(QList<int> lstIndexes)
{
	if ( modelSelectedRecords != NULL )
		delete modelSelectedRecords;

	modelSelectedRecords = new MaquinaModelBase(Parent,DB);
	foreach ( int i, lstIndexes )
	{
		if ( i < lstRecord.size() )
			modelSelectedRecords->lstRecord.append( getRecord( i ) );
	}

	return modelSelectedRecords;
}

QList<MaquinaRecordBase*> MaquinaModelBase::getRecords()
{
	return ModelBase::getTRecords<MaquinaRecordBase>();
}

RecordBase *MaquinaModelBase::getNewRecord()
{
	MaquinaRecordBase *r = new MaquinaRecordBase(this,NULL,DB);
	connect( r,SIGNAL(hasValuesWithOutSave(bool,RecordBase*)),
			this, SLOT(record_hasRecordsWithOutSave(bool,RecordBase*)));
	return r;
}


	


