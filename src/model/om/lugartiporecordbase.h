#ifndef LUGARTIPORECORDBASE_H
#define LUGARTIPORECORDBASE_H

#include "recordbase.h"
#include "tsqlgenerator.h"





/*!
  Record base de la tabla LugarTipo.

  No editar esta clase.

  Para mayor información ver Record.
*/

class LugarRecordBase;


class QANTMVSHARED_EXPORT LugarTipoRecordBase :  public RecordSimpleBase
{
friend class LugarRecordBase;

	Q_OBJECT
	/*!Esta propiedad representa el atributo de la llave primaria.
<b>Funciones de acceso:</b>
\code
int id()
void setIdLugarTipo(int idLugarTipo)
\endcode
*/
Q_PROPERTY(int id READ idLugarTipo WRITE setIdLugarTipo)
/*!Esta propiedad representa el atributo idLugarTipo.
<b>Funciones de acceso:</b>
\code
int idLugarTipo()
void setIdLugarTipo(int idLugarTipo)
\endcode
*/
Q_PROPERTY(int idLugarTipo READ idLugarTipo WRITE setIdLugarTipo)
/*!Esta propiedad representa el atributo idLugarTipo.
<b>Funciones de acceso:</b>
\code
int idLugarTipo()
void setIdLugarTipo(int idLugarTipo)
\endcode
*/
Q_PROPERTY(int idLugarTipo READ idLugarTipo WRITE setIdLugarTipo)
/*!Esta propiedad representa el atributo Tipo.
<b>Funciones de acceso:</b>
\code
QString Tipo()
void setTipo(QString Tipo)
\endcode
*/
Q_PROPERTY(QString Tipo READ Tipo WRITE setTipo)


	
	
	
	
	Q_PROPERTY(QStringList LugarTipoAttributesList READ LugarTipoAttributesList)
Q_PROPERTY(QStringList LugarTipoPKAttributesList READ LugarTipoPKAttributesList)
Q_PROPERTY(QStringList LugarTipoDateTimeAttributesList READ LugarTipoDateTimeAttributesList)
Q_PROPERTY(QString LugarTipoPKAutoIncrementAttribute READ LugarTipoPKAutoIncrementAttribute)

private:
	//record
	int IDLUGARTIPO;//!<Atributo idLugarTipo
QString TIPO;//!<Atributo Tipo

	

	LugarTipoRecordBase *BACKUPRECORD;

	QStringList LUGARTIPOATTRIBUTESLIST;
	QStringList LUGARTIPOPKATTRIBUTESLIST;
	QStringList LUGARTIPODATETIMEATTRIBUTESLIST;
	QString LUGARTIPOPKAUTOINCREMENTATTRIBUTE;

	RecordBase *getBackUpRecord();

protected:
	
  
	void init();
	void initValues();
	LugarTipoRecordBase(bool conf,
				   QObject *qparent=NULL,
				   RecordBase *rparent=NULL,
				   QSqlDatabase db = QSqlDatabase::database());
	void setRecordEnabledBackup(bool enabled);

public:
	LugarTipoRecordBase(QObject *qparent=NULL,
				  RecordBase *rparent=NULL,
				  QSqlDatabase db = QSqlDatabase::database());
	LugarTipoRecordBase(const LugarTipoRecordBase &other);
	~LugarTipoRecordBase();

	

	//set nuevo valor para un campo
	/*! Establece el valor del atributo idLugarTipo
\param idLugarTipo Valor del atributo
*/
void setIdLugarTipo(int idLugarTipo);
/*! Establece el valor del atributo Tipo
\param Tipo Valor del atributo
*/
void setTipo(QString Tipo);

	

	//get de los campos
	/*! Devuelve el valor del atributo idLugarTipo
\return Valor del atributo
*/
int idLugarTipo();
/*! Devuelve el valor del atributo Tipo
\return Valor del atributo
*/
QString Tipo();

	

	void clear();
	void revert();

	/*! Devuelve la propiedad del atributo idLugarTipo.
\return Nombre de la propiedad.
*/
static QString idLugarTipoProperty();
/*! Devuelve la propiedad del atributo Tipo.
\return Nombre de la propiedad.
*/
static QString TipoProperty();

	
	QStringList LugarTipoAttributesList();
QStringList LugarTipoPKAttributesList();
QStringList LugarTipoDateTimeAttributesList();
QString LugarTipoPKAutoIncrementAttribute();

QStringList getAttributesList();
QStringList getPKAttributesList();
QStringList getPKAutoIncrementAttributesList();
QStringList getDateTimeAttributesList();

	

	RecordBase *getLastChildDefaultRecord();
	
	
	
	
	
	LugarTipoRecordBase& operator=(const LugarTipoRecordBase&);
};



Q_DECLARE_METATYPE(LugarTipoRecordBase*)

#endif // LUGARTIPORECORDBASE_H
