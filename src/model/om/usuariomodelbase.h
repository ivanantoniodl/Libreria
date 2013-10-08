#ifndef USUARIOMODELBASE_H
#define USUARIOMODELBASE_H

#include "modelbase.h"
#include "recordconfigurequerybase.h"
#include "usuariorecordbase.h"

#include "empresamodelbase.h"
#include "rolmodelbase.h"
#include "usuariocargomodelbase.h"




class QANTMVSHARED_EXPORT UsuarioRecordConfigureQueryBase : public RecordConfigureQueryBase
{
friend class UsuarioModelBase;
private:
	EmpresaRecordConfigureQueryBase *REMPRESA_;
RolRecordConfigureQueryBase *RROL_;
UsuarioCargoRecordConfigureQueryBase *RUSUARIOCARGO_;


protected:
	UsuarioRecordBase rb;
	
public:
	UsuarioRecordConfigureQueryBase(RecordConfigureQueryBase *rparent=NULL);
	//para ser usadas por el modelo o el q lo necesite

	void idUsuario();
void Empresa_idEmpresa();
void Rol_idRol();
void UsuarioCargo_idUsuarioCargo();
void Nombres();
void Apellidos();
void Usuario();
void FechaHora();
void Turno();


void allAttributes();

	EmpresaRecordConfigureQueryBase *REmpresa_();
RolRecordConfigureQueryBase *RRol_();
UsuarioCargoRecordConfigureQueryBase *RUsuarioCargo_();

};

class QANTMVSHARED_EXPORT UsuarioRecordConfigureQuery : public TSqlGenerator, public UsuarioRecordConfigureQueryBase
{
protected:
	void lstAttributesToQueryReady(QString);
public:
	UsuarioRecordConfigureQuery(QString TableName=QString(),
							 RecordConfigureQueryBase* rparent=NULL);
};


    
/*!
  Modelo base de la tabla Usuario.

  No editar esta clase.

  Para mayor información ver ModelBase.
*/

class QANTMVSHARED_EXPORT UsuarioModelBase : public ModelBase
{
Q_OBJECT
private:
	UsuarioModelBase *modelSelectedRecords;
protected:
	UsuarioRecordConfigureQuery r;
	UsuarioRecordBase ra;
	

	void addSelectQueryToRecords(QSqlQuery) ;
	void configureInternalSelectQuery();
	RecordBase *defaultRecordBase();

	TSqlGenerator *tsqlGenerator();
public:
	UsuarioModelBase(QObject *parent=NULL,
				  QSqlDatabase db = QSqlDatabase::database());
	UsuarioRecordConfigureQuery *configureQuery();
	UsuarioModelBase *getModelRecords(QList<int> lstIndexes);
	QList<UsuarioRecordBase*> getRecords();

	RecordBase *getNewRecord();
	
	
	
	
};

#endif // USUARIOMODELBASE_H
