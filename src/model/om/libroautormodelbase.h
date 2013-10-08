#ifndef LIBROAUTORMODELBASE_H
#define LIBROAUTORMODELBASE_H

#include "modelbase.h"
#include "recordconfigurequerybase.h"
#include "libroautorrecordbase.h"

#include "libromodelbase.h"
#include "autormodelbase.h"




class QANTMVSHARED_EXPORT LibroAutorRecordConfigureQueryBase : public RecordConfigureQueryBase
{
friend class LibroAutorModelBase;
private:
	LibroRecordConfigureQueryBase *RLIBRO_;
AutorRecordConfigureQueryBase *RAUTOR_;


protected:
	LibroAutorRecordBase rb;
	
public:
	LibroAutorRecordConfigureQueryBase(RecordConfigureQueryBase *rparent=NULL);
	//para ser usadas por el modelo o el q lo necesite

	void id();
void Libro_id();
void Autor_id();


void allAttributes();

	LibroRecordConfigureQueryBase *RLibro_();
AutorRecordConfigureQueryBase *RAutor_();

};

class QANTMVSHARED_EXPORT LibroAutorRecordConfigureQuery : public TSqlGenerator, public LibroAutorRecordConfigureQueryBase
{
protected:
	void lstAttributesToQueryReady(QString);
public:
	LibroAutorRecordConfigureQuery(QString TableName=QString(),
							 RecordConfigureQueryBase* rparent=NULL);
};


    
/*!
  Modelo base de la tabla LibroAutor.

  No editar esta clase.

  Para mayor información ver ModelBase.
*/

class QANTMVSHARED_EXPORT LibroAutorModelBase : public ModelBase
{
Q_OBJECT
private:
	LibroAutorModelBase *modelSelectedRecords;
protected:
	LibroAutorRecordConfigureQuery r;
	LibroAutorRecordBase ra;
	

	void addSelectQueryToRecords(QSqlQuery) ;
	void configureInternalSelectQuery();
	RecordBase *defaultRecordBase();

	TSqlGenerator *tsqlGenerator();
public:
	LibroAutorModelBase(QObject *parent=NULL,
				  QSqlDatabase db = QSqlDatabase::database());
	LibroAutorRecordConfigureQuery *configureQuery();
	LibroAutorModelBase *getModelRecords(QList<int> lstIndexes);
	QList<LibroAutorRecordBase*> getRecords();

	RecordBase *getNewRecord();
	
	
	
	
};

#endif // LIBROAUTORMODELBASE_H
