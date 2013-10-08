#ifndef LUGARTIPOMODELBASE_H
#define LUGARTIPOMODELBASE_H

#include "modelbase.h"
#include "recordconfigurequerybase.h"
#include "lugartiporecordbase.h"





class QANTMVSHARED_EXPORT LugarTipoRecordConfigureQueryBase : public RecordConfigureQueryBase
{
friend class LugarTipoModelBase;
private:
	

protected:
	LugarTipoRecordBase rb;
	
public:
	LugarTipoRecordConfigureQueryBase(RecordConfigureQueryBase *rparent=NULL);
	//para ser usadas por el modelo o el q lo necesite

	void idLugarTipo();
void Tipo();


void allAttributes();

	
};

class QANTMVSHARED_EXPORT LugarTipoRecordConfigureQuery : public TSqlGenerator, public LugarTipoRecordConfigureQueryBase
{
protected:
	void lstAttributesToQueryReady(QString);
public:
	LugarTipoRecordConfigureQuery(QString TableName=QString(),
							 RecordConfigureQueryBase* rparent=NULL);
};


    
/*!
  Modelo base de la tabla LugarTipo.

  No editar esta clase.

  Para mayor información ver ModelBase.
*/

class QANTMVSHARED_EXPORT LugarTipoModelBase : public ModelBase
{
Q_OBJECT
private:
	LugarTipoModelBase *modelSelectedRecords;
protected:
	LugarTipoRecordConfigureQuery r;
	LugarTipoRecordBase ra;
	

	void addSelectQueryToRecords(QSqlQuery) ;
	void configureInternalSelectQuery();
	RecordBase *defaultRecordBase();

	TSqlGenerator *tsqlGenerator();
public:
	LugarTipoModelBase(QObject *parent=NULL,
				  QSqlDatabase db = QSqlDatabase::database());
	LugarTipoRecordConfigureQuery *configureQuery();
	LugarTipoModelBase *getModelRecords(QList<int> lstIndexes);
	QList<LugarTipoRecordBase*> getRecords();

	RecordBase *getNewRecord();
	
	
	
	
};

#endif // LUGARTIPOMODELBASE_H
