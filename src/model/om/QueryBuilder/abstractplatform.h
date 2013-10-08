#ifndef ABSTRACTPLATFORM_H
#define ABSTRACTPLATFORM_H

#include <QtCore>
#include "querybuilderdependencies.h"

class TSqlGenerator;

class AbstractPlatform
{
protected:
	TSqlGenerator* tsg;
	bool where_generateTableAlias;

	virtual QString getComparationOperator(TSqlG::criteriaComparation);
	virtual QString getLogicOperator(TSqlG::criteriaLogic);
	virtual QString getRelationOperator(TSqlG::criteriaRelation);
	virtual QString getOrderOperator(TSqlG::criteriaOrder);
	virtual QString valueToText(QVariant,QString id=QString());

	//generadores
	virtual QString generateSelect() = 0;
	virtual QString generateRelation() = 0;
	virtual QString generateWhere() = 0;
	virtual QString generateOrderBy() = 0;
	virtual QString generateLimitOffset() = 0;
	virtual QString generateInsertValues() = 0;
	virtual QString generateUpdate() = 0;
	virtual QString generateDelete() = 0;

    virtual QString generateGroupBy() = 0;
    virtual QString generateHaving() = 0;
public:
	AbstractPlatform(TSqlGenerator*);

	virtual QString getSelectQuery(bool withOffsetLimit = true) = 0;
	virtual QString getInsertQuery() = 0;
	virtual QString getUpdateQuery() = 0;
	virtual QString getDeleteQuery() = 0;
};

#endif // ABSTRACTPLATFORM_H
