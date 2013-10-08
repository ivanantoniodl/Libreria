#ifndef RECORD_H
#define RECORD_H

#include <QObject>
#include <QtSql>
#include "../qantmv_global.h"

typedef unsigned int UInt;
typedef unsigned long long ULongLong;
typedef long long LongLong;

/*!
\class Record
\brief Esta clase provee una interfaz de registro abstracto que puede ser utilizada para heredar nuevos registros que representan los atributos de una tabla de base de datos.

	Las clases herederas de esta implementarán los atributos únicos que poseen las tablas ademas de implementar clear(), idProperty(), idValue(), idIsNumeric(), idType() y getAttributesList()

\b Consulta

	Esta clase también es utilizada para configurar una consulta para los modelos, para ello se utiliza la relación entre padres e hijos ( ver Record(), setRParent() ) y las funciones set de los atributos únicos que hacen uso de la función agreaddAttributeToQuery
Ejemplo:

Tabla: Lugar

Tabla: Persona\n
Llave primaria: Lugar_idLugar

Configurando una consulta:

\code
PersonaRecord pr;
pr.setIdPersona();
pr.setNombre();
pr.RLugar_idLugar()->setIdLugar();
pr.RLugar_idLugar()->setNomnre();
\endcode

La consulta generada es:

\code
SELECT a.idPersona, a.Nombre from Persona a INNER JOIN Lugar b on a.Lugar_idLugar=b.idLugar
\endcode

\warning Esta clase no se utiliza directamente, debe de heredar.
*/

class TSqlGenerator;
class TSqlError;
class ModelBase;

class QANTMVSHARED_EXPORT RecordBase : public QObject
{
friend class ModelBase;
Q_OBJECT
protected:
	RecordBase *PARENT;
	QObject *QPARENT;
	QSqlDatabase DB;

	bool ISBACKUPRECORUSELOCALATT;
	bool enabledRecordBackup;
	bool enableExtension; //terminar de implementar
	bool recordbaseissettingattsvalues;
	
	bool enabledInsertUpdateOnlyHaveChanged;

	QStringList lstTables;
	QString TABLENAME;
	QString LASTQUERY;

	QStringList lstAttInsertUpdate; //!< Lista de atributos que fueron editados, ya sea para insertar o para actualizar. Atributos modificados

	void showLastQuery(QString);
	void setRecordValues(QSqlQuery&);
	bool verifyValue(QVariant);
	
	void setRecordBaseIsSettingAttsValues(bool);
	
	virtual void setRecordEnabledBackup(bool) = 0;

public:
	RecordBase(QObject *qparent=NULL,
			   RecordBase *rparent=NULL,
			   QSqlDatabase db = QSqlDatabase::database());

	void setRParent(RecordBase *rparent);
	void setQParent(QObject *qparent);
	QString tableName();
	
	bool isExtensionEnabled();

	void addAttributeInsertUpdate(QString);
	void addAttributeNoInsertUpdate(QString);
	
	void setEnabledInsertUpdateOnlyHaveChanged(bool);

	bool comparePK(RecordBase*); //compara las pk si son iguales regresa true si no false

	QString lastQuery();

	QVariantList getPKAttributesValuesList();

	virtual void clear() = 0;
	virtual QStringList getAttributesList() = 0;
	virtual QStringList getPKAttributesList() = 0;
	virtual QStringList getPKAutoIncrementAttributesList() = 0; //Mysql solo permite un campo como autoincrementable y como llave primaria, pero en los heredados una clase tendra todos los autoincrementables de las tablas papas.
	virtual QStringList getDateTimeAttributesList() = 0; //Si hay pk que sean date, time o datetime se asume que es la la base de datos la que asignara el valor y necesitamos saber que atributos son, cada tabla solo tendra un atributo date o datetime pero si es herencia tendra la lista de todos los que hayan en las tablas papas.
	virtual RecordBase *getBackUpRecord() = 0;

	virtual TSqlError update() = 0;
	virtual TSqlError select() = 0;
	virtual TSqlError insert() = 0;

	void revert();
	
	RecordBase* getRecordFromPath(QStringList path,
								  bool pathIncludeAttribute=false);

signals:
	void hasValuesWithOutSave(bool,RecordBase*);
	void destroyed(RecordBase*);
};

class QANTMVSHARED_EXPORT RecordSimpleBase : public RecordBase
{
Q_OBJECT
public:
	RecordSimpleBase(QObject *qparent=NULL,
					 RecordBase *rparent=NULL,
					 QSqlDatabase db = QSqlDatabase::database());

	TSqlError update();
	TSqlError select();
	TSqlError insert();
	TSqlError delete_();
};

class QANTMVSHARED_EXPORT RecordInheritsBase : public RecordBase
{
Q_OBJECT
public:
	RecordInheritsBase(QObject *qparent=NULL,
					   RecordBase *rparent=NULL,
					   QSqlDatabase db = QSqlDatabase::database());

	TSqlError update();
	TSqlError select();
	TSqlError insert();
	TSqlError delete_();

	QStringList getAttributesList();
QStringList getPKAttributesList();
	QStringList getPKAutoIncrementAttributesList();
	QStringList getDateTimeAttributesList();

	QVariantList getPKAttributesValuesList();

	virtual RecordBase *getLastChildDefaultRecord()=0;
};

Q_DECLARE_METATYPE(RecordBase*);
Q_DECLARE_METATYPE(RecordSimpleBase*);
Q_DECLARE_METATYPE(RecordInheritsBase*);
Q_DECLARE_METATYPE(UInt);
Q_DECLARE_METATYPE(LongLong);
Q_DECLARE_METATYPE(ULongLong);

#endif // RECORD_H
