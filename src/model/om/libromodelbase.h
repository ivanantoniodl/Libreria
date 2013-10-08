#ifndef LIBROMODELBASE_H
#define LIBROMODELBASE_H

#include "modelbase.h"
#include "recordconfigurequerybase.h"
#include "librorecordbase.h"





class QANTMVSHARED_EXPORT LibroRecordConfigureQueryBase : public RecordConfigureQueryBase
{
friend class LibroModelBase;
private:
	

protected:
	LibroRecordBase rb;
	
public:
	LibroRecordConfigureQueryBase(RecordConfigureQueryBase *rparent=NULL);
	//para ser usadas por el modelo o el q lo necesite

	void id();
void Nombre();
void AnioImp();


void allAttributes();

	
};

class QANTMVSHARED_EXPORT LibroRecordConfigureQuery : public TSqlGenerator, public LibroRecordConfigureQueryBase
{
protected:
	void lstAttributesToQueryReady(QString);
public:
	LibroRecordConfigureQuery(QString TableName=QString(),
							 RecordConfigureQueryBase* rparent=NULL);
};


    
/*!
  Modelo base de la tabla Libro.

  No editar esta clase.

  Para mayor información ver ModelBase.
*/

class QANTMVSHARED_EXPORT LibroModelBase : public ModelBase
{
Q_OBJECT
private:
	LibroModelBase *modelSelectedRecords;
protected:
	LibroRecordConfigureQuery r;
	LibroRecordBase ra;
	

	void addSelectQueryToRecords(QSqlQuery) ;
	void configureInternalSelectQuery();
	RecordBase *defaultRecordBase();

	TSqlGenerator *tsqlGenerator();
public:
	LibroModelBase(QObject *parent=NULL,
				  QSqlDatabase db = QSqlDatabase::database());
	LibroRecordConfigureQuery *configureQuery();
	LibroModelBase *getModelRecords(QList<int> lstIndexes);
	QList<LibroRecordBase*> getRecords();

	RecordBase *getNewRecord();
	
	
	
	
};

#endif // LIBROMODELBASE_H
