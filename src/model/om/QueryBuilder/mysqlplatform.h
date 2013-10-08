#ifndef MYSQLPLATFORM_H
#define MYSQLPLATFORM_H

#include "abstractplatform.h"

class TSqlGenerator;

class MySQLPlatform : public AbstractPlatform
{
protected:
	QString generateSelect();
	QString generateRelation();
	QString generateWhere();
	QString generateOrderBy();
	QString generateLimitOffset();
	QString generateInsertValues();
	QString generateUpdate();
	QString generateDelete();
    QString generateGroupBy();
    QString generateHaving();

public:
	MySQLPlatform(TSqlGenerator*);

	QString getSelectQuery(bool withOffsetLimit = true);
	QString getInsertQuery();
	QString getUpdateQuery();
	QString getDeleteQuery();
};

#endif // MYSQLPLATFORM_H
