#ifndef TSQLGENERATOR_H
#define TSQLGENERATOR_H

#include <QString>
#include <QVariant>
#include <QStringList>
#include <QDateTime>
#include <QDebug>
#include "../qantmv_global.h"

#include "QueryBuilder/querybuilderdependencies.h"
#include "QueryBuilder/mysqlplatform.h"

#include "recordconfigurequerybase.h"

/*!
\class TSqlGenerator
\brief Clase que genera código SQL.

    Esta clase genera el código SQL necesario para consultar, insertar y modificar registros en la base de datos.   
*/

class RecordBase;
class QSqlDatabase;

class QANTMVSHARED_EXPORT TSqlGenerator
{
friend class AbstractPlatform;
friend class MySQLPlatform;
protected:
	QList<confInsertValue*> lstCIV; //!<Lista de atributos a consultar
private:
	QString tableName; //alias es 'a', por ser la principal de la consulta
	AbstractPlatform *plataform;
	QString dbDriver;

	TSqlGenerator *tsqlGParent;
	short int level; //que nivel de subconsulta es, 0 consulta, 1 primera subconsulta, 2 segunda subconsulta

	char ultimoAlias;

	QList<TSqlG::table*> lstTables;
	QList<TSqlG::selectAttributeValue*> lstSelectAttributes;
	QList<TSqlG::relationValue*> lstRelationValues;
	QList<TSqlG::whereAttributeValue*> lstWhereAttributes;
	QList<TSqlG::orderAttributeValue*> lstOrderAttributes;
    QList<TSqlG::groupByAttribute*> lstGroupByAttributes;
    QList<TSqlG::havingAttribute*> lstHavingAttributes;

	void addConfiguredAtt(QString att,QStringList path=QStringList());

	// limit y offset
	int limite;//!<Limite de la consulta
	int offset;//!<offset de la consulta

	//para update
	QList<TSqlG::updateInsertSetAttributeValue*> lstUpdateSetAttributes;

	//para insert
	QList<RecordBase*> lstInsertRecord;//!<Lista de registros (Record) a insertar
	QList<TSqlG::updateInsertSetAttributeValue*> lstInsertAttributes;//!<Lista de atributos a insertar

public:
	TSqlGenerator(QString TableName=QString(),
				  QSqlDatabase *DB=NULL);
	~TSqlGenerator();

	void setTableName(QString TableName);
	void setTSqlGParent(TSqlGenerator *parent);
	void setSQLDatabase(QSqlDatabase *);
	void setSQLDatabaseDriver(QString);
	void clear();
	void addTable(QString table);
	QString tableAlias(QString table,bool inParent=false);

	void addSelectAttribute(QString attribute);
	void addSelectAttribute(QString table,QString attribute);
	void addSelectAttribute(TSqlGenerator*);
	void addAttributeToSelect(RecordBase *RECORD,QString c,bool subqueryaddingpk=false);

	void addRelation(QString attribute1,
					 QString table2,
					 QString table2_attribute,
					 TSqlG::criteriaRelation criterio=TSqlG::INNER_JOIN);
	void addRelation(QString table1,
					 QString attribute1,
					 QString table2,
					 QString table2_attribute,
					 TSqlG::criteriaRelation criterio=TSqlG::INNER_JOIN);
	void modRelation(QString table2,
					 TSqlG::criteriaRelation criterio=TSqlG::INNER_JOIN);

	void addWhereAttribute(QString attribute,
					   QVariant value,
					   TSqlG::criteriaComparation CriteriaComparation=TSqlG::EQUAL,
					   TSqlG::criteriaLogic CriteriaLogic=TSqlG::AND);
	void addWhereTableAttribute(QString table,
					   QString attribute,
					   QVariant value,
					   TSqlG::criteriaComparation CriteriaComparation=TSqlG::EQUAL,
					   TSqlG::criteriaLogic CriteriaLogic=TSqlG::AND);
	void addWhereTaTa(QString table1,
					  QString attribute1,
					  QString table2,
					  QString attribute2,
					  TSqlG::criteriaComparation CriteriaComparation=TSqlG::EQUAL,
					  TSqlG::criteriaLogic CriteriaLogic=TSqlG::AND,
					  bool Table1inParent=false,
					  bool Table2inParent=false);

	void addWhereStartGroup();
	void addWhereEndGroup();

    void addGroupBy(QString attribute,
                    TSqlG::criteriaOrder criterio=TSqlG::ASC);
    void addHaving(QString attribute,
                   QVariant value,
                   TSqlG::criteriaComparation CriteriaComparation=TSqlG::EQUAL,
                   TSqlG::criteriaLogic CriteriaLogic=TSqlG::AND);

	void addOrderBy(QString attribute,TSqlG::criteriaOrder criterio=TSqlG::ASC);
	void addOrderBy(QString table,QString attribute,TSqlG::criteriaOrder criterio=TSqlG::ASC);

	void setLimit(int l);
	void setOffset(int o);

	QList<confInsertValue*> getLstCIV();

	//para update
	void addUpdateAttribute(QString attribute,
						QVariant value);

	//para insert
	void addInsertAttribute(RecordBase *);
	void addInsertAttribute(QString attribute,
						QVariant value);

	QString getSelectQuery(bool withOffsetLimit = true);
	QString getInsertQuery();
	QString getUpdateQuery();
	QString getDeleteQuery();
};

/*! @} */

#endif
