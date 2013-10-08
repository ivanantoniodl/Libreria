#ifndef EMPRESARECORDBASE_H
#define EMPRESARECORDBASE_H

#include "recordbase.h"
#include "tsqlgenerator.h"





/*!
  Record base de la tabla Empresa.

  No editar esta clase.

  Para mayor información ver Record.
*/

class LugarRecordBase;
class UsuarioRecordBase;


class QANTMVSHARED_EXPORT EmpresaRecordBase :  public RecordSimpleBase
{
friend class LugarRecordBase;
friend class UsuarioRecordBase;

	Q_OBJECT
	/*!Esta propiedad representa el atributo de la llave primaria.
<b>Funciones de acceso:</b>
\code
int id()
void setIdEmpresa(int idEmpresa)
\endcode
*/
Q_PROPERTY(int id READ idEmpresa WRITE setIdEmpresa)
/*!Esta propiedad representa el atributo idEmpresa.
<b>Funciones de acceso:</b>
\code
int idEmpresa()
void setIdEmpresa(int idEmpresa)
\endcode
*/
Q_PROPERTY(int idEmpresa READ idEmpresa WRITE setIdEmpresa)
/*!Esta propiedad representa el atributo idEmpresa.
<b>Funciones de acceso:</b>
\code
int idEmpresa()
void setIdEmpresa(int idEmpresa)
\endcode
*/
Q_PROPERTY(int idEmpresa READ idEmpresa WRITE setIdEmpresa)
/*!Esta propiedad representa el atributo Nombre.
<b>Funciones de acceso:</b>
\code
QString Nombre()
void setNombre(QString Nombre)
\endcode
*/
Q_PROPERTY(QString Nombre READ Nombre WRITE setNombre)


	
	
	
	
	Q_PROPERTY(QStringList EmpresaAttributesList READ EmpresaAttributesList)
Q_PROPERTY(QStringList EmpresaPKAttributesList READ EmpresaPKAttributesList)
Q_PROPERTY(QStringList EmpresaDateTimeAttributesList READ EmpresaDateTimeAttributesList)
Q_PROPERTY(QString EmpresaPKAutoIncrementAttribute READ EmpresaPKAutoIncrementAttribute)

private:
	//record
	int IDEMPRESA;//!<Atributo idEmpresa
QString NOMBRE;//!<Atributo Nombre

	

	EmpresaRecordBase *BACKUPRECORD;

	QStringList EMPRESAATTRIBUTESLIST;
	QStringList EMPRESAPKATTRIBUTESLIST;
	QStringList EMPRESADATETIMEATTRIBUTESLIST;
	QString EMPRESAPKAUTOINCREMENTATTRIBUTE;

	RecordBase *getBackUpRecord();

protected:
	
  
	void init();
	void initValues();
	EmpresaRecordBase(bool conf,
				   QObject *qparent=NULL,
				   RecordBase *rparent=NULL,
				   QSqlDatabase db = QSqlDatabase::database());
	void setRecordEnabledBackup(bool enabled);

public:
	EmpresaRecordBase(QObject *qparent=NULL,
				  RecordBase *rparent=NULL,
				  QSqlDatabase db = QSqlDatabase::database());
	EmpresaRecordBase(const EmpresaRecordBase &other);
	~EmpresaRecordBase();

	

	//set nuevo valor para un campo
	/*! Establece el valor del atributo idEmpresa
\param idEmpresa Valor del atributo
*/
void setIdEmpresa(int idEmpresa);
/*! Establece el valor del atributo Nombre
\param Nombre Valor del atributo
*/
void setNombre(QString Nombre);

	

	//get de los campos
	/*! Devuelve el valor del atributo idEmpresa
\return Valor del atributo
*/
int idEmpresa();
/*! Devuelve el valor del atributo Nombre
\return Valor del atributo
*/
QString Nombre();

	

	void clear();
	void revert();

	/*! Devuelve la propiedad del atributo idEmpresa.
\return Nombre de la propiedad.
*/
static QString idEmpresaProperty();
/*! Devuelve la propiedad del atributo Nombre.
\return Nombre de la propiedad.
*/
static QString NombreProperty();

	
	QStringList EmpresaAttributesList();
QStringList EmpresaPKAttributesList();
QStringList EmpresaDateTimeAttributesList();
QString EmpresaPKAutoIncrementAttribute();

QStringList getAttributesList();
QStringList getPKAttributesList();
QStringList getPKAutoIncrementAttributesList();
QStringList getDateTimeAttributesList();

	

	RecordBase *getLastChildDefaultRecord();
	
	
	
	
	
	EmpresaRecordBase& operator=(const EmpresaRecordBase&);
};



Q_DECLARE_METATYPE(EmpresaRecordBase*)

#endif // EMPRESARECORDBASE_H
