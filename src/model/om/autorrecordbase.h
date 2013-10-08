#ifndef AUTORRECORDBASE_H
#define AUTORRECORDBASE_H

#include "recordbase.h"
#include "tsqlgenerator.h"





/*!
  Record base de la tabla Autor.

  No editar esta clase.

  Para mayor información ver Record.
*/

class LibroAutorRecordBase;


class QANTMVSHARED_EXPORT AutorRecordBase :  public RecordSimpleBase
{
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
/*!Esta propiedad representa el atributo Direccion.
<b>Funciones de acceso:</b>
\code
QString Direccion()
void setDireccion(QString Direccion)
\endcode
*/
Q_PROPERTY(QString Direccion READ Direccion WRITE setDireccion)


	
	
	
	
	Q_PROPERTY(QStringList AutorAttributesList READ AutorAttributesList)
Q_PROPERTY(QStringList AutorPKAttributesList READ AutorPKAttributesList)
Q_PROPERTY(QStringList AutorDateTimeAttributesList READ AutorDateTimeAttributesList)
Q_PROPERTY(QString AutorPKAutoIncrementAttribute READ AutorPKAutoIncrementAttribute)

private:
	//record
	int ID;//!<Atributo id
QString NOMBRE;//!<Atributo Nombre
QString DIRECCION;//!<Atributo Direccion

	

	AutorRecordBase *BACKUPRECORD;

	QStringList AUTORATTRIBUTESLIST;
	QStringList AUTORPKATTRIBUTESLIST;
	QStringList AUTORDATETIMEATTRIBUTESLIST;
	QString AUTORPKAUTOINCREMENTATTRIBUTE;

	RecordBase *getBackUpRecord();

protected:
	
  
	void init();
	void initValues();
	AutorRecordBase(bool conf,
				   QObject *qparent=NULL,
				   RecordBase *rparent=NULL,
				   QSqlDatabase db = QSqlDatabase::database());
	void setRecordEnabledBackup(bool enabled);

public:
	AutorRecordBase(QObject *qparent=NULL,
				  RecordBase *rparent=NULL,
				  QSqlDatabase db = QSqlDatabase::database());
	AutorRecordBase(const AutorRecordBase &other);
	~AutorRecordBase();

	

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

	
	QStringList AutorAttributesList();
QStringList AutorPKAttributesList();
QStringList AutorDateTimeAttributesList();
QString AutorPKAutoIncrementAttribute();

QStringList getAttributesList();
QStringList getPKAttributesList();
QStringList getPKAutoIncrementAttributesList();
QStringList getDateTimeAttributesList();

	

	RecordBase *getLastChildDefaultRecord();
	
	
	
	
	
	AutorRecordBase& operator=(const AutorRecordBase&);
};



Q_DECLARE_METATYPE(AutorRecordBase*)

#endif // AUTORRECORDBASE_H
