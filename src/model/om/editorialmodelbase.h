#ifndef EDITORIALMODELBASE_H
#define EDITORIALMODELBASE_H

#include "modelbase.h"
#include "recordconfigurequerybase.h"
#include "editorialrecordbase.h"





class QANTMVSHARED_EXPORT EditorialRecordConfigureQueryBase : public RecordConfigureQueryBase
{
friend class EditorialModelBase;
private:
	

protected:
	EditorialRecordBase rb;
	
public:
	EditorialRecordConfigureQueryBase(RecordConfigureQueryBase *rparent=NULL);
	//para ser usadas por el modelo o el q lo necesite

	void id();
void Nombre();
void Direccion();


void allAttributes();

	
};

class QANTMVSHARED_EXPORT EditorialRecordConfigureQuery : public TSqlGenerator, public EditorialRecordConfigureQueryBase
{
protected:
	void lstAttributesToQueryReady(QString);
public:
	EditorialRecordConfigureQuery(QString TableName=QString(),
							 RecordConfigureQueryBase* rparent=NULL);
};


    
/*!
  Modelo base de la tabla Editorial.

  No editar esta clase.

  Para mayor información ver ModelBase.
*/

class QANTMVSHARED_EXPORT EditorialModelBase : public ModelBase
{
Q_OBJECT
private:
	EditorialModelBase *modelSelectedRecords;
protected:
	EditorialRecordConfigureQuery r;
	EditorialRecordBase ra;
	

	void addSelectQueryToRecords(QSqlQuery) ;
	void configureInternalSelectQuery();
	RecordBase *defaultRecordBase();

	TSqlGenerator *tsqlGenerator();
public:
	EditorialModelBase(QObject *parent=NULL,
				  QSqlDatabase db = QSqlDatabase::database());
	EditorialRecordConfigureQuery *configureQuery();
	EditorialModelBase *getModelRecords(QList<int> lstIndexes);
	QList<EditorialRecordBase*> getRecords();

	RecordBase *getNewRecord();
	
	
	
	
};

#endif // EDITORIALMODELBASE_H
