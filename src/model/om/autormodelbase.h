#ifndef AUTORMODELBASE_H
#define AUTORMODELBASE_H

#include "modelbase.h"
#include "recordconfigurequerybase.h"
#include "autorrecordbase.h"





class QANTMVSHARED_EXPORT AutorRecordConfigureQueryBase : public RecordConfigureQueryBase
{
friend class AutorModelBase;
private:
	

protected:
	AutorRecordBase rb;
	
public:
	AutorRecordConfigureQueryBase(RecordConfigureQueryBase *rparent=NULL);
	//para ser usadas por el modelo o el q lo necesite

	void id();
void Nombre();
void Direccion();


void allAttributes();

	
};

class QANTMVSHARED_EXPORT AutorRecordConfigureQuery : public TSqlGenerator, public AutorRecordConfigureQueryBase
{
protected:
	void lstAttributesToQueryReady(QString);
public:
	AutorRecordConfigureQuery(QString TableName=QString(),
							 RecordConfigureQueryBase* rparent=NULL);
};


    
/*!
  Modelo base de la tabla Autor.

  No editar esta clase.

  Para mayor información ver ModelBase.
*/

class QANTMVSHARED_EXPORT AutorModelBase : public ModelBase
{
Q_OBJECT
private:
	AutorModelBase *modelSelectedRecords;
protected:
	AutorRecordConfigureQuery r;
	AutorRecordBase ra;
	

	void addSelectQueryToRecords(QSqlQuery) ;
	void configureInternalSelectQuery();
	RecordBase *defaultRecordBase();

	TSqlGenerator *tsqlGenerator();
public:
	AutorModelBase(QObject *parent=NULL,
				  QSqlDatabase db = QSqlDatabase::database());
	AutorRecordConfigureQuery *configureQuery();
	AutorModelBase *getModelRecords(QList<int> lstIndexes);
	QList<AutorRecordBase*> getRecords();

	RecordBase *getNewRecord();
	
	
	
	
};

#endif // AUTORMODELBASE_H
