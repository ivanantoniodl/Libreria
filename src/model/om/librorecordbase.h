#ifndef LIBRORECORDBASE_H
#define LIBRORECORDBASE_H

#include "recordbase.h"
#include "tsqlgenerator.h"





/*!
  Record base de la tabla Libro.

  No editar esta clase.

  Para mayor información ver Record.
*/

class EditorialLibroRecordBase;
class LibroAutorRecordBase;


class QANTMVSHARED_EXPORT LibroRecordBase :  public RecordSimpleBase
{
friend class EditorialLibroRecordBase;
friend class LibroAutorRecordBase;

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
/*!Esta propiedad representa el atributo Nombre.
<b>Funciones de acceso:</b>
\code
QString Nombre()
void setNombre(QString Nombre)
\endcode
*/
Q_PROPERTY(QString Nombre READ Nombre WRITE setNombre)
/*!Esta propiedad representa el atributo AnioImp.
<b>Funciones de acceso:</b>
\code
QString AnioImp()
void setAnioImp(QString AnioImp)
\endcode
*/
Q_PROPERTY(QString AnioImp READ AnioImp WRITE setAnioImp)


	
	
	
	
	Q_PROPERTY(QStringList LibroAttributesList READ LibroAttributesList)
Q_PROPERTY(QStringList LibroPKAttributesList READ LibroPKAttributesList)
Q_PROPERTY(QStringList LibroDateTimeAttributesList READ LibroDateTimeAttributesList)
Q_PROPERTY(QString LibroPKAutoIncrementAttribute READ LibroPKAutoIncrementAttribute)

private:
	//record
	int ID;//!<Atributo id
QString NOMBRE;//!<Atributo Nombre
QString ANIOIMP;//!<Atributo AnioImp

	

	LibroRecordBase *BACKUPRECORD;

	QStringList LIBROATTRIBUTESLIST;
	QStringList LIBROPKATTRIBUTESLIST;
	QStringList LIBRODATETIMEATTRIBUTESLIST;
	QString LIBROPKAUTOINCREMENTATTRIBUTE;

	RecordBase *getBackUpRecord();

protected:
	
  
	void init();
	void initValues();
	LibroRecordBase(bool conf,
				   QObject *qparent=NULL,
				   RecordBase *rparent=NULL,
				   QSqlDatabase db = QSqlDatabase::database());
	void setRecordEnabledBackup(bool enabled);

public:
	LibroRecordBase(QObject *qparent=NULL,
				  RecordBase *rparent=NULL,
				  QSqlDatabase db = QSqlDatabase::database());
	LibroRecordBase(const LibroRecordBase &other);
	~LibroRecordBase();

	

	//set nuevo valor para un campo
	/*! Establece el valor del atributo id
\param id Valor del atributo
*/
void setId(int id);
/*! Establece el valor del atributo Nombre
\param Nombre Valor del atributo
*/
void setNombre(QString Nombre);
/*! Establece el valor del atributo AnioImp
\param AnioImp Valor del atributo
*/
void setAnioImp(QString AnioImp);

	

	//get de los campos
	/*! Devuelve el valor del atributo id
\return Valor del atributo
*/
int id();
/*! Devuelve el valor del atributo Nombre
\return Valor del atributo
*/
QString Nombre();
/*! Devuelve el valor del atributo AnioImp
\return Valor del atributo
*/
QString AnioImp();

	

	void clear();
	void revert();

	/*! Devuelve la propiedad del atributo id.
\return Nombre de la propiedad.
*/
static QString idProperty();
/*! Devuelve la propiedad del atributo Nombre.
\return Nombre de la propiedad.
*/
static QString NombreProperty();
/*! Devuelve la propiedad del atributo AnioImp.
\return Nombre de la propiedad.
*/
static QString AnioImpProperty();

	
	QStringList LibroAttributesList();
QStringList LibroPKAttributesList();
QStringList LibroDateTimeAttributesList();
QString LibroPKAutoIncrementAttribute();

QStringList getAttributesList();
QStringList getPKAttributesList();
QStringList getPKAutoIncrementAttributesList();
QStringList getDateTimeAttributesList();

	

	RecordBase *getLastChildDefaultRecord();
	
	
	
	
	
	LibroRecordBase& operator=(const LibroRecordBase&);
};



Q_DECLARE_METATYPE(LibroRecordBase*)

#endif // LIBRORECORDBASE_H
