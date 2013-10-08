#ifndef MAQUINARECORDBASE_H
#define MAQUINARECORDBASE_H

#include "recordbase.h"
#include "tsqlgenerator.h"

#include "lugarrecordbase.h"




/*!
  Record base de la tabla Maquina.

  No editar esta clase.

  Para mayor información ver Record.
*/



class QANTMVSHARED_EXPORT MaquinaRecordBase :  public RecordSimpleBase
{

	Q_OBJECT
	/*!Esta propiedad representa el atributo de la llave primaria.
<b>Funciones de acceso:</b>
\code
int id()
void setIdMaquina(int idMaquina)
\endcode
*/
Q_PROPERTY(int id READ idMaquina WRITE setIdMaquina)
/*!Esta propiedad representa el atributo idMaquina.
<b>Funciones de acceso:</b>
\code
int idMaquina()
void setIdMaquina(int idMaquina)
\endcode
*/
Q_PROPERTY(int idMaquina READ idMaquina WRITE setIdMaquina)
/*!Esta propiedad representa el atributo idMaquina.
<b>Funciones de acceso:</b>
\code
int idMaquina()
void setIdMaquina(int idMaquina)
\endcode
*/
Q_PROPERTY(int idMaquina READ idMaquina WRITE setIdMaquina)
/*!Esta propiedad representa el atributo Ip.
<b>Funciones de acceso:</b>
\code
QString Ip()
void setIp(QString Ip)
\endcode
*/
Q_PROPERTY(QString Ip READ Ip WRITE setIp)
/*!Esta propiedad representa el atributo Lugar_idLugar.
<b>Funciones de acceso:</b>
\code
int Lugar_idLugar()
void setLugar_idLugar(int Lugar_idLugar)
\endcode
*/
Q_PROPERTY(int Lugar_idLugar READ Lugar_idLugar WRITE setLugar_idLugar)


	/*!Esta propiedad representa el registro del atributo Lugar_idLugar.
<b>Funciones de acceso:</b>
\code
LugarRecordBase *RLugar_idLugar()
void setPRLugar(RecordBase* record)
\endcode
*/
Q_PROPERTY(RecordBase* RLugar_ READ RLugar_ WRITE setPRLugar_)


	
	Q_PROPERTY(QStringList LugarFAttributes READ LugarFAttributes)

	
	Q_PROPERTY(QStringList MaquinaAttributesList READ MaquinaAttributesList)
Q_PROPERTY(QStringList MaquinaPKAttributesList READ MaquinaPKAttributesList)
Q_PROPERTY(QStringList MaquinaDateTimeAttributesList READ MaquinaDateTimeAttributesList)
Q_PROPERTY(QString MaquinaPKAutoIncrementAttribute READ MaquinaPKAutoIncrementAttribute)

private:
	//record
	int IDMAQUINA;//!<Atributo idMaquina
QString IP;//!<Atributo Ip
int LUGAR_IDLUGAR;//!<Atributo Lugar_idLugar

	LugarRecordBase *RLUGAR_;//!<Registro Lugar_


	MaquinaRecordBase *BACKUPRECORD;

	QStringList MAQUINAATTRIBUTESLIST;
	QStringList MAQUINAPKATTRIBUTESLIST;
	QStringList MAQUINADATETIMEATTRIBUTESLIST;
	QString MAQUINAPKAUTOINCREMENTATTRIBUTE;

	RecordBase *getBackUpRecord();

protected:
	
  
	void init();
	void initValues();
	MaquinaRecordBase(bool conf,
				   QObject *qparent=NULL,
				   RecordBase *rparent=NULL,
				   QSqlDatabase db = QSqlDatabase::database());
	void setRecordEnabledBackup(bool enabled);

public:
	MaquinaRecordBase(QObject *qparent=NULL,
				  RecordBase *rparent=NULL,
				  QSqlDatabase db = QSqlDatabase::database());
	MaquinaRecordBase(const MaquinaRecordBase &other);
	~MaquinaRecordBase();

	

	//set nuevo valor para un campo
	/*! Establece el valor del atributo idMaquina
\param idMaquina Valor del atributo
*/
void setIdMaquina(int idMaquina);
/*! Establece el valor del atributo Ip
\param Ip Valor del atributo
*/
void setIp(QString Ip);
/*! Establece el valor del atributo Lugar_idLugar
\param Lugar_idLugar Valor del atributo
*/
void setLugar_idLugar(int Lugar_idLugar);

	/*! Establece el registro del atributo Lugar_
\param lugarRecordBase Registro
*/
void setRLugar_(LugarRecordBase* LugarRecordBase);
/*! Establece el registro del atributo Lugar, utilizado por Q_PROPERTY.
\param record Registro
*/
void setPRLugar_(RecordBase* record);


	//get de los campos
	/*! Devuelve el valor del atributo idMaquina
\return Valor del atributo
*/
int idMaquina();
/*! Devuelve el valor del atributo Ip
\return Valor del atributo
*/
QString Ip();
/*! Devuelve el valor del atributo Lugar_idLugar
\return Valor del atributo
*/
int Lugar_idLugar();

	/*! Devuelve el registro del atributo Lugar, utilizado por Q_PROPERTY.
\return Registro
*/
LugarRecordBase *RLugar_();


	void clear();
	void revert();

	/*! Devuelve la propiedad del atributo idMaquina.
\return Nombre de la propiedad.
*/
static QString idMaquinaProperty();
/*! Devuelve la propiedad del atributo Ip.
\return Nombre de la propiedad.
*/
static QString IpProperty();
/*! Devuelve la propiedad del atributo Lugar_idLugar.
\return Nombre de la propiedad.
*/
static QString Lugar_idLugarProperty();

	
	QStringList MaquinaAttributesList();
QStringList MaquinaPKAttributesList();
QStringList MaquinaDateTimeAttributesList();
QString MaquinaPKAutoIncrementAttribute();

QStringList getAttributesList();
QStringList getPKAttributesList();
QStringList getPKAutoIncrementAttributesList();
QStringList getDateTimeAttributesList();

	QStringList LugarFAttributes();


	RecordBase *getLastChildDefaultRecord();
	
	
	
	
	
	MaquinaRecordBase& operator=(const MaquinaRecordBase&);
};



Q_DECLARE_METATYPE(MaquinaRecordBase*)

#endif // MAQUINARECORDBASE_H
