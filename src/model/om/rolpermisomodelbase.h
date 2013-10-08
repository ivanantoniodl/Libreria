#ifndef ROLPERMISOMODELBASE_H
#define ROLPERMISOMODELBASE_H

#include "modelbase.h"
#include "recordconfigurequerybase.h"
#include "rolpermisorecordbase.h"

#include "permisomodelbase.h"
#include "rolmodelbase.h"




class QANTMVSHARED_EXPORT RolPermisoRecordConfigureQueryBase : public RecordConfigureQueryBase
{
friend class RolPermisoModelBase;
private:
	PermisoRecordConfigureQueryBase *RPERMISO_;
RolRecordConfigureQueryBase *RROL_;


protected:
	RolPermisoRecordBase rb;
	
public:
	RolPermisoRecordConfigureQueryBase(RecordConfigureQueryBase *rparent=NULL);
	//para ser usadas por el modelo o el q lo necesite

	void idRolPermiso();
void Permiso_idPermiso();
void Rol_idRol();
void Permiso();


void allAttributes();

	PermisoRecordConfigureQueryBase *RPermiso_();
RolRecordConfigureQueryBase *RRol_();

};

class QANTMVSHARED_EXPORT RolPermisoRecordConfigureQuery : public TSqlGenerator, public RolPermisoRecordConfigureQueryBase
{
protected:
	void lstAttributesToQueryReady(QString);
public:
	RolPermisoRecordConfigureQuery(QString TableName=QString(),
							 RecordConfigureQueryBase* rparent=NULL);
};


    
/*!
  Modelo base de la tabla RolPermiso.

  No editar esta clase.

  Para mayor información ver ModelBase.
*/

class QANTMVSHARED_EXPORT RolPermisoModelBase : public ModelBase
{
Q_OBJECT
private:
	RolPermisoModelBase *modelSelectedRecords;
protected:
	RolPermisoRecordConfigureQuery r;
	RolPermisoRecordBase ra;
	

	void addSelectQueryToRecords(QSqlQuery) ;
	void configureInternalSelectQuery();
	RecordBase *defaultRecordBase();

	TSqlGenerator *tsqlGenerator();
public:
	RolPermisoModelBase(QObject *parent=NULL,
				  QSqlDatabase db = QSqlDatabase::database());
	RolPermisoRecordConfigureQuery *configureQuery();
	RolPermisoModelBase *getModelRecords(QList<int> lstIndexes);
	QList<RolPermisoRecordBase*> getRecords();

	RecordBase *getNewRecord();
	
	
	
	
};

#endif // ROLPERMISOMODELBASE_H
