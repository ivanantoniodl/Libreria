#ifndef LIBROAUTORRECORDBASE_H
#define LIBROAUTORRECORDBASE_H

#include "recordbase.h"
#include "tsqlgenerator.h"

#include "librorecordbase.h"
#include "autorrecordbase.h"




/*!
  Record base de la tabla LibroAutor.

  No editar esta clase.

  Para mayor información ver Record.
*/



class QANTMVSHARED_EXPORT LibroAutorRecordBase :  public RecordSimpleBase
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
/*!Esta propiedad representa el atributo Libro_id.
<b>Funciones de acceso:</b>
\code
int Libro_id()
void setLibro_id(int Libro_id)
\endcode
*/
Q_PROPERTY(int Libro_id READ Libro_id WRITE setLibro_id)
/*!Esta propiedad representa el atributo Autor_id.
<b>Funciones de acceso:</b>
\code
int Autor_id()
void setAutor_id(int Autor_id)
\endcode
*/
Q_PROPERTY(int Autor_id READ Autor_id WRITE setAutor_id)


	/*!Esta propiedad representa el registro del atributo Libro_id.
<b>Funciones de acceso:</b>
\code
LibroRecordBase *RLibro_id()
void setPRLibro(RecordBase* record)
\endcode
*/
Q_PROPERTY(RecordBase* RLibro_ READ RLibro_ WRITE setPRLibro_)

/*!Esta propiedad representa el registro del atributo Autor_id.
<b>Funciones de acceso:</b>
\code
AutorRecordBase *RAutor_id()
void setPRAutor(RecordBase* record)
\endcode
*/
Q_PROPERTY(RecordBase* RAutor_ READ RAutor_ WRITE setPRAutor_)


	
	Q_PROPERTY(QStringList LibroFAttributes READ LibroFAttributes)
Q_PROPERTY(QStringList AutorFAttributes READ AutorFAttributes)

	
	Q_PROPERTY(QStringList LibroAutorAttributesList READ LibroAutorAttributesList)
Q_PROPERTY(QStringList LibroAutorPKAttributesList READ LibroAutorPKAttributesList)
Q_PROPERTY(QStringList LibroAutorDateTimeAttributesList READ LibroAutorDateTimeAttributesList)
Q_PROPERTY(QString LibroAutorPKAutoIncrementAttribute READ LibroAutorPKAutoIncrementAttribute)

private:
	//record
	int ID;//!<Atributo id
int LIBRO_ID;//!<Atributo Libro_id
int AUTOR_ID;//!<Atributo Autor_id

	LibroRecordBase *RLIBRO_;//!<Registro Libro_
AutorRecordBase *RAUTOR_;//!<Registro Autor_


	LibroAutorRecordBase *BACKUPRECORD;

	QStringList LIBROAUTORATTRIBUTESLIST;
	QStringList LIBROAUTORPKATTRIBUTESLIST;
	QStringList LIBROAUTORDATETIMEATTRIBUTESLIST;
	QString LIBROAUTORPKAUTOINCREMENTATTRIBUTE;

	RecordBase *getBackUpRecord();

protected:
	
  
	void init();
	void initValues();
	LibroAutorRecordBase(bool conf,
				   QObject *qparent=NULL,
				   RecordBase *rparent=NULL,
				   QSqlDatabase db = QSqlDatabase::database());
	void setRecordEnabledBackup(bool enabled);

public:
	LibroAutorRecordBase(QObject *qparent=NULL,
				  RecordBase *rparent=NULL,
				  QSqlDatabase db = QSqlDatabase::database());
	LibroAutorRecordBase(const LibroAutorRecordBase &other);
	~LibroAutorRecordBase();

	

	//set nuevo valor para un campo
	/*! Establece el valor del atributo id
\param id Valor del atributo
*/
void setId(int id);
/*! Establece el valor del atributo Libro_id
\param Libro_id Valor del atributo
*/
void setLibro_id(int Libro_id);
/*! Establece el valor del atributo Autor_id
\param Autor_id Valor del atributo
*/
void setAutor_id(int Autor_id);

	/*! Establece el registro del atributo Libro_
\param libroRecordBase Registro
*/
void setRLibro_(LibroRecordBase* LibroRecordBase);
/*! Establece el registro del atributo Libro, utilizado por Q_PROPERTY.
\param record Registro
*/
void setPRLibro_(RecordBase* record);
/*! Establece el registro del atributo Autor_
\param autorRecordBase Registro
*/
void setRAutor_(AutorRecordBase* AutorRecordBase);
/*! Establece el registro del atributo Autor, utilizado por Q_PROPERTY.
\param record Registro
*/
void setPRAutor_(RecordBase* record);


	//get de los campos
	/*! Devuelve el valor del atributo id
\return Valor del atributo
*/
int id();
/*! Devuelve el valor del atributo Libro_id
\return Valor del atributo
*/
int Libro_id();
/*! Devuelve el valor del atributo Autor_id
\return Valor del atributo
*/
int Autor_id();

	/*! Devuelve el registro del atributo Libro, utilizado por Q_PROPERTY.
\return Registro
*/
LibroRecordBase *RLibro_();
/*! Devuelve el registro del atributo Autor, utilizado por Q_PROPERTY.
\return Registro
*/
AutorRecordBase *RAutor_();


	void clear();
	void revert();

	/*! Devuelve la propiedad del atributo id.
\return Nombre de la propiedad.
*/
static QString idProperty();
/*! Devuelve la propiedad del atributo Libro_id.
\return Nombre de la propiedad.
*/
static QString Libro_idProperty();
/*! Devuelve la propiedad del atributo Autor_id.
\return Nombre de la propiedad.
*/
static QString Autor_idProperty();

	
	QStringList LibroAutorAttributesList();
QStringList LibroAutorPKAttributesList();
QStringList LibroAutorDateTimeAttributesList();
QString LibroAutorPKAutoIncrementAttribute();

QStringList getAttributesList();
QStringList getPKAttributesList();
QStringList getPKAutoIncrementAttributesList();
QStringList getDateTimeAttributesList();

	QStringList LibroFAttributes();
QStringList AutorFAttributes();


	RecordBase *getLastChildDefaultRecord();
	
	
	
	
	
	LibroAutorRecordBase& operator=(const LibroAutorRecordBase&);
};



Q_DECLARE_METATYPE(LibroAutorRecordBase*)

#endif // LIBROAUTORRECORDBASE_H
