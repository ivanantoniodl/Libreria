#ifndef GRUPOPERMISORECORDBASE_H
#define GRUPOPERMISORECORDBASE_H

#include "recordbase.h"
#include "tsqlgenerator.h"





/*!
  Record base de la tabla GrupoPermiso.

  No editar esta clase.

  Para mayor información ver Record.
*/

class PermisoRecordBase;


class QANTMVSHARED_EXPORT GrupoPermisoRecordBase :  public RecordSimpleBase
{
friend class PermisoRecordBase;

	Q_OBJECT
	/*!Esta propiedad representa el atributo de la llave primaria.
<b>Funciones de acceso:</b>
\code
int id()
void setIdGrupoPermiso(int idGrupoPermiso)
\endcode
*/
Q_PROPERTY(int id READ idGrupoPermiso WRITE setIdGrupoPermiso)
/*!Esta propiedad representa el atributo idGrupoPermiso.
<b>Funciones de acceso:</b>
\code
int idGrupoPermiso()
void setIdGrupoPermiso(int idGrupoPermiso)
\endcode
*/
Q_PROPERTY(int idGrupoPermiso READ idGrupoPermiso WRITE setIdGrupoPermiso)
/*!Esta propiedad representa el atributo idGrupoPermiso.
<b>Funciones de acceso:</b>
\code
int idGrupoPermiso()
void setIdGrupoPermiso(int idGrupoPermiso)
\endcode
*/
Q_PROPERTY(int idGrupoPermiso READ idGrupoPermiso WRITE setIdGrupoPermiso)
/*!Esta propiedad representa el atributo Nombre.
<b>Funciones de acceso:</b>
\code
QString Nombre()
void setNombre(QString Nombre)
\endcode
*/
Q_PROPERTY(QString Nombre READ Nombre WRITE setNombre)


	
	
	
	
	Q_PROPERTY(QStringList GrupoPermisoAttributesList READ GrupoPermisoAttributesList)
Q_PROPERTY(QStringList GrupoPermisoPKAttributesList READ GrupoPermisoPKAttributesList)
Q_PROPERTY(QStringList GrupoPermisoDateTimeAttributesList READ GrupoPermisoDateTimeAttributesList)
Q_PROPERTY(QString GrupoPermisoPKAutoIncrementAttribute READ GrupoPermisoPKAutoIncrementAttribute)

private:
	//record
	int IDGRUPOPERMISO;//!<Atributo idGrupoPermiso
QString NOMBRE;//!<Atributo Nombre

	

	GrupoPermisoRecordBase *BACKUPRECORD;

	QStringList GRUPOPERMISOATTRIBUTESLIST;
	QStringList GRUPOPERMISOPKATTRIBUTESLIST;
	QStringList GRUPOPERMISODATETIMEATTRIBUTESLIST;
	QString GRUPOPERMISOPKAUTOINCREMENTATTRIBUTE;

	RecordBase *getBackUpRecord();

protected:
	
  
	void init();
	void initValues();
	GrupoPermisoRecordBase(bool conf,
				   QObject *qparent=NULL,
				   RecordBase *rparent=NULL,
				   QSqlDatabase db = QSqlDatabase::database());
	void setRecordEnabledBackup(bool enabled);

public:
	GrupoPermisoRecordBase(QObject *qparent=NULL,
				  RecordBase *rparent=NULL,
				  QSqlDatabase db = QSqlDatabase::database());
	GrupoPermisoRecordBase(const GrupoPermisoRecordBase &other);
	~GrupoPermisoRecordBase();

	

	//set nuevo valor para un campo
	/*! Establece el valor del atributo idGrupoPermiso
\param idGrupoPermiso Valor del atributo
*/
void setIdGrupoPermiso(int idGrupoPermiso);
/*! Establece el valor del atributo Nombre
\param Nombre Valor del atributo
*/
void setNombre(QString Nombre);

	

	//get de los campos
	/*! Devuelve el valor del atributo idGrupoPermiso
\return Valor del atributo
*/
int idGrupoPermiso();
/*! Devuelve el valor del atributo Nombre
\return Valor del atributo
*/
QString Nombre();

	

	void clear();
	void revert();

	/*! Devuelve la propiedad del atributo idGrupoPermiso.
\return Nombre de la propiedad.
*/
static QString idGrupoPermisoProperty();
/*! Devuelve la propiedad del atributo Nombre.
\return Nombre de la propiedad.
*/
static QString NombreProperty();

	
	QStringList GrupoPermisoAttributesList();
QStringList GrupoPermisoPKAttributesList();
QStringList GrupoPermisoDateTimeAttributesList();
QString GrupoPermisoPKAutoIncrementAttribute();

QStringList getAttributesList();
QStringList getPKAttributesList();
QStringList getPKAutoIncrementAttributesList();
QStringList getDateTimeAttributesList();

	

	RecordBase *getLastChildDefaultRecord();
	
	
	
	
	
	GrupoPermisoRecordBase& operator=(const GrupoPermisoRecordBase&);
};



Q_DECLARE_METATYPE(GrupoPermisoRecordBase*)

#endif // GRUPOPERMISORECORDBASE_H
