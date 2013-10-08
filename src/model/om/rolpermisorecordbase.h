#ifndef ROLPERMISORECORDBASE_H
#define ROLPERMISORECORDBASE_H

#include "recordbase.h"
#include "tsqlgenerator.h"

#include "permisorecordbase.h"
#include "rolrecordbase.h"




/*!
  Record base de la tabla RolPermiso.

  No editar esta clase.

  Para mayor información ver Record.
*/



class QANTMVSHARED_EXPORT RolPermisoRecordBase :  public RecordSimpleBase
{

	Q_OBJECT
	/*!Esta propiedad representa el atributo de la llave primaria.
<b>Funciones de acceso:</b>
\code
int id()
void setIdRolPermiso(int idRolPermiso)
\endcode
*/
Q_PROPERTY(int id READ idRolPermiso WRITE setIdRolPermiso)
/*!Esta propiedad representa el atributo idRolPermiso.
<b>Funciones de acceso:</b>
\code
int idRolPermiso()
void setIdRolPermiso(int idRolPermiso)
\endcode
*/
Q_PROPERTY(int idRolPermiso READ idRolPermiso WRITE setIdRolPermiso)
/*!Esta propiedad representa el atributo idRolPermiso.
<b>Funciones de acceso:</b>
\code
int idRolPermiso()
void setIdRolPermiso(int idRolPermiso)
\endcode
*/
Q_PROPERTY(int idRolPermiso READ idRolPermiso WRITE setIdRolPermiso)
/*!Esta propiedad representa el atributo Permiso_idPermiso.
<b>Funciones de acceso:</b>
\code
int Permiso_idPermiso()
void setPermiso_idPermiso(int Permiso_idPermiso)
\endcode
*/
Q_PROPERTY(int Permiso_idPermiso READ Permiso_idPermiso WRITE setPermiso_idPermiso)
/*!Esta propiedad representa el atributo Rol_idRol.
<b>Funciones de acceso:</b>
\code
int Rol_idRol()
void setRol_idRol(int Rol_idRol)
\endcode
*/
Q_PROPERTY(int Rol_idRol READ Rol_idRol WRITE setRol_idRol)
/*!Esta propiedad representa el atributo Permiso.
<b>Funciones de acceso:</b>
\code
int Permiso()
void setPermiso(int Permiso)
\endcode
*/
Q_PROPERTY(int Permiso READ Permiso WRITE setPermiso)


	/*!Esta propiedad representa el registro del atributo Permiso_idPermiso.
<b>Funciones de acceso:</b>
\code
PermisoRecordBase *RPermiso_idPermiso()
void setPRPermiso(RecordBase* record)
\endcode
*/
Q_PROPERTY(RecordBase* RPermiso_ READ RPermiso_ WRITE setPRPermiso_)

/*!Esta propiedad representa el registro del atributo Rol_idRol.
<b>Funciones de acceso:</b>
\code
RolRecordBase *RRol_idRol()
void setPRRol(RecordBase* record)
\endcode
*/
Q_PROPERTY(RecordBase* RRol_ READ RRol_ WRITE setPRRol_)


	
	Q_PROPERTY(QStringList PermisoFAttributes READ PermisoFAttributes)
Q_PROPERTY(QStringList RolFAttributes READ RolFAttributes)

	
	Q_PROPERTY(QStringList RolPermisoAttributesList READ RolPermisoAttributesList)
Q_PROPERTY(QStringList RolPermisoPKAttributesList READ RolPermisoPKAttributesList)
Q_PROPERTY(QStringList RolPermisoDateTimeAttributesList READ RolPermisoDateTimeAttributesList)
Q_PROPERTY(QString RolPermisoPKAutoIncrementAttribute READ RolPermisoPKAutoIncrementAttribute)

private:
	//record
	int IDROLPERMISO;//!<Atributo idRolPermiso
int PERMISO_IDPERMISO;//!<Atributo Permiso_idPermiso
int ROL_IDROL;//!<Atributo Rol_idRol
int PERMISO;//!<Atributo Permiso

	PermisoRecordBase *RPERMISO_;//!<Registro Permiso_
RolRecordBase *RROL_;//!<Registro Rol_


	RolPermisoRecordBase *BACKUPRECORD;

	QStringList ROLPERMISOATTRIBUTESLIST;
	QStringList ROLPERMISOPKATTRIBUTESLIST;
	QStringList ROLPERMISODATETIMEATTRIBUTESLIST;
	QString ROLPERMISOPKAUTOINCREMENTATTRIBUTE;

	RecordBase *getBackUpRecord();

protected:
	
  
	void init();
	void initValues();
	RolPermisoRecordBase(bool conf,
				   QObject *qparent=NULL,
				   RecordBase *rparent=NULL,
				   QSqlDatabase db = QSqlDatabase::database());
	void setRecordEnabledBackup(bool enabled);

public:
	RolPermisoRecordBase(QObject *qparent=NULL,
				  RecordBase *rparent=NULL,
				  QSqlDatabase db = QSqlDatabase::database());
	RolPermisoRecordBase(const RolPermisoRecordBase &other);
	~RolPermisoRecordBase();

	

	//set nuevo valor para un campo
	/*! Establece el valor del atributo idRolPermiso
\param idRolPermiso Valor del atributo
*/
void setIdRolPermiso(int idRolPermiso);
/*! Establece el valor del atributo Permiso_idPermiso
\param Permiso_idPermiso Valor del atributo
*/
void setPermiso_idPermiso(int Permiso_idPermiso);
/*! Establece el valor del atributo Rol_idRol
\param Rol_idRol Valor del atributo
*/
void setRol_idRol(int Rol_idRol);
/*! Establece el valor del atributo Permiso
\param Permiso Valor del atributo
*/
void setPermiso(int Permiso);

	/*! Establece el registro del atributo Permiso_
\param permisoRecordBase Registro
*/
void setRPermiso_(PermisoRecordBase* PermisoRecordBase);
/*! Establece el registro del atributo Permiso, utilizado por Q_PROPERTY.
\param record Registro
*/
void setPRPermiso_(RecordBase* record);
/*! Establece el registro del atributo Rol_
\param rolRecordBase Registro
*/
void setRRol_(RolRecordBase* RolRecordBase);
/*! Establece el registro del atributo Rol, utilizado por Q_PROPERTY.
\param record Registro
*/
void setPRRol_(RecordBase* record);


	//get de los campos
	/*! Devuelve el valor del atributo idRolPermiso
\return Valor del atributo
*/
int idRolPermiso();
/*! Devuelve el valor del atributo Permiso_idPermiso
\return Valor del atributo
*/
int Permiso_idPermiso();
/*! Devuelve el valor del atributo Rol_idRol
\return Valor del atributo
*/
int Rol_idRol();
/*! Devuelve el valor del atributo Permiso
\return Valor del atributo
*/
int Permiso();

	/*! Devuelve el registro del atributo Permiso, utilizado por Q_PROPERTY.
\return Registro
*/
PermisoRecordBase *RPermiso_();
/*! Devuelve el registro del atributo Rol, utilizado por Q_PROPERTY.
\return Registro
*/
RolRecordBase *RRol_();


	void clear();
	void revert();

	/*! Devuelve la propiedad del atributo idRolPermiso.
\return Nombre de la propiedad.
*/
static QString idRolPermisoProperty();
/*! Devuelve la propiedad del atributo Permiso_idPermiso.
\return Nombre de la propiedad.
*/
static QString Permiso_idPermisoProperty();
/*! Devuelve la propiedad del atributo Rol_idRol.
\return Nombre de la propiedad.
*/
static QString Rol_idRolProperty();
/*! Devuelve la propiedad del atributo Permiso.
\return Nombre de la propiedad.
*/
static QString PermisoProperty();

	
	QStringList RolPermisoAttributesList();
QStringList RolPermisoPKAttributesList();
QStringList RolPermisoDateTimeAttributesList();
QString RolPermisoPKAutoIncrementAttribute();

QStringList getAttributesList();
QStringList getPKAttributesList();
QStringList getPKAutoIncrementAttributesList();
QStringList getDateTimeAttributesList();

	QStringList PermisoFAttributes();
QStringList RolFAttributes();


	RecordBase *getLastChildDefaultRecord();
	
	
	
	
	
	RolPermisoRecordBase& operator=(const RolPermisoRecordBase&);
};



Q_DECLARE_METATYPE(RolPermisoRecordBase*)

#endif // ROLPERMISORECORDBASE_H
