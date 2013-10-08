#include "tsqlgenerator.h"
#include "recordbase.h"

/*!Construye el generador de código SQL con \a TableName como tabla principal.
  Al pasarle el nombre de la tabla principal como parametro se crear su alias 'a', si no se establece la tabla no se crea el alias.
  \param TableName Tabla principal con la que se trabaja.
*/
TSqlGenerator::TSqlGenerator(QString TableName,  QSqlDatabase *DB)
{
	tableName=TableName;
	plataform=NULL;
	if ( !tableName.isEmpty() )
	{
		TSqlG::table *t=new TSqlG::table;
		t->nombre=tableName;
		t->alias="a";
		lstTables.append(t);
		ultimoAlias='a';
	}
	else
		ultimoAlias=0;
	limite=50;
	offset=-1;
	tsqlGParent=NULL;
	level = 0;
	setSQLDatabase(DB);
}

/*! Establece \a TableName como la tabla principal a trabajar, se establece su alias 'a' y se reinicia todo.
  \param TableName Tabla principal con la que se trabaja.
*/
void TSqlGenerator::setTableName(QString TableName)
{	
	clear();
	tableName=TableName;
	TSqlG::table *t=new TSqlG::table;
	t->nombre=tableName;
	t->alias="a";
	ultimoAlias='a';
	lstTables.append(t);
}

void TSqlGenerator::setTSqlGParent(TSqlGenerator *parent) { tsqlGParent = parent; }

void TSqlGenerator::setSQLDatabase(QSqlDatabase *DB)
{
	if ( DB == NULL )
		return;

	if ( DB->driverName() == "QMYSQL" )
	{
		if ( plataform != NULL )
			delete plataform;
		plataform = new MySQLPlatform(this);
		dbDriver = "QMYSQL";
	}
}

void TSqlGenerator::setSQLDatabaseDriver(QString driver)
{
	if ( driver.isEmpty() )
		return;

	if ( driver == "QMYSQL" )
	{
		if ( plataform != NULL )
			delete plataform;
		plataform = new MySQLPlatform(this);
		dbDriver=driver;
	}
}

//! Se reinicia todo
TSqlGenerator::~TSqlGenerator() { clear(); }

//! Limpia todas las configuraciones.
void TSqlGenerator::clear()
{
	foreach ( TSqlG::selectAttributeValue *sa , lstSelectAttributes )
		if ( sa->tsg != NULL )
			delete sa->tsg;

	qDeleteAll (lstSelectAttributes);
	qDeleteAll (lstRelationValues);
	qDeleteAll (lstWhereAttributes);
	qDeleteAll (lstOrderAttributes);
	qDeleteAll (lstTables);
	qDeleteAll (lstUpdateSetAttributes);
	qDeleteAll (lstInsertRecord);
	qDeleteAll (lstInsertAttributes);
	qDeleteAll (lstCIV);

	lstTables.clear();
	lstSelectAttributes.clear();
	lstRelationValues.clear();
	lstWhereAttributes.clear();
	lstOrderAttributes.clear();
	lstUpdateSetAttributes.clear();
	lstInsertRecord.clear();
	lstInsertAttributes.clear();
	lstCIV.clear();
}

/*! Agrega una tabla a la consulta.
  La tabla se agrega y se le crea su alias. Los alias se crean en orden alfabetico, la tabla principal es 'a' así que la siguiente tabla a agregar será la 'b', la siguiente la 'c', etc.
  \param Table Table a agregar a la consulta.
*/
void TSqlGenerator::addTable(QString Table)
{
	if ( tableName.compare( Table, Qt::CaseInsensitive ) == 0 )
		return;

	foreach ( TSqlG::table *t, lstTables )
	{
		if ( t->nombre.compare( Table , Qt::CaseInsensitive) == 0 )
			return;
	}

	ultimoAlias++;
	TSqlG::table *t=new TSqlG::table;
	t->nombre=Table;
	t->alias=QString(ultimoAlias);
	lstTables.append(t);
}

/*! Devulve el alias de una tabla.
  \param tab Tabla a buscar el alias.
  \return Alias de la tabla \a tab
*/
QString TSqlGenerator::tableAlias(QString tab,bool inParent)
{
	if ( inParent && tsqlGParent == NULL)
	{
		qDebug() << "TSqlGenerator: TableAlias: No se puede encontrar el alias de la tabla "+tab+
					" en el padre ya que no existe el padre";
		return "";
	}

	if ( tsqlGParent == NULL )
	{
		foreach ( TSqlG::table *t, lstTables )
		{
			if ( t->nombre.compare( tab , Qt::CaseInsensitive) == 0 )
				return t->alias;
		}
	}
	else
	{
		QList<TSqlG::table*> lst;
		short int qlevel;
		if ( inParent )
		{
			lst = tsqlGParent->lstTables;
			qlevel = tsqlGParent->level;
		}
		else
		{
			lst = lstTables;
			qlevel = level;
		}

		foreach ( TSqlG::table *t, lst )
		{
			if ( t->nombre.compare( tab , Qt::CaseInsensitive) == 0 )
				return QString( qlevel+1, QChar(t->alias.at(0)) );
		}
	}
	return "";
}

/*! Agrega un atributo de la tabla principal a la consulta.
  \param attribute Atributo de la tabla principal a agregar.
*/
void TSqlGenerator::addSelectAttribute(QString attribute)
{
	addSelectAttribute(tableName,attribute);
}

/*! Agrega un atributo de la tabla \a table a la consulta.
  \param table Tabla de donde pertence el atributo \a attribute
  \param attribute Atributo de la tabla \a table a agregar.
*/
void TSqlGenerator::addSelectAttribute(QString table,QString attribute)
{
	foreach ( TSqlG::selectAttributeValue *sc, lstSelectAttributes )
		if ( sc->tableName == table && sc->attribute == attribute )
			return;

	addTable(table);
	TSqlG::selectAttributeValue *sc = new TSqlG::selectAttributeValue;
	sc->tableName=table;
	sc->attribute=attribute;
	lstSelectAttributes.append(sc);
}

/*! Agrega una subconsulta a la consulta
  \warning No disponible todavia.
*/
void TSqlGenerator::addSelectAttribute(TSqlGenerator *t)
{
	foreach ( TSqlG::selectAttributeValue *sc, lstSelectAttributes )
		if ( sc->tsg == (TSqlGenerator*)t )
			return;

	TSqlG::selectAttributeValue *sc = new TSqlG::selectAttributeValue;
	sc->tsg=(TSqlGenerator*)t;
	lstSelectAttributes.append(sc);
}

void TSqlGenerator::addConfiguredAtt(QString att,QStringList path)
{
	if ( tsqlGParent != NULL )
		tsqlGParent->addConfiguredAtt( att, path );

	foreach ( confInsertValue *civ, lstCIV )
		if ( civ->att == att && civ->lstRecord == path )
			return;

	//agregando configuracion de consulta al modelo
	confInsertValue *civ=new confInsertValue;
	civ->att=att;
	civ->lstRecord=path;
	lstCIV.append(civ);
}

void TSqlGenerator::addAttributeToSelect(RecordBase *RECORD,QString c,bool subqueryaddingpk)
{
	if ( tableName.isEmpty() )
	{
		qDebug() << "TSqlGenerator: No se ha especificado el nombre de la tabla. Utilizar setTableName(QString TableName)";
		return;
	}
	if ( RECORD==NULL )
	{
		qDebug() << "TSqlGenerator: No se ha especificado RECORD. Utilizar setRecord(RecordBase *)";
		return;
	}

	//agregando las tablas necesarias para llegar al atributo, esto es
	//necesario cuando son tablas heredadas

	QStringList lstConsulta=c.split(",",QString::SkipEmptyParts);

	if ( lstConsulta.size() > 1 )
	{
		//Atributo de otra tabla

		QStringList lstTablesTemp; //se usa para buscar el respectivo RECORD de la tabla

		if ( c.contains("(") && c.contains(")") )
		{			
			//el atributo en la consulta pasa por tablas que tienen fk que vienen de la misma pk

			//agregamos la pk de la tabla del atributo que se quiere consultar
			//*************************************************************************************************
			if ( ! subqueryaddingpk )
			{
				QStringList lstpkpath = lstConsulta;
				lstpkpath.removeLast();
				RecordBase *pkrecordtemp = RECORD->getRecordFromPath( lstConsulta, true );

				QString t = lstConsulta.at(lstConsulta.size()-2);
				t.replace( QRegExp("\\(([a-z]|[A-Z]|\\d)+\\)"),""  );

				foreach( QString pk,
						 pkrecordtemp->property(QString(t+"PKAttributesList").toLocal8Bit()).toStringList() )
				{
					if ( pk != lstConsulta.last() )
					{
						bool ya=false;
						foreach ( confInsertValue* civ, lstCIV )
						{
							if ( civ->lstRecord == lstpkpath && civ->att == pk )
							{
								ya=true;
								break;
							}
						}
						if ( ya )
							break;

						QStringList lst = lstpkpath;
						lst.append( pk );						
						addAttributeToSelect(RECORD, lst.join(",") ,true);
					}
				}
			}
			//*************************************************************************************************


			QStringList lstSubCon;
			int c=0;
			bool iniciando=true;
			short int querylevel = 0;
			TSqlGenerator *lastSubQuery=this;

			QString lastGroupLastTable; //sirve para generar la condicion de la subconsulta con el padre

			/*el path completo se parte en partes
			ej Tabla7,Tabla6,Tabla5(a),Tabla4,Tabla3,Tabla2(a),Tabla1,Tabla1Col
			se partiria en:
			"Tabla7", "Tabla6"
			"Tabla5(a)", "Tabla4", "Tabla3"
			"Tabla2(a)", "Tabla1"
			*/
			forever
			{
				QString table=lstConsulta.at(c);
				if ( iniciando )
				{
					lstSubCon.append( table );
					iniciando=false;
				}
				else if (( table.contains("(") && table.contains(")")) ||
						 c == lstConsulta.size()-1 )
				{
					//creando la consulta y subconsulta
					//******************************

					//si es la primera vuelta se usa para la primera relacion de la consulta principal,
					//si ya es subconsulta en la primera vuelta de
					//la subconsulta se reemplaza por la primera de la misma
					QString ultimo = tableName;

					TSqlGenerator *subquery;
					//recorremos una parte del camino: 1) "Tabla7", "Tabla6" 2) "Tabla5(a)", "Tabla4", "Tabla3" 3) "Tabla2(a)", "Tabla1"
					for ( int con = 0 ; con < lstSubCon.size(); con++ )
					{
						QString tableori = lstSubCon.at(con);
						QString table = lstSubCon.at(con);
						table.replace( QRegExp("\\(([a-z]|[A-Z]|\\d)+\\)"),"" );

						if ( con == 0 && tableori.contains("(") && tableori.contains(")") && querylevel == 0 )
						{
							lastGroupLastTable=tableName;
							querylevel=1;
						}

						//llenamos lstTableTemp que es el path hasta la tabla table que se usara en getRecordFromPath
						for ( int c=0; c<lstConsulta.size()-1; c++ )
						{
							QString tm = lstConsulta.at(c);
							lstTablesTemp.append(tm);
							if ( lstTablesTemp.last() == tableori )
								break;
						}

						//nos pasamos a la otra tabla, puede que sea el mismo dependiendo del path
						RecordBase *recordtemp = RECORD->getRecordFromPath( lstTablesTemp );

						if ( querylevel == 0 )
						{
							//consulta principal

							//ya que el atributo pasa por tablas con () el atributo a consultar y su pk estarian en una subconsulta
							//no se agrega atributo a consultar ni la pk de su tabla

							addTable(tableori);

							foreach( QString pk,
									 recordtemp->property(QString(table+"PKAttributesList").toLocal8Bit()).toStringList() )
							{
								//agregando la relacion
								addRelation(ultimo,table+"_"+pk,tableori,pk);
								ultimo=table;
							}
						}
						else
						{
							//subconsulta

							if ( con == 0 )
							{
								subquery = new TSqlGenerator(table);
								subquery->setSQLDatabaseDriver( dbDriver );

								if ( querylevel == 1 )
									subquery->setTSqlGParent(this);
								else
									subquery->setTSqlGParent( lastSubQuery );
								subquery->level = querylevel;
								ultimo = table;

								//agregamos la condicion de consulta del grupo anterior con este
								if ( ! lastGroupLastTable.isEmpty() )
								{
									QString id;
									QRegExp rx("\\(([a-z]|[A-Z]|\\d)+\\)");
									QStringList list;
									int pos = 0;

									while ((pos = rx.indexIn(tableori, pos)) != -1)
									{
										list << rx.cap(0);
										pos += rx.matchedLength();
									}
									id = list.at(0);
									id.replace("(","");
									id.replace(")","");

									//agregamos la condicion entre la subconsulta y su padre
									foreach( QString pk,
											 recordtemp->property(QString(table+
																		  "PKAttributesList").toLocal8Bit()).toStringList() )
										subquery->addWhereTaTa( table,
																pk,
																lastGroupLastTable,
																table+"_"+pk+"_"+id+"_",
																TSqlG::EQUAL,TSqlG::AND,false,true);
								}
							}

							//ya estamos en una subconsulta entonces ya se podria agregar el atributo final y su pk si
							//es que ya es el momento

							foreach( QString pk,
									 recordtemp->property(QString(table+"PKAttributesList").toLocal8Bit()).toStringList() )
							{
								//agregando relacion necesaria
								if ( con != 0 )
								{
									subquery->addRelation(ultimo,table+"_"+pk,tableori,pk);
									ultimo=table;
								}
							}

							//agregando el atributo de consulta a la subconsulta si es el momento
							if ( lstConsulta.at( lstConsulta.size()-2 ) == tableori )
							{
								QStringList lstPath = lstConsulta;
								lstPath.removeLast();

								//agregando el campo a consulta
								QString att = lstConsulta.at(lstConsulta.size()-2);
								att.replace(QRegExp("\\(([a-z]|[A-Z]|\\d)+\\)"),"");

								subquery->addSelectAttribute(att,lstConsulta.last());

								//agregando configuracion de consulta al modelo
								subquery->addConfiguredAtt( lstConsulta.last(), lstPath );
							}
						}
						lstTablesTemp.clear();
					}
					//guardamos la ultima tabla para que en el siguiente grupo se haga la condicion
					lastGroupLastTable = lstSubCon.last();

					//agregamos la subconsulta
					if ( querylevel != 0 )
					{
						lastSubQuery->addSelectAttribute( subquery );
						lastSubQuery = subquery;
					}

					querylevel++;
					//******************************

					lstSubCon.clear();
					iniciando=true;
					continue;
				}
				else
					lstSubCon.append( table );

				c++;
				if ( c == lstConsulta.size() )
					break;
			}
		}
		else
		{
			//consulta normal, el atributo no pasa por tablas con varias fk que vienen del mismo pk

			QString ultimo=tableName;
			for ( int con=0; con<lstConsulta.size()-1; con++ )
			{
				QString nt=lstConsulta.at(con); //nueva tabla
				lstTablesTemp.append( nt );

				addTable(nt);

				//nos pasamos a la otra tabla, puede que sea el mismo dependiendo el path
				RecordBase *recordtemp = RECORD->getRecordFromPath( lstTablesTemp );

				foreach( QString pk,
						 recordtemp->property(QString(nt+"PKAttributesList").toLocal8Bit()).toStringList() )
				{
					//si nt es igual a la penultima significa q esa tabla es donde esta el atributo que queremos consultar
					//por lo tanto agregamos la pk de esa tabla
					if ( lstConsulta.at(lstConsulta.size()-2) == nt )
					{
						//agregando la pk de esa tabla
						addSelectAttribute(nt,pk.toLocal8Bit());
						//agregando configuracion de consulta al modelo
						addConfiguredAtt( pk, lstTablesTemp );
					}
					//agregando relacion nesaria
					addRelation(ultimo,nt+"_"+pk,nt,pk);
					ultimo=nt;
				}
			}

			QStringList lstPath = lstConsulta;
			lstPath.removeLast();

			//agregando el campo a consulta
			addSelectAttribute(lstConsulta.at(lstConsulta.size()-2),
							   lstConsulta.last());

			//agregando configuracion de consulta al modelo
			addConfiguredAtt( lstConsulta.last(), lstPath );
		}
	}
	else
	{
		//Atributo de la misma tabla principal

		//agregando pk
		foreach ( QString pk,
				 RECORD->getPKAttributesList() )
		{
			addSelectAttribute(pk.toLocal8Bit());
			addConfiguredAtt( pk );
		}

		//agregando el campo a consulta
		addSelectAttribute(lstConsulta.last());
		addConfiguredAtt( lstConsulta.last() );
	}
}

/*! Agrega una relación a la consulta comparando un atributo de la tabla principal con otro de otra tabla.
  \param attribute1 Atributo de la tabla principal.
  \param table2 Tabla foránea.
  \param table2_attribute Atributo de la otra tabla.
  \param criterio Tipo de relación a realizar. Por defecto INNER JOIN.
*/
void TSqlGenerator::addRelation(QString attribute1,
				 QString table2,
				 QString table2_attribute,
				 TSqlG::criteriaRelation criterio)
{
	addRelation(tableName,attribute1,table2,table2_attribute,criterio);
}

/*! Agrega una relación a la consulta comparando un atributo de la tabla \a table1 con otro de otra de la tabla \a table2.
  \param table1 Tabla 1
  \param attribute1 Atributo de la tabla 1.
  \param table2 Tabla 2.
  \param table2_attribute Atributo de la tabla 2.
  \param criterio Tipo de relación a realizar. Por defecto INNER JOIN.
*/
void TSqlGenerator::addRelation(QString table1,
								QString attribute1,
								QString table2,
								QString table2_attribute,
								TSqlG::criteriaRelation criterio)
{
	addTable( table1 );
	addTable( table2 );

	if ( table2.contains("(") && table2.contains(")") )
	{
		QString id;
		QRegExp rx("\\(([a-z]|[A-Z]|\\d)+\\)");
		QStringList list;
		int pos = 0;

		while ((pos = rx.indexIn(table2, pos)) != -1)
		{
			list << rx.cap(0);
			pos += rx.matchedLength();
		}
		id = list.at(0);
		id.replace("(","");
		id.replace(")","");
		attribute1.append( "_"+id+"_" );
	}
	
	foreach ( TSqlG::relationValue *rcv, lstRelationValues )
	{
		if ( rcv->table1 == table1 && rcv->table2 == table2 &&
				rcv->attribute1 == attribute1 && rcv->table2_attribute == table2_attribute)
			return;
	}

	TSqlG::relationValue *rc = new TSqlG::relationValue;
	rc->table1=table1;
	rc->attribute1=attribute1;
	rc->table2=table2;
	rc->table2_attribute=table2_attribute;
	rc->CriterioRelacion=criterio;

	lstRelationValues.append(rc);
}

void TSqlGenerator::modRelation(QString table2,
				 TSqlG::criteriaRelation criterio)
{
	foreach ( TSqlG::relationValue *rcv, lstRelationValues )
	{
		if ( rcv->table2 == table2 )
		{
			rcv->CriterioRelacion=criterio;
			return;
		}
	}
}

/*! Agregar una condición a la consulta comparando un atributo de la tabla principal con un valor.
  \param attribute Atributo a comparar.
  \param value Valor para comparar.
  \param CriteriaComparation Operador de comparación. Por defecto EQUAL
  \param CriteriaLogic Operador lógico para unir con una condición anterior. Si esta es la primera condicíon en la consulta no se utiliza. Por defecto AND
*/
void TSqlGenerator::addWhereAttribute(QString attribute,
								  QVariant value,
								  TSqlG::criteriaComparation CriteriaComparation,
								  TSqlG::criteriaLogic CriteriaLogic)
{
	addWhereTableAttribute(tableName,attribute,value,
				  CriteriaComparation,
				  CriteriaLogic);
}

/*! Agregar una condición a la consulta comparando un atributo de la tabla \a table con un valor.
  \param table Tabla donde se encuentra el atributo a comparar.
  \param attribute Atributo a comparar.
  \param value Valor para comparar.
  \param CriteriaComparation Operador de comparación. Por defecto EQUAL
  \param CriteriaLogic Operador lógico para unir con una condición anterior. Si esta es la primera condicíon en la consulta no se utiliza. Por defecto AND
*/
void TSqlGenerator::addWhereTableAttribute(QString table,
								  QString attribute,
								  QVariant value,
								  TSqlG::criteriaComparation CriteriaComparation,
								  TSqlG::criteriaLogic CriteriaLogic)
{
	TSqlG::whereAttributeValue *wc = new TSqlG::whereAttributeValue;
	wc->table=table;
	wc->attribute=attribute;
	wc->CriteriaComparation=CriteriaComparation;
	wc->CriteriaLogic=CriteriaLogic;
	wc->value=value;

	lstWhereAttributes.append(wc);
}

/*! Agregar una condición a la consulta comparando un atributo de la tabla \a table1 con otro de la tabla \a table2.
  \param table1 Tabla donde se encuentra el atributo 1 a comparar.
  \param attribute1 Atributo 1 a comparar.
  \param table2 Tabla donde se encuentra el atributo 2 a comparar.
  \param attribute2 Atributo 2 a comparar.
  \param CriteriaComparation Operador de comparación. Por defecto EQUAL
  \param CriteriaLogic Operador lógico para unir con una condición anterior. Si esta es la primera condicíon en la consulta no se utiliza. Por defecto AND
*/
void TSqlGenerator::addWhereTaTa(QString table1,
								 QString attribute1,
								 QString table2,
								 QString attribute2,
								 TSqlG::criteriaComparation CriteriaComparation,
								 TSqlG::criteriaLogic CriteriaLogic,
								 bool Table1inParent,
								 bool Table2inParent)
{
	TSqlG::whereAttributeValue *wc = new TSqlG::whereAttributeValue;
	wc->table=table1;
	wc->attribute=attribute1;
	wc->table2=table2;
	wc->attribute2=attribute2;
	wc->CriteriaComparation=CriteriaComparation;
	wc->CriteriaLogic=CriteriaLogic;
	wc->table1inParent=Table1inParent;
	wc->table2inParent=Table2inParent;
	lstWhereAttributes.append(wc);
}

//! Agrega un simbolo '(' en la consulta para iniciar un grupo en la condición.
void TSqlGenerator::addWhereStartGroup()
{
	TSqlG::whereAttributeValue *wc = new TSqlG::whereAttributeValue;
	wc->grupoInicio=true;
	lstWhereAttributes.append(wc);
}

//! Agrega un simbolo ')' en la consulta para finalizar un grupo en la condición.
void TSqlGenerator::addWhereEndGroup()
{
	TSqlG::whereAttributeValue *wc = new TSqlG::whereAttributeValue;
	wc->grupoFinal=true;
	lstWhereAttributes.append(wc);
}

void TSqlGenerator::addGroupBy(QString attribute,
                               TSqlG::criteriaOrder criterio)
{
    TSqlG::groupByAttribute* gba = new TSqlG::groupByAttribute;
    gba->attribute=attribute;
    gba->CriteriaOrder=criterio;
    lstGroupByAttributes.append( gba );
}

void TSqlGenerator::addHaving(QString attribute,
                              QVariant value,
                              TSqlG::criteriaComparation CriteriaComparation,
                              TSqlG::criteriaLogic CriteriaLogic)
{
    TSqlG::havingAttribute* ha = new TSqlG::havingAttribute;
    ha->attribute=attribute;
    ha->value=value;
    ha->CriteriaComparation=CriteriaComparation;
    ha->CriteriaLogic=CriteriaLogic;
    lstHavingAttributes.append( ha );
}

/*! Agrega un tipo de orden para un atributo de una tabla en la consulta.
  \param attribute Atributo a ordenar.
  \param criterio Como se debe ordenar el atributo \a attribute. Por defecto ASC.
*/
void TSqlGenerator::addOrderBy(QString attribute,TSqlG::criteriaOrder criterio)
{
	addOrderBy(tableName,attribute,criterio);
}

/*! Agrega un tipo de orden para un atributo en la consulta.
  \param table Tabla del atributo
  \param attribute Atributo a ordenar.
  \param criterio Como se debe ordenar el atributo \a attribute. Por defecto ASC.
*/
void TSqlGenerator::addOrderBy(QString table,QString attribute,TSqlG::criteriaOrder criterio)
{
	TSqlG::orderAttributeValue *oc = new TSqlG::orderAttributeValue;
	oc->attribute=attribute;
	oc->table=table;
	oc->CriteriaOrder=criterio;

	lstOrderAttributes.append(oc);
}

/*! Establece el limite de la consulta.
  \param l Limite de la consulta.
*/
void TSqlGenerator::setLimit(int l)
{
	if ( l>0 )
		limite=l;
}

/*! Establece el offset de la consulta.
  \param o Offset de la consulta.
*/
void TSqlGenerator::setOffset(int o) { offset=o; }

QList<confInsertValue*> TSqlGenerator::getLstCIV() { return lstCIV; }

//para update

/*! Agrega un atributo para modificar o insertar.
  \param attribute Atributo para modificar o insertar.
  \param value Valor a establecerle al atributo.
*/
void TSqlGenerator::addUpdateAttribute(QString attribute,
								   QVariant value)
{
	TSqlG::updateInsertSetAttributeValue *v=new TSqlG::updateInsertSetAttributeValue;
	v->attribute=attribute;
	v->value=value;
	lstUpdateSetAttributes.append(v);
}

/*! Agrega un registro completo para insertar.
  \param f Registro a insertar.
*/
void TSqlGenerator::addInsertAttribute(RecordBase *f)
{
	lstInsertRecord.append(f);
}

/*! Agrega un atributo para insertar.
  \param attribute Atributo a insertar.
  \param value Valor del atributo a insertar.
*/
void TSqlGenerator::addInsertAttribute(QString attribute,
					QVariant value)
{
	TSqlG::updateInsertSetAttributeValue *v = new TSqlG::updateInsertSetAttributeValue;
	v->attribute=attribute;
	v->value=value;
	lstInsertAttributes.append(v);
}



/*! Genera la consulta completa y la devuelve.
  \return Consulta completa.
*/
QString TSqlGenerator::getSelectQuery(bool withOffsetLimit)
{
	if ( plataform == NULL )
	{
		qDebug() << "TSqlGenerator: No se ha especificado el driver de la base de datos";
		return "";
	}

	return plataform->getSelectQuery(withOffsetLimit);
}

/*! Devuelve la actualización de atributos.
  \return Código de actualización de atributos.
*/
QString TSqlGenerator::getUpdateQuery()
{
	if ( plataform == NULL )
	{
		qDebug() << "TSqlGenerator: No se ha especificado el driver de la base de datos";
		return "";
	}

	return plataform->getUpdateQuery();
}

QString TSqlGenerator::getDeleteQuery()
{
	if ( plataform == NULL )
	{
		qDebug() << "TSqlGenerator: No se ha especificado el driver de la base de datos";
		return "";
	}

	return plataform->getDeleteQuery();
}

/*! Devuelve el código para insertar en la base de datos.
  \return Código para insertar.
*/
QString TSqlGenerator::getInsertQuery()
{
	if ( plataform == NULL )
	{
		qDebug() << "TSqlGenerator: No se ha especificado el driver de la base de datos";
		return "";
	}

	return plataform->getInsertQuery();
}
