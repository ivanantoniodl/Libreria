#ifndef ROLRECORDBASE_H
#define ROLRECORDBASE_H

#include "recordbase.h"
#include "tsqlgenerator.h"





/*!
  Record base de la tabla Rol.

  No editar esta clase.

  Para mayor información ver Record.
*/

class RolPermisoRecordBase;
class UsuarioRecordBase;


class QANTMVSHARED_EXPORT RolRecordBase :  public RecordSimpleBase
{
friend class RolPermisoRecordBase;
friend class UsuarioRecordBase;

	Q_OBJECT
	/*!Esta propiedad representa el atributo de la llave primaria.
<b>Funciones de acceso:</b>
\code
int id()
void setIdRol(int idRol)
\endcode
*/
Q_PROPERTY(int id READ idRol WRITE setIdRol)
/*!Esta propiedad representa el atributo idRol.
<b>Funciones de acceso:</b>
\code
int idRol()
void setIdRol(int idRol)
\endcode
*/
Q_PROPERTY(int idRol READ idRol WRITE setIdRol)
/*!Esta propiedad representa el atributo idRol.
<b>Funciones de acceso:</b>
\code
int idRol()
void setIdRol(int idRol)
\endcode
*/
Q_PROPERTY(int idRol READ idRol WRITE setIdRol)
/*!Esta propiedad representa el atributo Rol.
<b>Funciones de acceso:</b>
\code
QString Rol()
void setRol(QString Rol)
\endcode
*/
Q_PROPERTY(QString Rol READ Rol WRITE setRol)


	
	
	
	
	Q_PROPERTY(QStringList RolAttributesList READ RolAttributesList)
Q_PROPERTY(QStringList RolPKAttributesList READ RolPKAttributesList)
Q_PROPERTY(QStringList RolDateTimeAttributesList READ RolDateTimeAttributesList)
Q_PROPERTY(QString RolPKAutoIncrementAttribute READ RolPKAutoIncrementAttribute)

private:
	//record
	int IDROL;//!<Atributo idRol
QString ROL;//!<Atributo Rol

	

	RolRecordBase *BACKUPRECORD;

	QStringList ROLATTRIBUTESLIST;
	QStringList ROLPKATTRIBUTESLIST;
	QStringList ROLDATETIMEATTRIBUTESLIST;
	QString ROLPKAUTOINCREMENTATTRIBUTE;

	RecordBase *getBackUpRecord();

protected:
	
  
	void init();
	void initValues();
	RolRecordBase(bool conf,
				   QObject *qparent=NULL,
				   RecordBase *rparent=NULL,
				   QSqlDatabase db = QSqlDatabase::database());
	void setRecordEnabledBackup(bool enabled);

public:
	RolRecordBase(QObject *qparent=NULL,
				  RecordBase *rparent=NULL,
				  QSqlDatabase db = QSqlDatabase::database());
	RolRecordBase(const RolRecordBase &other);
	~RolRecordBase();

	

	//set nuevo valor para un campo
	/*! Establece el valor del atributo idRol
\param idRol Valor del atributo
*/
void setIdRol(int idRol);
/*! Establece el valor del atributo Rol
\param Rol Valor del atributo
*/
void setRol(QString Rol);

	

	//get de los campos
	/*! Devuelve el valor del atributo idRol
\return Valor del atributo
*/
int idRol();
/*! Devuelve el valor del atributo Rol
\return Valor del atributo
*/
QString Rol();

	

	void clear();
	void revert();

	/*! Devuelve la propiedad del atributo idRol.
\return Nombre de la propiedad.
*/
static QString idRolProperty();
/*! Devuelve la propiedad del atributo Rol.
\return Nombre de la propiedad.
*/
static QString RolProperty();

	
	QStringList RolAttributesList();
QStringList RolPKAttributesList();
QStringList RolDateTimeAttributesList();
QString RolPKAutoIncrementAttribute();

QStringList getAttributesList();
QStringList getPKAttributesList();
QStringList getPKAutoIncrementAttributesList();
QStringList getDateTimeAttributesList();

	

	RecordBase *getLastChildDefaultRecord();
	
	
	
	
	
	RolRecordBase& operator=(const RolRecordBase&);
};



Q_DECLARE_METATYPE(RolRecordBase*)

#endif // ROLRECORDBASE_H
