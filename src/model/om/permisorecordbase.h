#ifndef PERMISORECORDBASE_H
#define PERMISORECORDBASE_H

#include "recordbase.h"
#include "tsqlgenerator.h"

#include "grupopermisorecordbase.h"




/*!
  Record base de la tabla Permiso.

  No editar esta clase.

  Para mayor información ver Record.
*/

class RolPermisoRecordBase;


class QANTMVSHARED_EXPORT PermisoRecordBase :  public RecordSimpleBase
{
friend class RolPermisoRecordBase;

	Q_OBJECT
	/*!Esta propiedad representa el atributo de la llave primaria.
<b>Funciones de acceso:</b>
\code
int id()
void setIdPermiso(int idPermiso)
\endcode
*/
Q_PROPERTY(int id READ idPermiso WRITE setIdPermiso)
/*!Esta propiedad representa el atributo idPermiso.
<b>Funciones de acceso:</b>
\code
int idPermiso()
void setIdPermiso(int idPermiso)
\endcode
*/
Q_PROPERTY(int idPermiso READ idPermiso WRITE setIdPermiso)
/*!Esta propiedad representa el atributo idPermiso.
<b>Funciones de acceso:</b>
\code
int idPermiso()
void setIdPermiso(int idPermiso)
\endcode
*/
Q_PROPERTY(int idPermiso READ idPermiso WRITE setIdPermiso)
/*!Esta propiedad representa el atributo GrupoPermiso_idGrupoPermiso.
<b>Funciones de acceso:</b>
\code
int GrupoPermiso_idGrupoPermiso()
void setGrupoPermiso_idGrupoPermiso(int GrupoPermiso_idGrupoPermiso)
\endcode
*/
Q_PROPERTY(int GrupoPermiso_idGrupoPermiso READ GrupoPermiso_idGrupoPermiso WRITE setGrupoPermiso_idGrupoPermiso)
/*!Esta propiedad representa el atributo Formulario.
<b>Funciones de acceso:</b>
\code
QString Formulario()
void setFormulario(QString Formulario)
\endcode
*/
Q_PROPERTY(QString Formulario READ Formulario WRITE setFormulario)
/*!Esta propiedad representa el atributo Etiqueta.
<b>Funciones de acceso:</b>
\code
QString Etiqueta()
void setEtiqueta(QString Etiqueta)
\endcode
*/
Q_PROPERTY(QString Etiqueta READ Etiqueta WRITE setEtiqueta)


	/*!Esta propiedad representa el registro del atributo GrupoPermiso_idGrupoPermiso.
<b>Funciones de acceso:</b>
\code
GrupoPermisoRecordBase *RGrupoPermiso_idGrupoPermiso()
void setPRGrupoPermiso(RecordBase* record)
\endcode
*/
Q_PROPERTY(RecordBase* RGrupoPermiso_ READ RGrupoPermiso_ WRITE setPRGrupoPermiso_)


	
	Q_PROPERTY(QStringList GrupoPermisoFAttributes READ GrupoPermisoFAttributes)

	
	Q_PROPERTY(QStringList PermisoAttributesList READ PermisoAttributesList)
Q_PROPERTY(QStringList PermisoPKAttributesList READ PermisoPKAttributesList)
Q_PROPERTY(QStringList PermisoDateTimeAttributesList READ PermisoDateTimeAttributesList)
Q_PROPERTY(QString PermisoPKAutoIncrementAttribute READ PermisoPKAutoIncrementAttribute)

private:
	//record
	int IDPERMISO;//!<Atributo idPermiso
int GRUPOPERMISO_IDGRUPOPERMISO;//!<Atributo GrupoPermiso_idGrupoPermiso
QString FORMULARIO;//!<Atributo Formulario
QString ETIQUETA;//!<Atributo Etiqueta

	GrupoPermisoRecordBase *RGRUPOPERMISO_;//!<Registro GrupoPermiso_


	PermisoRecordBase *BACKUPRECORD;

	QStringList PERMISOATTRIBUTESLIST;
	QStringList PERMISOPKATTRIBUTESLIST;
	QStringList PERMISODATETIMEATTRIBUTESLIST;
	QString PERMISOPKAUTOINCREMENTATTRIBUTE;

	RecordBase *getBackUpRecord();

protected:
	
  
	void init();
	void initValues();
	PermisoRecordBase(bool conf,
				   QObject *qparent=NULL,
				   RecordBase *rparent=NULL,
				   QSqlDatabase db = QSqlDatabase::database());
	void setRecordEnabledBackup(bool enabled);

public:
	PermisoRecordBase(QObject *qparent=NULL,
				  RecordBase *rparent=NULL,
				  QSqlDatabase db = QSqlDatabase::database());
	PermisoRecordBase(const PermisoRecordBase &other);
	~PermisoRecordBase();

	

	//set nuevo valor para un campo
	/*! Establece el valor del atributo idPermiso
\param idPermiso Valor del atributo
*/
void setIdPermiso(int idPermiso);
/*! Establece el valor del atributo GrupoPermiso_idGrupoPermiso
\param GrupoPermiso_idGrupoPermiso Valor del atributo
*/
void setGrupoPermiso_idGrupoPermiso(int GrupoPermiso_idGrupoPermiso);
/*! Establece el valor del atributo Formulario
\param Formulario Valor del atributo
*/
void setFormulario(QString Formulario);
/*! Establece el valor del atributo Etiqueta
\param Etiqueta Valor del atributo
*/
void setEtiqueta(QString Etiqueta);

	/*! Establece el registro del atributo GrupoPermiso_
\param grupopermisoRecordBase Registro
*/
void setRGrupoPermiso_(GrupoPermisoRecordBase* GrupoPermisoRecordBase);
/*! Establece el registro del atributo GrupoPermiso, utilizado por Q_PROPERTY.
\param record Registro
*/
void setPRGrupoPermiso_(RecordBase* record);


	//get de los campos
	/*! Devuelve el valor del atributo idPermiso
\return Valor del atributo
*/
int idPermiso();
/*! Devuelve el valor del atributo GrupoPermiso_idGrupoPermiso
\return Valor del atributo
*/
int GrupoPermiso_idGrupoPermiso();
/*! Devuelve el valor del atributo Formulario
\return Valor del atributo
*/
QString Formulario();
/*! Devuelve el valor del atributo Etiqueta
\return Valor del atributo
*/
QString Etiqueta();

	/*! Devuelve el registro del atributo GrupoPermiso, utilizado por Q_PROPERTY.
\return Registro
*/
GrupoPermisoRecordBase *RGrupoPermiso_();


	void clear();
	void revert();

	/*! Devuelve la propiedad del atributo idPermiso.
\return Nombre de la propiedad.
*/
static QString idPermisoProperty();
/*! Devuelve la propiedad del atributo GrupoPermiso_idGrupoPermiso.
\return Nombre de la propiedad.
*/
static QString GrupoPermiso_idGrupoPermisoProperty();
/*! Devuelve la propiedad del atributo Formulario.
\return Nombre de la propiedad.
*/
static QString FormularioProperty();
/*! Devuelve la propiedad del atributo Etiqueta.
\return Nombre de la propiedad.
*/
static QString EtiquetaProperty();

	
	QStringList PermisoAttributesList();
QStringList PermisoPKAttributesList();
QStringList PermisoDateTimeAttributesList();
QString PermisoPKAutoIncrementAttribute();

QStringList getAttributesList();
QStringList getPKAttributesList();
QStringList getPKAutoIncrementAttributesList();
QStringList getDateTimeAttributesList();

	QStringList GrupoPermisoFAttributes();


	RecordBase *getLastChildDefaultRecord();
	
	
	
	
	
	PermisoRecordBase& operator=(const PermisoRecordBase&);
};



Q_DECLARE_METATYPE(PermisoRecordBase*)

#endif // PERMISORECORDBASE_H
