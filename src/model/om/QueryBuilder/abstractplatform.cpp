#include "abstractplatform.h"
#include "../tsqlgenerator.h"

#include <QSqlDatabase>
#include <QSqlDriver>

AbstractPlatform::AbstractPlatform(TSqlGenerator *tsqlGenerator):
	tsg(tsqlGenerator)
{
	where_generateTableAlias=true;
}

/*! Devuelve en forma de texto la representación del operador de comparación \a criterio
  \param criterio Operador de comparación a convertir.
  \return Texto que representa el operador \a criterio.
*/
QString AbstractPlatform::getComparationOperator(TSqlG::criteriaComparation criterio)
{
	switch (criterio)
	{
		case TSqlG::EQUAL:
			return "=";
		case TSqlG::NOT_EQUAL:
			return "<>";
		case TSqlG::GREATER_THAN:
			return ">";
		case TSqlG::LESS_THAN:
			return "<";
		case TSqlG::GREATER_EQUAL:
			return ">=";
		case TSqlG::LESS_EQUAL:
			return "<=";
		case TSqlG::ISNULL:
			return "IS NULL";
		case TSqlG::ISNOTNULL:
			return "IS NOT NULL";
		case TSqlG::LIKE:
			return "LIKE";
		case TSqlG::ILIKE:
			return "ILIKE";
		case TSqlG::IN:
			return "IN";
		case TSqlG::NOT_IN:
			return "NOT IN";
		default:
			return "";
	};
	return "";
}

/*! Devuelve en forma de texto la representación del operador lógico \a criterio
  \param criterio Operador ló a convertir.
  \return Texto que representa el operador \a criterio.
*/
QString AbstractPlatform::getLogicOperator(TSqlG::criteriaLogic criterio)
{
	switch (criterio)
	{
		case TSqlG::AND:
			return "AND";
		case TSqlG::OR:
			return "OR";
	};
	return "";
}

/*! Devuelve en forma de texto la representación la relación \a criterio
  \param criterio Relación a convertir.
  \return Texto que representa la relación \a criterio.
*/
QString AbstractPlatform::getRelationOperator(TSqlG::criteriaRelation criterio)
{
	switch(criterio)
	{
		case TSqlG::INNER_JOIN:
			return "INNER JOIN";
		case TSqlG::LEFT_JOIN:
			return "LEFT JOIN";
		case TSqlG::RIGHT_JOIN:
			return "RIGHT JOIN";
		default:
			return "";
	}
}

/*! Devuelve en forma de texto la representación del orden de atributos \a criterio
  \param criterio Orden a convertir.
  \return Texto que representa el orden \a criterio.
*/
QString AbstractPlatform::getOrderOperator(TSqlG::criteriaOrder criterio)
{
	switch (criterio)
	{
		case TSqlG::ASC:
			return "ASC";
		case TSqlG::DESC:
			return "DESC";
		default:
			return "";
	}
}

/*! Devuelve el valor del atributo en forma de texto.
  El texto que se devuelve es para utilizarlo en la consulta.
  Cuando se asigna un valor a un atributo en una consulta UPDATE y el tipo es numérico debe ser de la siguiente manera:

  UPDATE tabla SET Atributo=23

  Pero si el tipo es alfanumérico debe ser de la siguiente manera:

  UPDATE tabla SET Atributo='texto23'

  Esta función se encarga de generar el texto con el valor dependiendo el tipo.

  \param value Valor a convertir.
  \return Texto que representa el valor.s
*/
QString AbstractPlatform::valueToText(QVariant value,QString id)
{
	switch ( value.type() )
	{
		case QVariant::UInt:
		case QVariant::Int:
		case QVariant::LongLong:
		case QVariant::ULongLong:
		case QVariant::Double:
		case QVariant::Char:
		case QVariant::Bool:
			return value.toString();
		case QVariant::Date:
			return "'"+value.toDate().toString("yyyy-MM-dd")+"'";
		case QVariant::DateTime:
			return "'"+value.toDateTime().toString("yyyy-MM-dd hh:mm:ss")+"'";
		case QVariant::String:
			return "'"+value.toString()+"'";
		case QVariant::ByteArray:
			return ":BINDVALUE"+id+"VALUE";
		default:
			return "";
	}
}

