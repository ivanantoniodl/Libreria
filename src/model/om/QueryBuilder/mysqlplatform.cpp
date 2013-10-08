#include "mysqlplatform.h"
#include "../tsqlgenerator.h"

MySQLPlatform::MySQLPlatform(TSqlGenerator* tsqlGenerator):
	AbstractPlatform(tsqlGenerator)
{
}

QString MySQLPlatform::generateSelect()
{
	QString generado;
	if ( tsg->lstSelectAttributes.size() > 0 )
	{
		foreach ( TSqlG::selectAttributeValue *sc, tsg->lstSelectAttributes )
		{
			if ( sc->tsg == NULL )
			{
				if ( generado.isEmpty() )
					generado="select "+tsg->tableAlias(sc->tableName)+"."+
							 sc->attribute;
				else
					generado+=","+tsg->tableAlias(sc->tableName)+"."+
							  sc->attribute;
			}
			else
			{
				if ( generado.isEmpty() )
					generado="select ("+sc->tsg->getSelectQuery(false)+")";
				else
					generado+=",("+sc->tsg->getSelectQuery(false)+")";
			}
		}
	}
	else
		generado+="select *";

	QString prinTableAlias( QString( tsg->level+1,QChar('a') ) );
	generado+=" from "+tsg->tableName+" "+prinTableAlias+" ";
	return generado;
}

QString MySQLPlatform::generateRelation()
{
	QString generado;
	QList<TSqlG::relationValue*> lstTablasGeneradas;

	for ( int c=0; c<tsg->lstRelationValues.size(); c++ )
	{
		TSqlG::relationValue *rv=tsg->lstRelationValues.at(c);

		//verificamos que no se haya generado la relacion de dos tablas especificas
		bool encontrado=false;
		foreach ( TSqlG::relationValue *rvtg, lstTablasGeneradas )
		{
			if ( rvtg->table1 == rv->table1 &&
					rvtg->table2 == rv->table2 )
			{
				encontrado=true;
				break;
			}
		}
		if ( encontrado )
			continue;

		//generando relacion de tabla1 con tabla2 usando atributo1 y atributo2
		generado+=getRelationOperator(rv->CriterioRelacion)+
				" "+rv->table2+" "+
				tsg->tableAlias(rv->table2)+" ON "+
				tsg->tableAlias(rv->table1)+"."+
				rv->attribute1+
				"="+tsg->tableAlias(rv->table2)+
				"."+rv->table2_attribute+" ";

		//se busca en la lista de relaciones si hay otra que tenga las mismas tabla1 y tabla2
		//para agregarlos a la condicion ( ON ) de la relacion.
		//Habrian mas si una tabla tuvira mas de un atributo como llave primaria, si una tabla
		//solo tiene un atributo como llave primaria no entraria al siguiente ciclo.
		for ( int d=c+1; d<tsg->lstRelationValues.size(); d++ )
		{
			TSqlG::relationValue *rvo=tsg->lstRelationValues.at(d);
			if ( rvo->table1 == rv->table1 &&
					rvo->table2 == rv->table2)
				generado+=" AND "+
						tsg->tableAlias(rvo->table1)+"."+
						rvo->attribute1+
						"="+tsg->tableAlias(rvo->table2)+
						"."+rvo->table2_attribute+" ";
		}
		lstTablasGeneradas.append( rv );
	}
	return generado;
}

QString MySQLPlatform::generateWhere()
{
	QString generado;
	bool primero=true;
	foreach ( TSqlG::whereAttributeValue *wcv, tsg->lstWhereAttributes )
	{
		if ( wcv->grupoInicio )
		{
			generado+=" ( ";
			continue;
		}
		if ( wcv->grupoFinal )
		{
			generado+=" ) ";
			continue;
		}

		if ( !primero )
		{
			generado+=" "+getLogicOperator(wcv->CriteriaLogic)+" ";
		}

		QString ta=where_generateTableAlias?tsg->tableAlias(wcv->table,wcv->table1inParent)+".":"";

		if ( wcv->value.type() != QVariant::Invalid )
		{
			if ( wcv->CriteriaComparation == TSqlG::ISNULL ||
				 wcv->CriteriaComparation == TSqlG::ISNOTNULL )
				generado+=ta+wcv->attribute+" "+
						getComparationOperator(wcv->CriteriaComparation);
			else
				generado+=ta+wcv->attribute+" "+getComparationOperator(wcv->CriteriaComparation)+" "+
						  valueToText(wcv->value);
		}
		else
		{
			//no tiene value,es comparacion entre campos
			generado+=ta+wcv->attribute+" "+
					getComparationOperator(wcv->CriteriaComparation)+
					" "+(where_generateTableAlias?tsg->tableAlias(wcv->table2,wcv->table2inParent):wcv->table2)+
					"."+wcv->attribute2;
		}
		primero=false;
	}
	if ( !generado.isEmpty() )
	{
		//if ( incluirWhere )
		generado.prepend(" WHERE ");
		generado+=" ";
	}

	return generado;
}

QString MySQLPlatform::generateOrderBy()
{
	QString generado;
	foreach ( TSqlG::orderAttributeValue *oav, tsg->lstOrderAttributes )
	{
		if ( generado.isEmpty() )
			generado=" ORDER BY "+tsg->tableAlias(oav->table)+"."+oav->attribute+" "+
					getOrderOperator(oav->CriteriaOrder)+" ";
		else
			generado+=", "+tsg->tableAlias(oav->table)+"."+oav->attribute+" "+
                    getOrderOperator(oav->CriteriaOrder)+" ";
	}
	return generado;
}

QString MySQLPlatform::generateLimitOffset()
{
	QString generado=" LIMIT "+QString::number(tsg->limite);
	if ( tsg->offset > 0 )
		generado+=" OFFSET "+QString::number(tsg->offset);

	return generado;
}

//QString MySQLPlatform::generateInsertRecord()
//{
//}

QString MySQLPlatform::generateInsertValues()
{
	QString query="INSERT INTO "+tsg->tableName+" (";
	QString valuees="(";
	for ( int c=0; c<tsg->lstInsertAttributes.size(); c++ )
	{
		TSqlG::updateInsertSetAttributeValue *v=tsg->lstInsertAttributes.at(c);
		query+=v->attribute;
		if ( c < tsg->lstInsertAttributes.size()-1 )
			query+=",";
		else
			query+=") VALUES ";
		valuees+=valueToText( v->value , v->attribute );
		if ( c < tsg->lstInsertAttributes.size()-1 )
			valuees+=",";
	}
	valuees+=")";
	query+=valuees;

	return query;
}

QString MySQLPlatform::generateUpdate()
{
	//cantidad de where debe ser igual al lista de campos a modificar

	QString query="UPDATE "+ tsg->tableName+" SET ";
	for ( int c=0; c<tsg->lstUpdateSetAttributes.size() ; c++ )
	{
		TSqlG::updateInsertSetAttributeValue *v=tsg->lstUpdateSetAttributes.at(c);
		query+=v->attribute+" = "+valueToText(v->value, v->attribute );
		if ( c != (tsg->lstUpdateSetAttributes.size()-1) )
			query+=",";
	}
	where_generateTableAlias=false;
	query+=generateWhere();
	where_generateTableAlias=true;
	return query;
}

QString MySQLPlatform::generateDelete()
{
	QString query="DELETE FROM "+ tsg->tableName;
	where_generateTableAlias=false;
	query+=generateWhere();
	where_generateTableAlias=true;
	return query;
}

QString MySQLPlatform::generateGroupBy()
{
    if ( ! tsg->lstGroupByAttributes.isEmpty() )
    {
        QString query="GROUP BY";
        for ( int c=0; c<tsg->lstGroupByAttributes.size(); c++ )
        {
            TSqlG::groupByAttribute* v=tsg->lstGroupByAttributes.at(c);

            if ( c>0 )
                query+=",";

            query+=" "+v->attribute+" "+getOrderOperator( v->CriteriaOrder )+" ";
        }
        return query;
    }
    else
        return "";
}

QString MySQLPlatform::generateHaving()
{
    if ( ! tsg->lstGroupByAttributes.isEmpty() && ! tsg->lstHavingAttributes.isEmpty() )
    {
        QString query="HAVING";
        for ( int c=0; c<tsg->lstHavingAttributes.size(); c++ )
        {
            TSqlG::havingAttribute* v=tsg->lstHavingAttributes.at(c);

            if ( c>0 )
                query+=" "+getLogicOperator(v->CriteriaLogic);

            if ( v->CriteriaComparation == TSqlG::ISNULL ||
                 v->CriteriaComparation == TSqlG::ISNOTNULL )
                query+=" "+v->attribute+" "+
                        getComparationOperator(v->CriteriaComparation);
            else
                query+=" "+v->attribute+" "+getComparationOperator(v->CriteriaComparation)+" "+
                          valueToText(v->value);
        }
        return query;
    }
    else
        return "";
}

QString MySQLPlatform::getSelectQuery(bool withOffsetLimit)
{
	QString consulta = generateSelect()+
			generateRelation()+
			generateWhere()+
            generateGroupBy()+
            generateHaving()+
			generateOrderBy();

	if (withOffsetLimit)
		consulta += generateLimitOffset();

	return consulta;
}

QString MySQLPlatform::getInsertQuery()
{
	if ( tsg->lstInsertAttributes.size() > 0 )
		return generateInsertValues();

	return "";
}

QString MySQLPlatform::getUpdateQuery()
{
	return generateUpdate();
}

QString MySQLPlatform::getDeleteQuery()
{
	return generateDelete();
}
