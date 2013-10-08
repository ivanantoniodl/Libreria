#ifndef EDITORIALLIBRORECORDBASE_H
#define EDITORIALLIBRORECORDBASE_H

#include "recordbase.h"
#include "tsqlgenerator.h"

#include "editorialrecordbase.h"
#include "librorecordbase.h"




/*!
  Record base de la tabla EditorialLibro.

  No editar esta clase.

  Para mayor información ver Record.
*/



class QANTMVSHARED_EXPORT EditorialLibroRecordBase :  public RecordSimpleBase
{

	Q_OBJECT
	/*!Esta propiedad representa el atributo de la llave primaria.
<b>Funciones de acceso:</b>
\code
int id()
void setId(int id)
\endcode
*/
Q_PROPERTY(int id READ id WRITE setId)
/*!Esta propiedad representa el atributo id.
<b>Funciones de acceso:</b>
\code
int id()
void setId(int id)
\endcode
*/
Q_PROPERTY(int id READ id WRITE setId)
/*!Esta propiedad representa el atributo id.
<b>Funciones de acceso:</b>
\code
int id()
void setId(int id)
\endcode
*/
Q_PROPERTY(int id READ id WRITE setId)
/*!Esta propiedad representa el atributo Editorial_id.
<b>Funciones de acceso:</b>
\code
int Editorial_id()
void setEditorial_id(int Editorial_id)
\endcode
*/
Q_PROPERTY(int Editorial_id READ Editorial_id WRITE setEditorial_id)
/*!Esta propiedad representa el atributo Libro_id.
<b>Funciones de acceso:</b>
\code
int Libro_id()
void setLibro_id(int Libro_id)
\endcode
*/
Q_PROPERTY(int Libro_id READ Libro_id WRITE setLibro_id)


	/*!Esta propiedad representa el registro del atributo Editorial_id.
<b>Funciones de acceso:</b>
\code
EditorialRecordBase *REditorial_id()
void setPREditorial(RecordBase* record)
\endcode
*/
Q_PROPERTY(RecordBase* REditorial_ READ REditorial_ WRITE setPREditorial_)

/*!Esta propiedad representa el registro del atributo Libro_id.
<b>Funciones de acceso:</b>
\code
LibroRecordBase *RLibro_id()
void setPRLibro(RecordBase* record)
\endcode
*/
Q_PROPERTY(RecordBase* RLibro_ READ RLibro_ WRITE setPRLibro_)


	
	Q_PROPERTY(QStringList EditorialFAttributes READ EditorialFAttributes)
Q_PROPERTY(QStringList LibroFAttributes READ LibroFAttributes)

	
	Q_PROPERTY(QStringList EditorialLibroAttributesList READ EditorialLibroAttributesList)
Q_PROPERTY(QStringList EditorialLibroPKAttributesList READ EditorialLibroPKAttributesList)
Q_PROPERTY(QStringList EditorialLibroDateTimeAttributesList READ EditorialLibroDateTimeAttributesList)
Q_PROPERTY(QString EditorialLibroPKAutoIncrementAttribute READ EditorialLibroPKAutoIncrementAttribute)

private:
	//record
	int ID;//!<Atributo id
int EDITORIAL_ID;//!<Atributo Editorial_id
int LIBRO_ID;//!<Atributo Libro_id

	EditorialRecordBase *REDITORIAL_;//!<Registro Editorial_
LibroRecordBase *RLIBRO_;//!<Registro Libro_


	EditorialLibroRecordBase *BACKUPRECORD;

	QStringList EDITORIALLIBROATTRIBUTESLIST;
	QStringList EDITORIALLIBROPKATTRIBUTESLIST;
	QStringList EDITORIALLIBRODATETIMEATTRIBUTESLIST;
	QString EDITORIALLIBROPKAUTOINCREMENTATTRIBUTE;

	RecordBase *getBackUpRecord();

protected:
	
  
	void init();
	void initValues();
	EditorialLibroRecordBase(bool conf,
				   QObject *qparent=NULL,
				   RecordBase *rparent=NULL,
				   QSqlDatabase db = QSqlDatabase::database());
	void setRecordEnabledBackup(bool enabled);

public:
	EditorialLibroRecordBase(QObject *qparent=NULL,
				  RecordBase *rparent=NULL,
				  QSqlDatabase db = QSqlDatabase::database());
	EditorialLibroRecordBase(const EditorialLibroRecordBase &other);
	~EditorialLibroRecordBase();

	

	//set nuevo valor para un campo
	/*! Establece el valor del atributo id
\param id Valor del atributo
*/
void setId(int id);
/*! Establece el valor del atributo Editorial_id
\param Editorial_id Valor del atributo
*/
void setEditorial_id(int Editorial_id);
/*! Establece el valor del atributo Libro_id
\param Libro_id Valor del atributo
*/
void setLibro_id(int Libro_id);

	/*! Establece el registro del atributo Editorial_
\param editorialRecordBase Registro
*/
void setREditorial_(EditorialRecordBase* EditorialRecordBase);
/*! Establece el registro del atributo Editorial, utilizado por Q_PROPERTY.
\param record Registro
*/
void setPREditorial_(RecordBase* record);
/*! Establece el registro del atributo Libro_
\param libroRecordBase Registro
*/
void setRLibro_(LibroRecordBase* LibroRecordBase);
/*! Establece el registro del atributo Libro, utilizado por Q_PROPERTY.
\param record Registro
*/
void setPRLibro_(RecordBase* record);


	//get de los campos
	/*! Devuelve el valor del atributo id
\return Valor del atributo
*/
int id();
/*! Devuelve el valor del atributo Editorial_id
\return Valor del atributo
*/
int Editorial_id();
/*! Devuelve el valor del atributo Libro_id
\return Valor del atributo
*/
int Libro_id();

	/*! Devuelve el registro del atributo Editorial, utilizado por Q_PROPERTY.
\return Registro
*/
EditorialRecordBase *REditorial_();
/*! Devuelve el registro del atributo Libro, utilizado por Q_PROPERTY.
\return Registro
*/
LibroRecordBase *RLibro_();


	void clear();
	void revert();

	/*! Devuelve la propiedad del atributo id.
\return Nombre de la propiedad.
*/
static QString idProperty();
/*! Devuelve la propiedad del atributo Editorial_id.
\return Nombre de la propiedad.
*/
static QString Editorial_idProperty();
/*! Devuelve la propiedad del atributo Libro_id.
\return Nombre de la propiedad.
*/
static QString Libro_idProperty();

	
	QStringList EditorialLibroAttributesList();
QStringList EditorialLibroPKAttributesList();
QStringList EditorialLibroDateTimeAttributesList();
QString EditorialLibroPKAutoIncrementAttribute();

QStringList getAttributesList();
QStringList getPKAttributesList();
QStringList getPKAutoIncrementAttributesList();
QStringList getDateTimeAttributesList();

	QStringList EditorialFAttributes();
QStringList LibroFAttributes();


	RecordBase *getLastChildDefaultRecord();
	
	
	
	
	
	EditorialLibroRecordBase& operator=(const EditorialLibroRecordBase&);
};



Q_DECLARE_METATYPE(EditorialLibroRecordBase*)

#endif // EDITORIALLIBRORECORDBASE_H
