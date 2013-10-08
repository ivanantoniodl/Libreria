#ifndef MAQUINAMODELBASE_H
#define MAQUINAMODELBASE_H

#include "modelbase.h"
#include "recordconfigurequerybase.h"
#include "maquinarecordbase.h"
#include "lugarmodelbase.h"




class QANTMVSHARED_EXPORT MaquinaRecordConfigureQueryBase : public RecordConfigureQueryBase
{
friend class MaquinaModelBase;
private:
	LugarRecordConfigureQueryBase *RLUGAR_;


protected:
	MaquinaRecordBase rb;
	
public:
	MaquinaRecordConfigureQueryBase(RecordConfigureQueryBase *rparent=NULL);
	//para ser usadas por el modelo o el q lo necesite

	void idMaquina();
void Ip();
void Lugar_idLugar();


void allAttributes();

	LugarRecordConfigureQueryBase *RLugar_();

};

class QANTMVSHARED_EXPORT MaquinaRecordConfigureQuery : public TSqlGenerator, public MaquinaRecordConfigureQueryBase
{
protected:
	void lstAttributesToQueryReady(QString);
public:
	MaquinaRecordConfigureQuery(QString TableName=QString(),
							 RecordConfigureQueryBase* rparent=NULL);
};


    
/*!
  Modelo base de la tabla Maquina.

  No editar esta clase.

  Para mayor información ver ModelBase.
*/

class QANTMVSHARED_EXPORT MaquinaModelBase : public ModelBase
{
Q_OBJECT
private:
	MaquinaModelBase *modelSelectedRecords;
protected:
	MaquinaRecordConfigureQuery r;
	MaquinaRecordBase ra;
	

	void addSelectQueryToRecords(QSqlQuery) ;
	void configureInternalSelectQuery();
	RecordBase *defaultRecordBase();

	TSqlGenerator *tsqlGenerator();
public:
	MaquinaModelBase(QObject *parent=NULL,
				  QSqlDatabase db = QSqlDatabase::database());
	MaquinaRecordConfigureQuery *configureQuery();
	MaquinaModelBase *getModelRecords(QList<int> lstIndexes);
	QList<MaquinaRecordBase*> getRecords();

	RecordBase *getNewRecord();
	
	
	
	
};

#endif // MAQUINAMODELBASE_H
