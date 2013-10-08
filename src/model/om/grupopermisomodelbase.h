#ifndef GRUPOPERMISOMODELBASE_H
#define GRUPOPERMISOMODELBASE_H

#include "modelbase.h"
#include "recordconfigurequerybase.h"
#include "grupopermisorecordbase.h"





class QANTMVSHARED_EXPORT GrupoPermisoRecordConfigureQueryBase : public RecordConfigureQueryBase
{
friend class GrupoPermisoModelBase;
private:
	

protected:
	GrupoPermisoRecordBase rb;
	
public:
	GrupoPermisoRecordConfigureQueryBase(RecordConfigureQueryBase *rparent=NULL);
	//para ser usadas por el modelo o el q lo necesite

	void idGrupoPermiso();
void Nombre();


void allAttributes();

	
};

class QANTMVSHARED_EXPORT GrupoPermisoRecordConfigureQuery : public TSqlGenerator, public GrupoPermisoRecordConfigureQueryBase
{
protected:
	void lstAttributesToQueryReady(QString);
public:
	GrupoPermisoRecordConfigureQuery(QString TableName=QString(),
							 RecordConfigureQueryBase* rparent=NULL);
};


    
/*!
  Modelo base de la tabla GrupoPermiso.

  No editar esta clase.

  Para mayor información ver ModelBase.
*/

class QANTMVSHARED_EXPORT GrupoPermisoModelBase : public ModelBase
{
Q_OBJECT
private:
	GrupoPermisoModelBase *modelSelectedRecords;
protected:
	GrupoPermisoRecordConfigureQuery r;
	GrupoPermisoRecordBase ra;
	

	void addSelectQueryToRecords(QSqlQuery) ;
	void configureInternalSelectQuery();
	RecordBase *defaultRecordBase();

	TSqlGenerator *tsqlGenerator();
public:
	GrupoPermisoModelBase(QObject *parent=NULL,
				  QSqlDatabase db = QSqlDatabase::database());
	GrupoPermisoRecordConfigureQuery *configureQuery();
	GrupoPermisoModelBase *getModelRecords(QList<int> lstIndexes);
	QList<GrupoPermisoRecordBase*> getRecords();

	RecordBase *getNewRecord();
	
	
	
	
};

#endif // GRUPOPERMISOMODELBASE_H
