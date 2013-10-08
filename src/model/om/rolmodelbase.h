#ifndef ROLMODELBASE_H
#define ROLMODELBASE_H

#include "modelbase.h"
#include "recordconfigurequerybase.h"
#include "rolrecordbase.h"





class QANTMVSHARED_EXPORT RolRecordConfigureQueryBase : public RecordConfigureQueryBase
{
friend class RolModelBase;
private:
	

protected:
	RolRecordBase rb;
	
public:
	RolRecordConfigureQueryBase(RecordConfigureQueryBase *rparent=NULL);
	//para ser usadas por el modelo o el q lo necesite

	void idRol();
void Rol();


void allAttributes();

	
};

class QANTMVSHARED_EXPORT RolRecordConfigureQuery : public TSqlGenerator, public RolRecordConfigureQueryBase
{
protected:
	void lstAttributesToQueryReady(QString);
public:
	RolRecordConfigureQuery(QString TableName=QString(),
							 RecordConfigureQueryBase* rparent=NULL);
};


    
/*!
  Modelo base de la tabla Rol.

  No editar esta clase.

  Para mayor información ver ModelBase.
*/

class QANTMVSHARED_EXPORT RolModelBase : public ModelBase
{
Q_OBJECT
private:
	RolModelBase *modelSelectedRecords;
protected:
	RolRecordConfigureQuery r;
	RolRecordBase ra;
	

	void addSelectQueryToRecords(QSqlQuery) ;
	void configureInternalSelectQuery();
	RecordBase *defaultRecordBase();

	TSqlGenerator *tsqlGenerator();
public:
	RolModelBase(QObject *parent=NULL,
				  QSqlDatabase db = QSqlDatabase::database());
	RolRecordConfigureQuery *configureQuery();
	RolModelBase *getModelRecords(QList<int> lstIndexes);
	QList<RolRecordBase*> getRecords();

	RecordBase *getNewRecord();
	
	
	
	
};

#endif // ROLMODELBASE_H
