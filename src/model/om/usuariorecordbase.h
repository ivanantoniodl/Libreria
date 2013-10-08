#ifndef USUARIORECORDBASE_H
#define USUARIORECORDBASE_H

#include "recordbase.h"
#include "tsqlgenerator.h"

#include "empresarecordbase.h"
#include "rolrecordbase.h"
#include "usuariocargorecordbase.h"




/*!
  Record base de la tabla Usuario.

  No editar esta clase.

  Para mayor información ver Record.
*/



class QANTMVSHARED_EXPORT UsuarioRecordBase :  public RecordSimpleBase
{

	Q_OBJECT
	/*!Esta propiedad representa el atributo de la llave primaria.
<b>Funciones de acceso:</b>
\code
int id()
void setIdUsuario(int idUsuario)
\endcode
*/
Q_PROPERTY(int id READ idUsuario WRITE setIdUsuario)
/*!Esta propiedad representa el atributo idUsuario.
<b>Funciones de acceso:</b>
\code
int idUsuario()
void setIdUsuario(int idUsuario)
\endcode
*/
Q_PROPERTY(int idUsuario READ idUsuario WRITE setIdUsuario)
/*!Esta propiedad representa el atributo idUsuario.
<b>Funciones de acceso:</b>
\code
int idUsuario()
void setIdUsuario(int idUsuario)
\endcode
*/
Q_PROPERTY(int idUsuario READ idUsuario WRITE setIdUsuario)
/*!Esta propiedad representa el atributo Empresa_idEmpresa.
<b>Funciones de acceso:</b>
\code
int Empresa_idEmpresa()
void setEmpresa_idEmpresa(int Empresa_idEmpresa)
\endcode
*/
Q_PROPERTY(int Empresa_idEmpresa READ Empresa_idEmpresa WRITE setEmpresa_idEmpresa)
/*!Esta propiedad representa el atributo Rol_idRol.
<b>Funciones de acceso:</b>
\code
int Rol_idRol()
void setRol_idRol(int Rol_idRol)
\endcode
*/
Q_PROPERTY(int Rol_idRol READ Rol_idRol WRITE setRol_idRol)
/*!Esta propiedad representa el atributo UsuarioCargo_idUsuarioCargo.
<b>Funciones de acceso:</b>
\code
int UsuarioCargo_idUsuarioCargo()
void setUsuarioCargo_idUsuarioCargo(int UsuarioCargo_idUsuarioCargo)
\endcode
*/
Q_PROPERTY(int UsuarioCargo_idUsuarioCargo READ UsuarioCargo_idUsuarioCargo WRITE setUsuarioCargo_idUsuarioCargo)
/*!Esta propiedad representa el atributo Nombres.
<b>Funciones de acceso:</b>
\code
QString Nombres()
void setNombres(QString Nombres)
\endcode
*/
Q_PROPERTY(QString Nombres READ Nombres WRITE setNombres)
/*!Esta propiedad representa el atributo Apellidos.
<b>Funciones de acceso:</b>
\code
QString Apellidos()
void setApellidos(QString Apellidos)
\endcode
*/
Q_PROPERTY(QString Apellidos READ Apellidos WRITE setApellidos)
/*!Esta propiedad representa el atributo Usuario.
<b>Funciones de acceso:</b>
\code
QString Usuario()
void setUsuario(QString Usuario)
\endcode
*/
Q_PROPERTY(QString Usuario READ Usuario WRITE setUsuario)
/*!Esta propiedad representa el atributo FechaHora.
<b>Funciones de acceso:</b>
\code
QDateTime FechaHora()
void setFechaHora(QDateTime FechaHora)
\endcode
*/
Q_PROPERTY(QDateTime FechaHora READ FechaHora WRITE setFechaHora)
/*!Esta propiedad representa el atributo Turno.
<b>Funciones de acceso:</b>
\code
QString Turno()
void setTurno(QString Turno)
\endcode
*/
Q_PROPERTY(QString Turno READ Turno WRITE setTurno)


	/*!Esta propiedad representa el registro del atributo Empresa_idEmpresa.
<b>Funciones de acceso:</b>
\code
EmpresaRecordBase *REmpresa_idEmpresa()
void setPREmpresa(RecordBase* record)
\endcode
*/
Q_PROPERTY(RecordBase* REmpresa_ READ REmpresa_ WRITE setPREmpresa_)

/*!Esta propiedad representa el registro del atributo Rol_idRol.
<b>Funciones de acceso:</b>
\code
RolRecordBase *RRol_idRol()
void setPRRol(RecordBase* record)
\endcode
*/
Q_PROPERTY(RecordBase* RRol_ READ RRol_ WRITE setPRRol_)

/*!Esta propiedad representa el registro del atributo UsuarioCargo_idUsuarioCargo.
<b>Funciones de acceso:</b>
\code
UsuarioCargoRecordBase *RUsuarioCargo_idUsuarioCargo()
void setPRUsuarioCargo(RecordBase* record)
\endcode
*/
Q_PROPERTY(RecordBase* RUsuarioCargo_ READ RUsuarioCargo_ WRITE setPRUsuarioCargo_)


	
	Q_PROPERTY(QStringList EmpresaFAttributes READ EmpresaFAttributes)
Q_PROPERTY(QStringList RolFAttributes READ RolFAttributes)
Q_PROPERTY(QStringList UsuarioCargoFAttributes READ UsuarioCargoFAttributes)

	
	Q_PROPERTY(QStringList UsuarioAttributesList READ UsuarioAttributesList)
Q_PROPERTY(QStringList UsuarioPKAttributesList READ UsuarioPKAttributesList)
Q_PROPERTY(QStringList UsuarioDateTimeAttributesList READ UsuarioDateTimeAttributesList)
Q_PROPERTY(QString UsuarioPKAutoIncrementAttribute READ UsuarioPKAutoIncrementAttribute)

private:
	//record
	int IDUSUARIO;//!<Atributo idUsuario
int EMPRESA_IDEMPRESA;//!<Atributo Empresa_idEmpresa
int ROL_IDROL;//!<Atributo Rol_idRol
int USUARIOCARGO_IDUSUARIOCARGO;//!<Atributo UsuarioCargo_idUsuarioCargo
QString NOMBRES;//!<Atributo Nombres
QString APELLIDOS;//!<Atributo Apellidos
QString USUARIO;//!<Atributo Usuario
QDateTime FECHAHORA;//!<Atributo FechaHora
QString TURNO;//!<Atributo Turno

	EmpresaRecordBase *REMPRESA_;//!<Registro Empresa_
RolRecordBase *RROL_;//!<Registro Rol_
UsuarioCargoRecordBase *RUSUARIOCARGO_;//!<Registro UsuarioCargo_


	UsuarioRecordBase *BACKUPRECORD;

	QStringList USUARIOATTRIBUTESLIST;
	QStringList USUARIOPKATTRIBUTESLIST;
	QStringList USUARIODATETIMEATTRIBUTESLIST;
	QString USUARIOPKAUTOINCREMENTATTRIBUTE;

	RecordBase *getBackUpRecord();

protected:
	
  
	void init();
	void initValues();
	UsuarioRecordBase(bool conf,
				   QObject *qparent=NULL,
				   RecordBase *rparent=NULL,
				   QSqlDatabase db = QSqlDatabase::database());
	void setRecordEnabledBackup(bool enabled);

public:
	UsuarioRecordBase(QObject *qparent=NULL,
				  RecordBase *rparent=NULL,
				  QSqlDatabase db = QSqlDatabase::database());
	UsuarioRecordBase(const UsuarioRecordBase &other);
	~UsuarioRecordBase();

	

	//set nuevo valor para un campo
	/*! Establece el valor del atributo idUsuario
\param idUsuario Valor del atributo
*/
void setIdUsuario(int idUsuario);
/*! Establece el valor del atributo Empresa_idEmpresa
\param Empresa_idEmpresa Valor del atributo
*/
void setEmpresa_idEmpresa(int Empresa_idEmpresa);
/*! Establece el valor del atributo Rol_idRol
\param Rol_idRol Valor del atributo
*/
void setRol_idRol(int Rol_idRol);
/*! Establece el valor del atributo UsuarioCargo_idUsuarioCargo
\param UsuarioCargo_idUsuarioCargo Valor del atributo
*/
void setUsuarioCargo_idUsuarioCargo(int UsuarioCargo_idUsuarioCargo);
/*! Establece el valor del atributo Nombres
\param Nombres Valor del atributo
*/
void setNombres(QString Nombres);
/*! Establece el valor del atributo Apellidos
\param Apellidos Valor del atributo
*/
void setApellidos(QString Apellidos);
/*! Establece el valor del atributo Usuario
\param Usuario Valor del atributo
*/
void setUsuario(QString Usuario);
/*! Establece el valor del atributo FechaHora
\param FechaHora Valor del atributo
*/
void setFechaHora(QDateTime FechaHora);
/*! Establece el valor del atributo Turno
\param Turno Valor del atributo
*/
void setTurno(QString Turno);

	/*! Establece el registro del atributo Empresa_
\param empresaRecordBase Registro
*/
void setREmpresa_(EmpresaRecordBase* EmpresaRecordBase);
/*! Establece el registro del atributo Empresa, utilizado por Q_PROPERTY.
\param record Registro
*/
void setPREmpresa_(RecordBase* record);
/*! Establece el registro del atributo Rol_
\param rolRecordBase Registro
*/
void setRRol_(RolRecordBase* RolRecordBase);
/*! Establece el registro del atributo Rol, utilizado por Q_PROPERTY.
\param record Registro
*/
void setPRRol_(RecordBase* record);
/*! Establece el registro del atributo UsuarioCargo_
\param usuariocargoRecordBase Registro
*/
void setRUsuarioCargo_(UsuarioCargoRecordBase* UsuarioCargoRecordBase);
/*! Establece el registro del atributo UsuarioCargo, utilizado por Q_PROPERTY.
\param record Registro
*/
void setPRUsuarioCargo_(RecordBase* record);


	//get de los campos
	/*! Devuelve el valor del atributo idUsuario
\return Valor del atributo
*/
int idUsuario();
/*! Devuelve el valor del atributo Empresa_idEmpresa
\return Valor del atributo
*/
int Empresa_idEmpresa();
/*! Devuelve el valor del atributo Rol_idRol
\return Valor del atributo
*/
int Rol_idRol();
/*! Devuelve el valor del atributo UsuarioCargo_idUsuarioCargo
\return Valor del atributo
*/
int UsuarioCargo_idUsuarioCargo();
/*! Devuelve el valor del atributo Nombres
\return Valor del atributo
*/
QString Nombres();
/*! Devuelve el valor del atributo Apellidos
\return Valor del atributo
*/
QString Apellidos();
/*! Devuelve el valor del atributo Usuario
\return Valor del atributo
*/
QString Usuario();
/*! Devuelve el valor del atributo FechaHora
\return Valor del atributo
*/
QDateTime FechaHora();
/*! Devuelve el valor del atributo Turno
\return Valor del atributo
*/
QString Turno();

	/*! Devuelve el registro del atributo Empresa, utilizado por Q_PROPERTY.
\return Registro
*/
EmpresaRecordBase *REmpresa_();
/*! Devuelve el registro del atributo Rol, utilizado por Q_PROPERTY.
\return Registro
*/
RolRecordBase *RRol_();
/*! Devuelve el registro del atributo UsuarioCargo, utilizado por Q_PROPERTY.
\return Registro
*/
UsuarioCargoRecordBase *RUsuarioCargo_();


	void clear();
	void revert();

	/*! Devuelve la propiedad del atributo idUsuario.
\return Nombre de la propiedad.
*/
static QString idUsuarioProperty();
/*! Devuelve la propiedad del atributo Empresa_idEmpresa.
\return Nombre de la propiedad.
*/
static QString Empresa_idEmpresaProperty();
/*! Devuelve la propiedad del atributo Rol_idRol.
\return Nombre de la propiedad.
*/
static QString Rol_idRolProperty();
/*! Devuelve la propiedad del atributo UsuarioCargo_idUsuarioCargo.
\return Nombre de la propiedad.
*/
static QString UsuarioCargo_idUsuarioCargoProperty();
/*! Devuelve la propiedad del atributo Nombres.
\return Nombre de la propiedad.
*/
static QString NombresProperty();
/*! Devuelve la propiedad del atributo Apellidos.
\return Nombre de la propiedad.
*/
static QString ApellidosProperty();
/*! Devuelve la propiedad del atributo Usuario.
\return Nombre de la propiedad.
*/
static QString UsuarioProperty();
/*! Devuelve la propiedad del atributo FechaHora.
\return Nombre de la propiedad.
*/
static QString FechaHoraProperty();
/*! Devuelve la propiedad del atributo Turno.
\return Nombre de la propiedad.
*/
static QString TurnoProperty();

	
	QStringList UsuarioAttributesList();
QStringList UsuarioPKAttributesList();
QStringList UsuarioDateTimeAttributesList();
QString UsuarioPKAutoIncrementAttribute();

QStringList getAttributesList();
QStringList getPKAttributesList();
QStringList getPKAutoIncrementAttributesList();
QStringList getDateTimeAttributesList();

	QStringList EmpresaFAttributes();
QStringList RolFAttributes();
QStringList UsuarioCargoFAttributes();


	RecordBase *getLastChildDefaultRecord();
	
	
	
	
	
	UsuarioRecordBase& operator=(const UsuarioRecordBase&);
};



Q_DECLARE_METATYPE(UsuarioRecordBase*)

#endif // USUARIORECORDBASE_H
