#ifndef LUGARRECORDBASE_H
#define LUGARRECORDBASE_H

#include "recordbase.h"
#include "tsqlgenerator.h"

#include "empresarecordbase.h"
#include "lugartiporecordbase.h"




/*!
  Record base de la tabla Lugar.

  No editar esta clase.

  Para mayor información ver Record.
*/

class MaquinaRecordBase;


class QANTMVSHARED_EXPORT LugarRecordBase :  public RecordSimpleBase
{
friend class MaquinaRecordBase;

	Q_OBJECT
	/*!Esta propiedad representa el atributo de la llave primaria.
<b>Funciones de acceso:</b>
\code
int id()
void setIdLugar(int idLugar)
\endcode
*/
Q_PROPERTY(int id READ idLugar WRITE setIdLugar)
/*!Esta propiedad representa el atributo idLugar.
<b>Funciones de acceso:</b>
\code
int idLugar()
void setIdLugar(int idLugar)
\endcode
*/
Q_PROPERTY(int idLugar READ idLugar WRITE setIdLugar)
/*!Esta propiedad representa el atributo idLugar.
<b>Funciones de acceso:</b>
\code
int idLugar()
void setIdLugar(int idLugar)
\endcode
*/
Q_PROPERTY(int idLugar READ idLugar WRITE setIdLugar)
/*!Esta propiedad representa el atributo Empresa_idEmpresa.
<b>Funciones de acceso:</b>
\code
int Empresa_idEmpresa()
void setEmpresa_idEmpresa(int Empresa_idEmpresa)
\endcode
*/
Q_PROPERTY(int Empresa_idEmpresa READ Empresa_idEmpresa WRITE setEmpresa_idEmpresa)
/*!Esta propiedad representa el atributo LugarTipo_idLugarTipo.
<b>Funciones de acceso:</b>
\code
int LugarTipo_idLugarTipo()
void setLugarTipo_idLugarTipo(int LugarTipo_idLugarTipo)
\endcode
*/
Q_PROPERTY(int LugarTipo_idLugarTipo READ LugarTipo_idLugarTipo WRITE setLugarTipo_idLugarTipo)
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
/*!Esta propiedad representa el atributo Telefono.
<b>Funciones de acceso:</b>
\code
QString Telefono()
void setTelefono(QString Telefono)
\endcode
*/
Q_PROPERTY(QString Telefono READ Telefono WRITE setTelefono)
/*!Esta propiedad representa el atributo NumPlaca.
<b>Funciones de acceso:</b>
\code
QString NumPlaca()
void setNumPlaca(QString NumPlaca)
\endcode
*/
Q_PROPERTY(QString NumPlaca READ NumPlaca WRITE setNumPlaca)


	/*!Esta propiedad representa el registro del atributo Empresa_idEmpresa.
<b>Funciones de acceso:</b>
\code
EmpresaRecordBase *REmpresa_idEmpresa()
void setPREmpresa(RecordBase* record)
\endcode
*/
Q_PROPERTY(RecordBase* REmpresa_ READ REmpresa_ WRITE setPREmpresa_)

/*!Esta propiedad representa el registro del atributo LugarTipo_idLugarTipo.
<b>Funciones de acceso:</b>
\code
LugarTipoRecordBase *RLugarTipo_idLugarTipo()
void setPRLugarTipo(RecordBase* record)
\endcode
*/
Q_PROPERTY(RecordBase* RLugarTipo_ READ RLugarTipo_ WRITE setPRLugarTipo_)


	
	Q_PROPERTY(QStringList EmpresaFAttributes READ EmpresaFAttributes)
Q_PROPERTY(QStringList LugarTipoFAttributes READ LugarTipoFAttributes)

	
	Q_PROPERTY(QStringList LugarAttributesList READ LugarAttributesList)
Q_PROPERTY(QStringList LugarPKAttributesList READ LugarPKAttributesList)
Q_PROPERTY(QStringList LugarDateTimeAttributesList READ LugarDateTimeAttributesList)
Q_PROPERTY(QString LugarPKAutoIncrementAttribute READ LugarPKAutoIncrementAttribute)

private:
	//record
	int IDLUGAR;//!<Atributo idLugar
int EMPRESA_IDEMPRESA;//!<Atributo Empresa_idEmpresa
int LUGARTIPO_IDLUGARTIPO;//!<Atributo LugarTipo_idLugarTipo
QString NOMBRE;//!<Atributo Nombre
QString DIRECCION;//!<Atributo Direccion
QString TELEFONO;//!<Atributo Telefono
QString NUMPLACA;//!<Atributo NumPlaca

	EmpresaRecordBase *REMPRESA_;//!<Registro Empresa_
LugarTipoRecordBase *RLUGARTIPO_;//!<Registro LugarTipo_


	LugarRecordBase *BACKUPRECORD;

	QStringList LUGARATTRIBUTESLIST;
	QStringList LUGARPKATTRIBUTESLIST;
	QStringList LUGARDATETIMEATTRIBUTESLIST;
	QString LUGARPKAUTOINCREMENTATTRIBUTE;

	RecordBase *getBackUpRecord();

protected:
	
  
	void init();
	void initValues();
	LugarRecordBase(bool conf,
				   QObject *qparent=NULL,
				   RecordBase *rparent=NULL,
				   QSqlDatabase db = QSqlDatabase::database());
	void setRecordEnabledBackup(bool enabled);

public:
	LugarRecordBase(QObject *qparent=NULL,
				  RecordBase *rparent=NULL,
				  QSqlDatabase db = QSqlDatabase::database());
	LugarRecordBase(const LugarRecordBase &other);
	~LugarRecordBase();

	

	//set nuevo valor para un campo
	/*! Establece el valor del atributo idLugar
\param idLugar Valor del atributo
*/
void setIdLugar(int idLugar);
/*! Establece el valor del atributo Empresa_idEmpresa
\param Empresa_idEmpresa Valor del atributo
*/
void setEmpresa_idEmpresa(int Empresa_idEmpresa);
/*! Establece el valor del atributo LugarTipo_idLugarTipo
\param LugarTipo_idLugarTipo Valor del atributo
*/
void setLugarTipo_idLugarTipo(int LugarTipo_idLugarTipo);
/*! Establece el valor del atributo Nombre
\param Nombre Valor del atributo
*/
void setNombre(QString Nombre);
/*! Establece el valor del atributo Direccion
\param Direccion Valor del atributo
*/
void setDireccion(QString Direccion);
/*! Establece el valor del atributo Telefono
\param Telefono Valor del atributo
*/
void setTelefono(QString Telefono);
/*! Establece el valor del atributo NumPlaca
\param NumPlaca Valor del atributo
*/
void setNumPlaca(QString NumPlaca);

	/*! Establece el registro del atributo Empresa_
\param empresaRecordBase Registro
*/
void setREmpresa_(EmpresaRecordBase* EmpresaRecordBase);
/*! Establece el registro del atributo Empresa, utilizado por Q_PROPERTY.
\param record Registro
*/
void setPREmpresa_(RecordBase* record);
/*! Establece el registro del atributo LugarTipo_
\param lugartipoRecordBase Registro
*/
void setRLugarTipo_(LugarTipoRecordBase* LugarTipoRecordBase);
/*! Establece el registro del atributo LugarTipo, utilizado por Q_PROPERTY.
\param record Registro
*/
void setPRLugarTipo_(RecordBase* record);


	//get de los campos
	/*! Devuelve el valor del atributo idLugar
\return Valor del atributo
*/
int idLugar();
/*! Devuelve el valor del atributo Empresa_idEmpresa
\return Valor del atributo
*/
int Empresa_idEmpresa();
/*! Devuelve el valor del atributo LugarTipo_idLugarTipo
\return Valor del atributo
*/
int LugarTipo_idLugarTipo();
/*! Devuelve el valor del atributo Nombre
\return Valor del atributo
*/
QString Nombre();
/*! Devuelve el valor del atributo Direccion
\return Valor del atributo
*/
QString Direccion();
/*! Devuelve el valor del atributo Telefono
\return Valor del atributo
*/
QString Telefono();
/*! Devuelve el valor del atributo NumPlaca
\return Valor del atributo
*/
QString NumPlaca();

	/*! Devuelve el registro del atributo Empresa, utilizado por Q_PROPERTY.
\return Registro
*/
EmpresaRecordBase *REmpresa_();
/*! Devuelve el registro del atributo LugarTipo, utilizado por Q_PROPERTY.
\return Registro
*/
LugarTipoRecordBase *RLugarTipo_();


	void clear();
	void revert();

	/*! Devuelve la propiedad del atributo idLugar.
\return Nombre de la propiedad.
*/
static QString idLugarProperty();
/*! Devuelve la propiedad del atributo Empresa_idEmpresa.
\return Nombre de la propiedad.
*/
static QString Empresa_idEmpresaProperty();
/*! Devuelve la propiedad del atributo LugarTipo_idLugarTipo.
\return Nombre de la propiedad.
*/
static QString LugarTipo_idLugarTipoProperty();
/*! Devuelve la propiedad del atributo Nombre.
\return Nombre de la propiedad.
*/
static QString NombreProperty();
/*! Devuelve la propiedad del atributo Direccion.
\return Nombre de la propiedad.
*/
static QString DireccionProperty();
/*! Devuelve la propiedad del atributo Telefono.
\return Nombre de la propiedad.
*/
static QString TelefonoProperty();
/*! Devuelve la propiedad del atributo NumPlaca.
\return Nombre de la propiedad.
*/
static QString NumPlacaProperty();

	
	QStringList LugarAttributesList();
QStringList LugarPKAttributesList();
QStringList LugarDateTimeAttributesList();
QString LugarPKAutoIncrementAttribute();

QStringList getAttributesList();
QStringList getPKAttributesList();
QStringList getPKAutoIncrementAttributesList();
QStringList getDateTimeAttributesList();

	QStringList EmpresaFAttributes();
QStringList LugarTipoFAttributes();


	RecordBase *getLastChildDefaultRecord();
	
	
	
	
	
	LugarRecordBase& operator=(const LugarRecordBase&);
};



Q_DECLARE_METATYPE(LugarRecordBase*)

#endif // LUGARRECORDBASE_H
