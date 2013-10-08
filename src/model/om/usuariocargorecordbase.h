#ifndef USUARIOCARGORECORDBASE_H
#define USUARIOCARGORECORDBASE_H

#include "recordbase.h"
#include "tsqlgenerator.h"





/*!
  Record base de la tabla UsuarioCargo.

  No editar esta clase.

  Para mayor información ver Record.
*/

class UsuarioRecordBase;


class QANTMVSHARED_EXPORT UsuarioCargoRecordBase :  public RecordSimpleBase
{
friend class UsuarioRecordBase;

	Q_OBJECT
	/*!Esta propiedad representa el atributo de la llave primaria.
<b>Funciones de acceso:</b>
\code
int id()
void setIdUsuarioCargo(int idUsuarioCargo)
\endcode
*/
Q_PROPERTY(int id READ idUsuarioCargo WRITE setIdUsuarioCargo)
/*!Esta propiedad representa el atributo idUsuarioCargo.
<b>Funciones de acceso:</b>
\code
int idUsuarioCargo()
void setIdUsuarioCargo(int idUsuarioCargo)
\endcode
*/
Q_PROPERTY(int idUsuarioCargo READ idUsuarioCargo WRITE setIdUsuarioCargo)
/*!Esta propiedad representa el atributo idUsuarioCargo.
<b>Funciones de acceso:</b>
\code
int idUsuarioCargo()
void setIdUsuarioCargo(int idUsuarioCargo)
\endcode
*/
Q_PROPERTY(int idUsuarioCargo READ idUsuarioCargo WRITE setIdUsuarioCargo)
/*!Esta propiedad representa el atributo Cargo.
<b>Funciones de acceso:</b>
\code
QString Cargo()
void setCargo(QString Cargo)
\endcode
*/
Q_PROPERTY(QString Cargo READ Cargo WRITE setCargo)


	
	
	
	
	Q_PROPERTY(QStringList UsuarioCargoAttributesList READ UsuarioCargoAttributesList)
Q_PROPERTY(QStringList UsuarioCargoPKAttributesList READ UsuarioCargoPKAttributesList)
Q_PROPERTY(QStringList UsuarioCargoDateTimeAttributesList READ UsuarioCargoDateTimeAttributesList)
Q_PROPERTY(QString UsuarioCargoPKAutoIncrementAttribute READ UsuarioCargoPKAutoIncrementAttribute)

private:
	//record
	int IDUSUARIOCARGO;//!<Atributo idUsuarioCargo
QString CARGO;//!<Atributo Cargo

	

	UsuarioCargoRecordBase *BACKUPRECORD;

	QStringList USUARIOCARGOATTRIBUTESLIST;
	QStringList USUARIOCARGOPKATTRIBUTESLIST;
	QStringList USUARIOCARGODATETIMEATTRIBUTESLIST;
	QString USUARIOCARGOPKAUTOINCREMENTATTRIBUTE;

	RecordBase *getBackUpRecord();

protected:
	
  
	void init();
	void initValues();
	UsuarioCargoRecordBase(bool conf,
				   QObject *qparent=NULL,
				   RecordBase *rparent=NULL,
				   QSqlDatabase db = QSqlDatabase::database());
	void setRecordEnabledBackup(bool enabled);

public:
	UsuarioCargoRecordBase(QObject *qparent=NULL,
				  RecordBase *rparent=NULL,
				  QSqlDatabase db = QSqlDatabase::database());
	UsuarioCargoRecordBase(const UsuarioCargoRecordBase &other);
	~UsuarioCargoRecordBase();

	

	//set nuevo valor para un campo
	/*! Establece el valor del atributo idUsuarioCargo
\param idUsuarioCargo Valor del atributo
*/
void setIdUsuarioCargo(int idUsuarioCargo);
/*! Establece el valor del atributo Cargo
\param Cargo Valor del atributo
*/
void setCargo(QString Cargo);

	

	//get de los campos
	/*! Devuelve el valor del atributo idUsuarioCargo
\return Valor del atributo
*/
int idUsuarioCargo();
/*! Devuelve el valor del atributo Cargo
\return Valor del atributo
*/
QString Cargo();

	

	void clear();
	void revert();

	/*! Devuelve la propiedad del atributo idUsuarioCargo.
\return Nombre de la propiedad.
*/
static QString idUsuarioCargoProperty();
/*! Devuelve la propiedad del atributo Cargo.
\return Nombre de la propiedad.
*/
static QString CargoProperty();

	
	QStringList UsuarioCargoAttributesList();
QStringList UsuarioCargoPKAttributesList();
QStringList UsuarioCargoDateTimeAttributesList();
QString UsuarioCargoPKAutoIncrementAttribute();

QStringList getAttributesList();
QStringList getPKAttributesList();
QStringList getPKAutoIncrementAttributesList();
QStringList getDateTimeAttributesList();

	

	RecordBase *getLastChildDefaultRecord();
	
	
	
	
	
	UsuarioCargoRecordBase& operator=(const UsuarioCargoRecordBase&);
};



Q_DECLARE_METATYPE(UsuarioCargoRecordBase*)

#endif // USUARIOCARGORECORDBASE_H
