#ifndef EDITORIALLIBROMODELBASE_H
#define EDITORIALLIBROMODELBASE_H

#include "modelbase.h"
#include "recordconfigurequerybase.h"
#include "editoriallibrorecordbase.h"

#include "editorialmodelbase.h"
#include "libromodelbase.h"




class QANTMVSHARED_EXPORT EditorialLibroRecordConfigureQueryBase : public RecordConfigureQueryBase
{
friend class EditorialLibroModelBase;
private:
	EditorialRecordConfigureQueryBase *REDITORIAL_;
LibroRecordConfigureQueryBase *RLIBRO_;


protected:
	EditorialLibroRecordBase rb;
	
public:
	EditorialLibroRecordConfigureQueryBase(RecordConfigureQueryBase *rparent=NULL);
	//para ser usadas por el modelo o el q lo necesite

	void id();
void Editorial_id();
void Libro_id();


void allAttributes();

	EditorialRecordConfigureQueryBase *REditorial_();
LibroRecordConfigureQueryBase *RLibro_();

};

class QANTMVSHARED_EXPORT EditorialLibroRecordConfigureQuery : public TSqlGenerator, public EditorialLibroRecordConfigureQueryBase
{
protected:
	void lstAttributesToQueryReady(QString);
public:
	EditorialLibroRecordConfigureQuery(QString TableName=QString(),
							 RecordConfigureQueryBase* rparent=NULL);
};


    
/*!
  Modelo base de la tabla EditorialLibro.

  No editar esta clase.

  Para mayor información ver ModelBase.
*/

class QANTMVSHARED_EXPORT EditorialLibroModelBase : public ModelBase
{
Q_OBJECT
private:
	EditorialLibroModelBase *modelSelectedRecords;
protected:
	EditorialLibroRecordConfigureQuery r;
	EditorialLibroRecordBase ra;
	

	void addSelectQueryToRecords(QSqlQuery) ;
	void configureInternalSelectQuery();
	RecordBase *defaultRecordBase();

	TSqlGenerator *tsqlGenerator();
public:
	EditorialLibroModelBase(QObject *parent=NULL,
				  QSqlDatabase db = QSqlDatabase::database());
	EditorialLibroRecordConfigureQuery *configureQuery();
	EditorialLibroModelBase *getModelRecords(QList<int> lstIndexes);
	QList<EditorialLibroRecordBase*> getRecords();

	RecordBase *getNewRecord();
	
	
	
	
};

#endif // EDITORIALLIBROMODELBASE_H
