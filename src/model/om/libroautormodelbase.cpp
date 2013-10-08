#include "libroautormodelbase.h"

LibroAutorRecordConfigureQueryBase::LibroAutorRecordConfigureQueryBase(RecordConfigureQueryBase *rparent):
	RecordConfigureQueryBase(rparent)
{
	lstTables.prepend("LibroAutor");
	RLIBRO_ = NULL;
RAUTOR_ = NULL;


	
}

void LibroAutorRecordConfigureQueryBase::id()
{
	addAttributeToQuery("id");
}

void LibroAutorRecordConfigureQueryBase::Libro_id()
{
	addAttributeToQuery("Libro_id");
}

void LibroAutorRecordConfigureQueryBase::Autor_id()
{
	addAttributeToQuery("Autor_id");
}



//!Establece todos los atributos para la consulta.
void LibroAutorRecordConfigureQueryBase::allAttributes()
{
	LibroAutorRecordBase r;
	foreach( QString att, r.getAttributesList() )
		addAttributeToQuery(att);
}

LibroRecordConfigureQueryBase *LibroAutorRecordConfigureQueryBase::RLibro_()
{
	if ( RLIBRO_ == NULL )
		RLIBRO_ = new LibroRecordConfigureQueryBase(this);
	return RLIBRO_;
}

AutorRecordConfigureQueryBase *LibroAutorRecordConfigureQueryBase::RAutor_()
{
	if ( RAUTOR_ == NULL )
		RAUTOR_ = new AutorRecordConfigureQueryBase(this);
	return RAUTOR_;
}



//LibroAutorRecordConfigureQuery
//********************************************************************************

LibroAutorRecordConfigureQuery::LibroAutorRecordConfigureQuery(QString TableName,
						 RecordConfigureQueryBase* rparent):
	TSqlGenerator(TableName),LibroAutorRecordConfigureQueryBase(rparent)
{}

void LibroAutorRecordConfigureQuery::lstAttributesToQueryReady(QString c)
{
	addAttributeToSelect(&rb,c);
}

//LibroAutorModelBase
//********************************************************************************

/*! Contruye LibroAutorModelBase
    Se conectan las señales del registro por defecto para que cuando este configure consultas el modelo lo pueda realizar.
\param parent Padre del modelo.
*/
LibroAutorModelBase::LibroAutorModelBase(QObject *parent,
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
void LibroAutorModelBase::addSelectQueryToRecords(QSqlQuery query)
{
	query.first();

	//no se cuenta el ultimo ya que ese es solo para saber si hay mas datos a consultar
	for ( int c=0; c<actualQuerySize-( actualQuerySize==(limit+1)?1:0 ); c++ )
	{
		int pos=0;
		LibroAutorRecordBase *p=new LibroAutorRecordBase(this,NULL,DB);
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

void LibroAutorModelBase::configureInternalSelectQuery()
{
	r.allAttributes();
}

/*! Devuelve el registro por defecto del modelo.
\return Record por defecto del modelo.
*/
RecordBase *LibroAutorModelBase::defaultRecordBase() { return &ra; }

TSqlGenerator *LibroAutorModelBase::tsqlGenerator() { return &r; }

/*! Devuelve el registro por defecto para generar código SQL de la consulta.
\return LibroAutorRecord por defecto del modelo.
*/
LibroAutorRecordConfigureQuery *LibroAutorModelBase::configureQuery()
{
	fastConfiguration=true;
	return &r;
}

LibroAutorModelBase *LibroAutorModelBase::getModelRecords(QList<int> lstIndexes)
{
	if ( modelSelectedRecords != NULL )
		delete modelSelectedRecords;

	modelSelectedRecords = new LibroAutorModelBase(Parent,DB);
	foreach ( int i, lstIndexes )
	{
		if ( i < lstRecord.size() )
			modelSelectedRecords->lstRecord.append( getRecord( i ) );
	}

	return modelSelectedRecords;
}

QList<LibroAutorRecordBase*> LibroAutorModelBase::getRecords()
{
	return ModelBase::getTRecords<LibroAutorRecordBase>();
}

RecordBase *LibroAutorModelBase::getNewRecord()
{
	LibroAutorRecordBase *r = new LibroAutorRecordBase(this,NULL,DB);
	connect( r,SIGNAL(hasValuesWithOutSave(bool,RecordBase*)),
			this, SLOT(record_hasRecordsWithOutSave(bool,RecordBase*)));
	return r;
}


	


