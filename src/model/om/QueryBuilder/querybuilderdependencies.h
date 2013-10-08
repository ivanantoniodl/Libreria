#ifndef QUERYBUILDERDEPENDENCIES_H
#define QUERYBUILDERDEPENDENCIES_H

#include <QtCore>

class TSqlGenerator;

namespace TSqlG
{

//! Representa la comparación que ser hará entre dos elementos en la sección WHERE de una consulta.
enum criteriaComparation
{
	EQUAL,
	NOT_EQUAL,
	GREATER_THAN,
	LESS_THAN,
	GREATER_EQUAL,
	LESS_EQUAL,
	ISNULL,
	ISNOTNULL,
	LIKE,
	ILIKE,
	NOT_IN,
	IN
};

//! Representa el tipo de relación que se hará entre dos tablas.
enum criteriaRelation
{
	RELACION_NA,
	LEFT_JOIN,
	RIGHT_JOIN,
	INNER_JOIN
};

//!Representa la unión entre condiciones en la sección WHERE de una consulta.
enum criteriaLogic
{
	AND,
	OR
};

//!Representa el tipo de ordenamiento que se hará en la sección ORDER BY
enum criteriaOrder
{
	ORDEN_NA,
	ASC,
	DESC
};

//!Representa una tabla en la consulta
struct table
{
	QString nombre; //!<Nombre de la tabla.
	QString alias; //!<Alias de la tabla.
};

//!Representa un atributo de una tabla a consultar.
struct selectAttributeValue
{
	TSqlGenerator *tsg;
	QString tableName;//!<Tabla de donde pertenece el atributo a consultar.
	QString attribute;//!<Atributo a consultar

	selectAttributeValue()
	{
		tsg=NULL;
	}
};

//!Representa los elementos de una relación
struct relationValue
{
	QString table1;//!<Tabla 1
	QString attribute1;//!<Atributo de la tabla 1
	QString table2;//!<Tabla 2
	QString table2_attribute;//!<Atributo de la tabla 2
	criteriaRelation CriterioRelacion;//!<Tipo de relación a realizar.
};

//!Representa una condición en la sección WHERE
struct whereAttributeValue
{
	QString table;//!<Tabla 1
	QString attribute;//!<Atributo 1
	QString table2;//!<Tabla 2
	QString attribute2;//!<Atributo 2
	QVariant value;//!<Valor a comparar
	bool isValue;//!<Si es valor lo que se va a comparar
	bool grupoInicio;//!<Si inicia un grupo de comparación, abre un parentesis en la consulta
	bool grupoFinal;//!<Si finaliza un grupo de comparación, cierra un parentesis en la consultar
	criteriaComparation CriteriaComparation;//!<Comparación a realizar
	criteriaLogic CriteriaLogic;//!<Operador lógico para unirlo con una comparación anterior
	bool table1inParent;
	bool table2inParent;

	whereAttributeValue()
	{
		isValue=true;
		grupoInicio=false;
		grupoFinal=false;
		table1inParent=false;
		table2inParent=false;
	}
};

//!Representa una manera de ordenar los atributos consultados
struct orderAttributeValue
{
	QString attribute;//!<Atributo a ordenar
	QString table;//!<Tabla del atributo
	criteriaOrder CriteriaOrder;//!<Orden a aplicar
};

//!Representa un atributo para actualizar o insertar
struct updateInsertSetAttributeValue
{
	QString attribute;//!<Atributo
	QVariant value;//!<Valor del atributo
};

struct groupByAttribute
{
    QString attribute;
    criteriaOrder CriteriaOrder;
};

struct havingAttribute
{
    QString attribute;
    QVariant value;
    criteriaComparation CriteriaComparation;
    criteriaLogic CriteriaLogic;
};

}

#endif // QUERYBUILDERDEPENDENCIES_H
