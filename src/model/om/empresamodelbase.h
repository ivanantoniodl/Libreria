#ifndef EMPRESAMODELBASE_H
#define EMPRESAMODELBASE_H

#include "modelbase.h"
#include "recordconfigurequerybase.h"
#include "empresarecordbase.h"





class QANTMVSHARED_EXPORT EmpresaRecordConfigureQueryBase : public RecordConfigureQueryBase
{
friend class EmpresaModelBase;
private:
	

protected:
	EmpresaRecordBase rb;
	
public:
	EmpresaRecordConfigureQueryBase(RecordConfigureQueryBase *rparent=NULL);
	//para ser usadas por el modelo o el q lo necesite

	void idEmpresa();
void Nombre();


void allAttributes();

	
};

class QANTMVSHARED_EXPORT EmpresaRecordConfigureQuery : public TSqlGenerator, public EmpresaRecordConfigureQueryBase
{
protected:
	void lstAttributesToQueryReady(QString);
public:
	EmpresaRecordConfigureQuery(QString TableName=QString(),
							 RecordConfigureQueryBase* rparent=NULL);
};


    
/*!
  Modelo base de la tabla Empresa.

  No editar esta clase.

  Para mayor información ver ModelBase.
*/

class QANTMVSHARED_EXPORT EmpresaModelBase : public ModelBase
{
Q_OBJECT
private:
	EmpresaModelBase *modelSelectedRecords;
protected:
	EmpresaRecordConfigureQuery r;
	EmpresaRecordBase ra;
	

	void addSelectQueryToRecords(QSqlQuery) ;
	void configureInternalSelectQuery();
	RecordBase *defaultRecordBase();

	TSqlGenerator *tsqlGenerator();
public:
	EmpresaModelBase(QObject *parent=NULL,
				  QSqlDatabase db = QSqlDatabase::database());
	EmpresaRecordConfigureQuery *configureQuery();
	EmpresaModelBase *getModelRecords(QList<int> lstIndexes);
	QList<EmpresaRecordBase*> getRecords();

	RecordBase *getNewRecord();
	
	
	
	
};

#endif // EMPRESAMODELBASE_H
