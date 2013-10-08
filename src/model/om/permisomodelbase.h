#ifndef PERMISOMODELBASE_H
#define PERMISOMODELBASE_H

#include "modelbase.h"
#include "recordconfigurequerybase.h"
#include "permisorecordbase.h"

#include "grupopermisomodelbase.h"




class QANTMVSHARED_EXPORT PermisoRecordConfigureQueryBase : public RecordConfigureQueryBase
{
friend class PermisoModelBase;
private:
	GrupoPermisoRecordConfigureQueryBase *RGRUPOPERMISO_;


protected:
	PermisoRecordBase rb;
	
public:
	PermisoRecordConfigureQueryBase(RecordConfigureQueryBase *rparent=NULL);
	//para ser usadas por el modelo o el q lo necesite

	void idPermiso();
void GrupoPermiso_idGrupoPermiso();
void Formulario();
void Etiqueta();


void allAttributes();

	GrupoPermisoRecordConfigureQueryBase *RGrupoPermiso_();

};

class QANTMVSHARED_EXPORT PermisoRecordConfigureQuery : public TSqlGenerator, public PermisoRecordConfigureQueryBase
{
protected:
	void lstAttributesToQueryReady(QString);
public:
	PermisoRecordConfigureQuery(QString TableName=QString(),
							 RecordConfigureQueryBase* rparent=NULL);
};


    
/*!
  Modelo base de la tabla Permiso.

  No editar esta clase.

  Para mayor información ver ModelBase.
*/

class QANTMVSHARED_EXPORT PermisoModelBase : public ModelBase
{
Q_OBJECT
private:
	PermisoModelBase *modelSelectedRecords;
protected:
	PermisoRecordConfigureQuery r;
	PermisoRecordBase ra;
	

	void addSelectQueryToRecords(QSqlQuery) ;
	void configureInternalSelectQuery();
	RecordBase *defaultRecordBase();

	TSqlGenerator *tsqlGenerator();
public:
	PermisoModelBase(QObject *parent=NULL,
				  QSqlDatabase db = QSqlDatabase::database());
	PermisoRecordConfigureQuery *configureQuery();
	PermisoModelBase *getModelRecords(QList<int> lstIndexes);
	QList<PermisoRecordBase*> getRecords();

	RecordBase *getNewRecord();
	
	
	
	
};

#endif // PERMISOMODELBASE_H
