#ifndef RECORDCONFIGUREQUERYBASE_H
#define RECORDCONFIGUREQUERYBASE_H

#include <QString>
#include <QStringList>
#include <QDebug>
#include "../qantmv_global.h"

/*!Representa la ruta para consultar y escribir un registro.

Cuando se consulta datos de la base de datos, estos se pueden obtener de la misma tabla que se esta trabajando o de otra que sea la tabla propia de una llave foranea, cuando es así se necesita saber las otras tablas a consultar.

Ejemplo:

	Se esta en el modelo que representa a la tabla Persona, esta tiene una llave foránea Lugar_idLugar, la tabla Lugar tiene una llave foránea Tipo_idTipo, la tabla Tipo tiene un atributo llamado Nombre.

	La configuración para poder acceder al atributo Nombre de la tabla Tipo desde Persona es:
	lstRecord = Lugar,Tipo
	att= Nombre
*/
struct confInsertValue
{
	QStringList lstRecord;//!<Ruta del atributo a consultar y escribir
	QString att;//Nombre del atributo a consultar y escribir
};

class QANTMVSHARED_EXPORT RecordConfigureQueryBase
{
protected:
	RecordConfigureQueryBase *PARENT;
	QStringList lstTables;
	QString extensionFor;
	QString id; //en una tabla con varios fk que van a la misma pk identifica a cual de esos es

	void addAttributeToQuery(QString);

	//en este nivel no tiene utilidad, reimplementar en una clase que herede tambien de TSqlGenerator
	virtual void lstAttributesToQueryReady(QString);
public:
	RecordConfigureQueryBase(RecordConfigureQueryBase *rparent=NULL);
	void setId(QString i) { id = i; }

	virtual void allAttributes() = 0;

	//mover
//	void campoDeConsulta(QString); //se emite para que el modelo lo agregue ej. persona,lugar,nombre
};

#endif // RECORDCONFIGUREQUERYBASE_H
