#include "editoriallibromodelbase.h"

EditorialLibroRecordConfigureQueryBase::EditorialLibroRecordConfigureQueryBase(RecordConfigureQueryBase *rparent):
	RecordConfigureQueryBase(rparent)
{
	lstTables.prepend("EditorialLibro");
	REDITORIAL_ = NULL;
RLIBRO_ = NULL;


	
}

void EditorialLibroRecordConfigureQueryBase::id()
{
	addAttributeToQuery("id");
}

void EditorialLibroRecordConfigureQueryBase::Editorial_id()
{
	addAttributeToQuery("Editorial_id");
}

void EditorialLibroRecordConfigureQueryBase::Libro_id()
{
	addAttributeToQuery("Libro_id");
}



//!Establece todos los atributos para la consulta.
void EditorialLibroRecordConfigureQueryBase::allAttributes()
{
	EditorialLibroRecordBase r;
	foreach( QString att, r.getAttributesList() )
		addAttributeToQuery(att);
}

EditorialRecordConfigureQueryBase *EditorialLibroRecordConfigureQueryBase::REditorial_()
{
	if ( REDITORIAL_ == NULL )
		REDITORIAL_ = new EditorialRecordConfigureQueryBase(this);
	return REDITORIAL_;
}

LibroRecordConfigureQueryBase *EditorialLibroRecordConfigureQueryBase::RLibro_()
{
	if ( RLIBRO_ == NULL )
		RLIBRO_ = new LibroRecordConfigureQueryBase(this);
	return RLIBRO_;
}



//EditorialLibroRecordConfigureQuery
//********************************************************************************

EditorialLibroRecordConfigureQuery::EditorialLibroRecordConfigureQuery(QString TableName,
						 RecordConfigureQueryBase* rparent):
	TSqlGenerator(TableName),EditorialLibroRecordConfigureQueryBase(rparent)
{}

void EditorialLibroRecordConfigureQuery::lstAttributesToQueryReady(QString c)
{
	addAttributeToSelect(&rb,c);
}

//EditorialLibroModelBase
//********************************************************************************

/*! Contruye EditorialLibroModelBase
    Se conectan las señales del registro por defecto para que cuando este configure consultas el modelo lo pueda realizar.
\param parent Padre del modelo.
*/
EditorialLibroModelBase::EditorialLibroModelBase(QObject *parent,
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
void EditorialLibroModelBase::addSelectQueryToRecords(QSqlQuery query)
{
	query.first();

	//no se cuenta el ultimo ya que ese es solo para saber si hay mas datos a consultar
	for ( int c=0; c<actualQuerySize-( actualQuerySize==(limit+1)?1:0 ); c++ )
	{
		int pos=0;
		EditorialLibroRecordBase *p=new EditorialLibroRecordBase(this,NULL,DB);
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

void EditorialLibroModelBase::configureInternalSelectQuery()
{
	r.allAttributes();
}

/*! Devuelve el registro por defecto del modelo.
\return Record por defecto del modelo.
*/
RecordBase *EditorialLibroModelBase::defaultRecordBase() { return &ra; }

TSqlGenerator *EditorialLibroModelBase::tsqlGenerator() { return &r; }

/*! Devuelve el registro por defecto para generar código SQL de la consulta.
\return EditorialLibroRecord por defecto del modelo.
*/
EditorialLibroRecordConfigureQuery *EditorialLibroModelBase::configureQuery()
{
	fastConfiguration=true;
	return &r;
}

EditorialLibroModelBase *EditorialLibroModelBase::getModelRecords(QList<int> lstIndexes)
{
	if ( modelSelectedRecords != NULL )
		delete modelSelectedRecords;

	modelSelectedRecords = new EditorialLibroModelBase(Parent,DB);
	foreach ( int i, lstIndexes )
	{
		if ( i < lstRecord.size() )
			modelSelectedRecords->lstRecord.append( getRecord( i ) );
	}

	return modelSelectedRecords;
}

QList<EditorialLibroRecordBase*> EditorialLibroModelBase::getRecords()
{
	return ModelBase::getTRecords<EditorialLibroRecordBase>();
}

RecordBase *EditorialLibroModelBase::getNewRecord()
{
	EditorialLibroRecordBase *r = new EditorialLibroRecordBase(this,NULL,DB);
	connect( r,SIGNAL(hasValuesWithOutSave(bool,RecordBase*)),
			this, SLOT(record_hasRecordsWithOutSave(bool,RecordBase*)));
	return r;
}


	


