#ifndef LUGARMODELBASE_H
#define LUGARMODELBASE_H

#include "modelbase.h"
#include "recordconfigurequerybase.h"
#include "lugarrecordbase.h"

#include "empresamodelbase.h"
#include "lugartipomodelbase.h"




class QANTMVSHARED_EXPORT LugarRecordConfigureQueryBase : public RecordConfigureQueryBase
{
friend class LugarModelBase;
private:
	EmpresaRecordConfigureQueryBase *REMPRESA_;
LugarTipoRecordConfigureQueryBase *RLUGARTIPO_;


protected:
	LugarRecordBase rb;
	
public:
	LugarRecordConfigureQueryBase(RecordConfigureQueryBase *rparent=NULL);
	//para ser usadas por el modelo o el q lo necesite

	void idLugar();
void Empresa_idEmpresa();
void LugarTipo_idLugarTipo();
void Nombre();
void Direccion();
void Telefono();
void NumPlaca();


void allAttributes();

	EmpresaRecordConfigureQueryBase *REmpresa_();
LugarTipoRecordConfigureQueryBase *RLugarTipo_();

};

class QANTMVSHARED_EXPORT LugarRecordConfigureQuery : public TSqlGenerator, public LugarRecordConfigureQueryBase
{
protected:
	void lstAttributesToQueryReady(QString);
public:
	LugarRecordConfigureQuery(QString TableName=QString(),
							 RecordConfigureQueryBase* rparent=NULL);
};


    
/*!
  Modelo base de la tabla Lugar.

  No editar esta clase.

  Para mayor información ver ModelBase.
*/

class QANTMVSHARED_EXPORT LugarModelBase : public ModelBase
{
Q_OBJECT
private:
	LugarModelBase *modelSelectedRecords;
protected:
	LugarRecordConfigureQuery r;
	LugarRecordBase ra;
	

	void addSelectQueryToRecords(QSqlQuery) ;
	void configureInternalSelectQuery();
	RecordBase *defaultRecordBase();

	TSqlGenerator *tsqlGenerator();
public:
	LugarModelBase(QObject *parent=NULL,
				  QSqlDatabase db = QSqlDatabase::database());
	LugarRecordConfigureQuery *configureQuery();
	LugarModelBase *getModelRecords(QList<int> lstIndexes);
	QList<LugarRecordBase*> getRecords();

	RecordBase *getNewRecord();
	
	
	
	
};

#endif // LUGARMODELBASE_H
