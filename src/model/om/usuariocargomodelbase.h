#ifndef USUARIOCARGOMODELBASE_H
#define USUARIOCARGOMODELBASE_H

#include "modelbase.h"
#include "recordconfigurequerybase.h"
#include "usuariocargorecordbase.h"





class QANTMVSHARED_EXPORT UsuarioCargoRecordConfigureQueryBase : public RecordConfigureQueryBase
{
friend class UsuarioCargoModelBase;
private:
	

protected:
	UsuarioCargoRecordBase rb;
	
public:
	UsuarioCargoRecordConfigureQueryBase(RecordConfigureQueryBase *rparent=NULL);
	//para ser usadas por el modelo o el q lo necesite

	void idUsuarioCargo();
void Cargo();


void allAttributes();

	
};

class QANTMVSHARED_EXPORT UsuarioCargoRecordConfigureQuery : public TSqlGenerator, public UsuarioCargoRecordConfigureQueryBase
{
protected:
	void lstAttributesToQueryReady(QString);
public:
	UsuarioCargoRecordConfigureQuery(QString TableName=QString(),
							 RecordConfigureQueryBase* rparent=NULL);
};


    
/*!
  Modelo base de la tabla UsuarioCargo.

  No editar esta clase.

  Para mayor información ver ModelBase.
*/

class QANTMVSHARED_EXPORT UsuarioCargoModelBase : public ModelBase
{
Q_OBJECT
private:
	UsuarioCargoModelBase *modelSelectedRecords;
protected:
	UsuarioCargoRecordConfigureQuery r;
	UsuarioCargoRecordBase ra;
	

	void addSelectQueryToRecords(QSqlQuery) ;
	void configureInternalSelectQuery();
	RecordBase *defaultRecordBase();

	TSqlGenerator *tsqlGenerator();
public:
	UsuarioCargoModelBase(QObject *parent=NULL,
				  QSqlDatabase db = QSqlDatabase::database());
	UsuarioCargoRecordConfigureQuery *configureQuery();
	UsuarioCargoModelBase *getModelRecords(QList<int> lstIndexes);
	QList<UsuarioCargoRecordBase*> getRecords();

	RecordBase *getNewRecord();
	
	
	
	
};

#endif // USUARIOCARGOMODELBASE_H
