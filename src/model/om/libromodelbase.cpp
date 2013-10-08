#include "libromodelbase.h"

LibroRecordConfigureQueryBase::LibroRecordConfigureQueryBase(RecordConfigureQueryBase *rparent):
	RecordConfigureQueryBase(rparent)
{
	lstTables.prepend("Libro");
	

	
}

void LibroRecordConfigureQueryBase::id()
{
	addAttributeToQuery("id");
}

void LibroRecordConfigureQueryBase::Nombre()
{
	addAttributeToQuery("Nombre");
}

void LibroRecordConfigureQueryBase::AnioImp()
{
	addAttributeToQuery("AnioImp");
}



//!Establece todos los atributos para la consulta.
void LibroRecordConfigureQueryBase::allAttributes()
{
	LibroRecordBase r;
	foreach( QString att, r.getAttributesList() )
		addAttributeToQuery(att);
}



//LibroRecordConfigureQuery
//********************************************************************************

LibroRecordConfigureQuery::LibroRecordConfigureQuery(QString TableName,
						 RecordConfigureQueryBase* rparent):
	TSqlGenerator(TableName),LibroRecordConfigureQueryBase(rparent)
{}

void LibroRecordConfigureQuery::lstAttributesToQueryReady(QString c)
{
	addAttributeToSelect(&rb,c);
}

//LibroModelBase
//********************************************************************************

/*! Contruye LibroModelBase
    Se conectan las señales del registro por defecto para que cuando este configure consultas el modelo lo pueda realizar.
\param parent Padre del modelo.
*/
LibroModelBase::LibroModelBase(QObject *parent,
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
void LibroModelBase::addSelectQueryToRecords(QSqlQuery query)
{
	query.first();

	//no se cuenta el ultimo ya que ese es solo para saber si hay mas datos a consultar
	for ( int c=0; c<actualQuerySize-( actualQuerySize==(limit+1)?1:0 ); c++ )
	{
		int pos=0;
		LibroRecordBase *p=new LibroRecordBase(this,NULL,DB);
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

void LibroModelBase::configureInternalSelectQuery()
{
	r.allAttributes();
}

/*! Devuelve el registro por defecto del modelo.
\return Record por defecto del modelo.
*/
RecordBase *LibroModelBase::defaultRecordBase() { return &ra; }

TSqlGenerator *LibroModelBase::tsqlGenerator() { return &r; }

/*! Devuelve el registro por defecto para generar código SQL de la consulta.
\return LibroRecord por defecto del modelo.
*/
LibroRecordConfigureQuery *LibroModelBase::configureQuery()
{
	fastConfiguration=true;
	return &r;
}

LibroModelBase *LibroModelBase::getModelRecords(QList<int> lstIndexes)
{
	if ( modelSelectedRecords != NULL )
		delete modelSelectedRecords;

	modelSelectedRecords = new LibroModelBase(Parent,DB);
	foreach ( int i, lstIndexes )
	{
		if ( i < lstRecord.size() )
			modelSelectedRecords->lstRecord.append( getRecord( i ) );
	}

	return modelSelectedRecords;
}

QList<LibroRecordBase*> LibroModelBase::getRecords()
{
	return ModelBase::getTRecords<LibroRecordBase>();
}

RecordBase *LibroModelBase::getNewRecord()
{
	LibroRecordBase *r = new LibroRecordBase(this,NULL,DB);
	connect( r,SIGNAL(hasValuesWithOutSave(bool,RecordBase*)),
			this, SLOT(record_hasRecordsWithOutSave(bool,RecordBase*)));
	return r;
}


	


