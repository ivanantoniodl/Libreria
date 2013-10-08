#ifndef EDITORIALRECORDBASE_H
#define EDITORIALRECORDBASE_H

#include "recordbase.h"
#include "tsqlgenerator.h"





/*!
  Record base de la tabla Editorial.

  No editar esta clase.

  Para mayor información ver Record.
*/

class EditorialLibroRecordBase;


class QANTMVSHARED_EXPORT EditorialRecordBase :  public RecordSimpleBase
{
friend class EditorialLibroRecordBase;

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
/*!Esta propiedad representa el atributo Direccion.
<b>Funciones de acceso:</b>
\code
QString Direccion()
void setDireccion(QString Direccion)
\endcode
*/
Q_PROPERTY(QString Direccion READ Direccion WRITE setDireccion)


	
	
	
	
	Q_PROPERTY(QStringList EditorialAttributesList READ EditorialAttributesList)
Q_PROPERTY(QStringList EditorialPKAttributesList READ EditorialPKAttributesList)
Q_PROPERTY(QStringList EditorialDateTimeAttributesList READ EditorialDateTimeAttributesList)
Q_PROPERTY(QString EditorialPKAutoIncrementAttribute READ EditorialPKAutoIncrementAttribute)

private:
	//record
	int ID;//!<Atributo id
QString NOMBRE;//!<Atributo Nombre
QString DIRECCION;//!<Atributo Direccion

	

	EditorialRecordBase *BACKUPRECORD;

	QStringList EDITORIALATTRIBUTESLIST;
	QStringList EDITORIALPKATTRIBUTESLIST;
	QStringList EDITORIALDATETIMEATTRIBUTESLIST;
	QString EDITORIALPKAUTOINCREMENTATTRIBUTE;

	RecordBase *getBackUpRecord();

protected:
	
  
	void init();
	void initValues();
	EditorialRecordBase(bool conf,
				   QObject *qparent=NULL,
				   RecordBase *rparent=NULL,
				   QSqlDatabase db = QSqlDatabase::database());
	void setRecordEnabledBackup(bool enabled);

public:
	EditorialRecordBase(QObject *qparent=NULL,
				  RecordBase *rparent=NULL,
				  QSqlDatabase db = QSqlDatabase::database());
	EditorialRecordBase(const EditorialRecordBase &other);
	~EditorialRecordBase();

	

	//set nuevo valor para un campo
	/*! Establece el valor del atributo id
\param id Valor del atributo
*/
void setId(int id);
/*! Establece el valor del atributo Nombre
\param Nombre Valor del atributo
*/
void setNombre(QString Nombre);
/*! Establece el valor del atributo Direccion
\param Direccion Valor del atributo
*/
void setDireccion(QString Direccion);

	

	//get de los campos
	/*! Devuelve el valor del atributo id
\return Valor del atributo
*/
int id();
/*! Devuelve el valor del atributo Nombre
\return Valor del atributo
*/
QString Nombre();
/*! Devuelve el valor del atributo Direccion
\return Valor del atributo
*/
QString Direccion();

	

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
/*! Devuelve la propiedad del atributo Direccion.
\return Nombre de la propiedad.
*/
static QString DireccionProperty();

	
	QStringList EditorialAttributesList();
QStringList EditorialPKAttributesList();
QStringList EditorialDateTimeAttributesList();
QString EditorialPKAutoIncrementAttribute();

QStringList getAttributesList();
QStringList getPKAttributesList();
QStringList getPKAutoIncrementAttributesList();
QStringList getDateTimeAttributesList();

	

	RecordBase *getLastChildDefaultRecord();
	
	
	
	
	
	EditorialRecordBase& operator=(const EditorialRecordBase&);
};



Q_DECLARE_METATYPE(EditorialRecordBase*)

#endif // EDITORIALRECORDBASE_H
