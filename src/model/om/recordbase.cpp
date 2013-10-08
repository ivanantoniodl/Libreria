#include "recordbase.h"
#include "tsqlgenerator.h"
#include "tsqlerror.h"

/*! Contructor.
  El padre del registro puede ser nulo u otro registro.

  Un objeto que tiene atributos que representan llaves foráneas será el padre de los objetos que regresentan a las tablas foráneas.

  \param qparent Padre del objeto.
  \param rparent Padre del registro.

  \b Ejemplo:

  Tabla: Lugar\n
  Llave primaria: idLugar\n

  Tabla: Persona\n
  Llave primaria: idPersona\n
  Llave foranea: Lugar_idLugar\n

  Persona padre de Lugar.

  Esta relación de padres e hijos se utiliza entre la clase instanciada y sus miembros heredados de Record que representan sus llaves foraneas.
*/

RecordBase::RecordBase(QObject *qparent,
					   RecordBase *rparent,
					   QSqlDatabase db) :
	QObject(qparent),PARENT(rparent),QPARENT(qparent),DB(db)
{
	 enabledRecordBackup=true;
	 enableExtension=false;
	 enabledInsertUpdateOnlyHaveChanged=true;
	 recordbaseissettingattsvalues=false;
}

/*! Establece el padre del registro
\param rparent Registro padre
*/
void RecordBase::setRParent(RecordBase *rparent) { PARENT=rparent; }

/*! Establece el padre del objeto
\param qparent Objeto padre
*/
void RecordBase::setQParent(QObject *qparent)
{
	QPARENT=qparent;
	QObject::setParent(qparent);
}

bool RecordBase::isExtensionEnabled() { return enableExtension; }

/*! Regresa el nombre de la tabla
\return Nombre de la tabla
*/
QString RecordBase::tableName() { return TABLENAME; }

void RecordBase::showLastQuery(QString msg)
{
#if defined(QANTDEBUG)
	qDebug() << "Tabla: "+TABLENAME +": "+msg+": "+LASTQUERY;
#else
	Q_UNUSED(msg)
#endif
}

/*! Establece valores a los atributos del registro.
Esta función se encarga de guardar el resultado de una consulta a sus respectivos atributos. Se utiliza la configuración de la consulta realizada.

\param query Consulta a utilizar

\b Ejemplo:

Configuración:

\code
idPersona -> Primer valor de la consulta se guarda en el atributo idPersona
Nombre -> Segundo valor de la consulta se guarda en el atributo Nombre
Lugar,Nombre -> Se salta a la tabla Lugar y el tercer valor de la consulta se guarda en el atributo Nombre
Lugar,Tipo,Nombre -> Se salta a la tabla Lugar, luego se salta a la tabla Tipo y el cuarto valor de la consulta se guarda en el atributo Nombre
\endcode

*/
void RecordBase::setRecordValues(QSqlQuery& query)
{
	int pos=0;
	query.first();

	//modificar query size
	if ( query.size() == 1 )
	{
		enabledRecordBackup=false;
		foreach ( QString attribute, getAttributesList() )
			setProperty( attribute.toLocal8Bit() , query.value(pos++) );
		enabledRecordBackup=true;
		lstAttInsertUpdate.clear();
		emit hasValuesWithOutSave(false,this);
	}
}

bool RecordBase::verifyValue(QVariant value)
{
	switch ( value.type() )
	{
		case QVariant::Bool:
			return true;
		case QVariant::Date:
			return value.toDate().isValid();
		case QVariant::DateTime:
		{
			QDateTime dt=value.toDateTime();
			if ( dt.date().isValid() && dt.time().isValid() )
				return true;
			else
				return false;
		}
		case QVariant::Time:
			return value.toTime().isValid();
		case QVariant::Double:
			return ( value.toDouble() > 0 ? true : false );
		case QVariant::Int:
			return ( value.toInt() > 0 ? true : false );
		case QVariant::LongLong:
			return ( value.toLongLong() > 0 ? true : false );
		case QVariant::UInt:
			return ( value.toUInt() > 0 ? true : false );
		case QVariant::ULongLong:
			return ( value.toULongLong() > 0 ? true : false );
		case QVariant::String:
			return !value.toString().isEmpty();
		default:
			return false;
	}
}

void RecordBase::setRecordBaseIsSettingAttsValues(bool issetting )
{
	recordbaseissettingattsvalues=issetting;
	if ( ! ISBACKUPRECORUSELOCALATT )
		getBackUpRecord()->setRecordBaseIsSettingAttsValues( issetting );
}

void RecordBase::addAttributeInsertUpdate(QString c)
{
	if ( ! lstAttInsertUpdate.contains(c) )
		lstAttInsertUpdate.append( c );

	if ( ! recordbaseissettingattsvalues )
		emit hasValuesWithOutSave(true,this);
}

/*!  Agrega un atributo a la lista de atributos a no incluir cuando se actualiza o insertan un registro.

Cuando se ejecuta apply() se verifica si la llave primaria tiene un valor valido, si lo tiene se genera una consulta SQL UPDATE,
si no lo tiene se genera una consulta SQL INSERT. Al generar estas consultas se actualizan o insertan todos los atributos, si no se desea que se actualice o inserte un atributo se utiliza esta función.

\param att Atributo a excluir.
*/
void RecordBase::addAttributeNoInsertUpdate(QString att)
{
	lstAttInsertUpdate.removeAt( lstAttInsertUpdate.indexOf( att ) );
	emit hasValuesWithOutSave( lstAttInsertUpdate.size() > 0 ? true : false,this );
}

void RecordBase::setEnabledInsertUpdateOnlyHaveChanged(bool enabled) { enabledInsertUpdateOnlyHaveChanged=enabled; }

QString RecordBase::lastQuery()
{
	return LASTQUERY;
}

QVariantList RecordBase::getPKAttributesValuesList()
{
	QVariantList values;
	foreach ( QString att, getPKAttributesList() )
		values.append( property( att.toLocal8Bit() ) );

	return values;
}

bool RecordBase::comparePK(RecordBase* other)
{
	QVariantList thisPkValues = getPKAttributesValuesList();
	QVariantList otherPkValues = other->getPKAttributesValuesList();

	if ( thisPkValues.size() != otherPkValues.size() )
		return false;

	for ( int c=0; c<thisPkValues.size(); c++ )
	{
		if ( thisPkValues.at( c ) != otherPkValues.at(c) )
			return false;
	}
	return true;
}

void RecordBase::revert()
{
	getBackUpRecord()->clear();
	lstAttInsertUpdate.clear();
	emit hasValuesWithOutSave(false,this);
}

RecordBase* RecordBase::getRecordFromPath(QStringList path,
										  bool pathIncludeAttribute)
{
	RecordBase *ultimoRec=this;

	if ( path.isEmpty() )
		return ultimoRec;

	if ( pathIncludeAttribute )
		path.removeLast(); //quitamos el atributo

	for ( int c=0;;c++ )
	{
		QStringList lstTables = ultimoRec->lstTables;
		if ( path.size() >= lstTables.size() )
		{
			lstTables.removeFirst(); //quitamos la primera tabla que es la tabla en donde esta el record

			for ( int f=0; f<lstTables.size(); f++ )
				path.removeFirst();

			//nos pasamos a la otra tabla
			if ( path.first().contains("(") && path.first().contains(")") )
			{
				//el atributo pertenece a una tabla donde hay varios FK que apuntan a la misma PK
				QRegExp rx("\\(([a-z]|[A-Z]|\\d)+\\)");
				QStringList list;
				int pos = 0;
				while ((pos = rx.indexIn(path.first(), pos)) != -1)
				{
					list << rx.cap(0);
					pos += rx.matchedLength();
				}

				QString id = list.at(0);
				id.replace("(","");
				id.replace(")","");

				QString property = path.first();
				property.replace(rx,"");
				property="R"+property+"_"+id+"_";

				ultimoRec = ultimoRec->property(property.toLocal8Bit()).value<RecordBase*>();
			}
			else
				ultimoRec = ultimoRec->property(QString("R"+path.first()+"_").toLocal8Bit()).value<RecordBase*>();

			path.removeFirst();

			if ( path.size() == 0 )
				return ultimoRec;
		}
		else
			//lstTables es mayor que path, significa que estamos en el record
			//que contiene el atributo que necesitamos
			return ultimoRec;
	}
}

//RecordSimpleBase
//***********************************************************************************************************

RecordSimpleBase::RecordSimpleBase(QObject *qparent,
								   RecordBase *rparent,
								   QSqlDatabase db) :
	RecordBase(qparent,rparent,db)
{
}

/*! Actualiza el contenido del registro consultando la base de datos.

\return Estado de la consulta realizada
*/
TSqlError RecordSimpleBase::update()
{
	TSqlError error;
	TSqlGenerator sg(TABLENAME,&DB);

	//verificando que las llaves primarias tengan asignados valores
	foreach( QString pk, getPKAttributesList() )
	{
		QVariant value = property(pk.toLocal8Bit());
		if ( ! verifyValue( value ) )
		{
			error.setType( QSqlError::UnknownError );
			error.RecordMessage="Update: El atributo "+
					pk+" que pertenece a la llave primaria de la tabla "+
					TABLENAME+" no tiene asignado un valor";
			error.showMessages();
			return error;
		}
		sg.addWhereAttribute( pk , value );
	}

	//agregando los atributos a actualizar
	foreach ( QString attribute, lstAttInsertUpdate )
		sg.addUpdateAttribute( attribute, property(attribute.toLocal8Bit()));

	LASTQUERY=sg.getUpdateQuery();
	QSqlQuery query(DB);
	query.prepare( LASTQUERY );

	//si el registro tiene datos binarios como blob se asignan esos valores para la consulta
	if ( LASTQUERY.contains(":BINDVALUE") )
	{
		QRegExp rx(":BINDVALUE.+VALUE");
		QStringList list;
		int pos = 0;

		while ((pos = rx.indexIn(LASTQUERY, pos)) != -1) {
			list << rx.cap(0);
			pos += rx.matchedLength();
		}

		foreach ( QString str, list )
		{
			QString att = str;
			att = att.left( att.size() - 5 );
			att = att.right( att.size() - 10 );

			query.bindValue(str, property(att.toLocal8Bit()).toByteArray() );
		}
	}
	query.exec();

	error.RecordMessage = "Update: Error al actualizar los atributos";
	error.RecordQuery = LASTQUERY;
	error = query.lastError();

	if ( error.type() == QSqlError::NoError )
	{
		showLastQuery("Update");

		//aplicando los cambios hechos en el backup al principal
		enabledRecordBackup=false;
		foreach ( QString att, lstAttInsertUpdate )
			setProperty( att.toLocal8Bit(), getBackUpRecord()->property( att.toLocal8Bit() ) );
		enabledRecordBackup=true;
		lstAttInsertUpdate.clear();
		emit hasValuesWithOutSave(false,this);
	}

	return error;
}

TSqlError RecordSimpleBase::select()
{
	TSqlError error;
	if ( PARENT != NULL )
	{
		error.setType( QSqlError::UnknownError );
		error.RecordMessage = "Select: Attribute hijo de otro campo, no se puede actualizar";
		error.showMessages();
		return error;
	}

	TSqlGenerator sg(TABLENAME,&DB);
	sg.setLimit(1);

	//verificando que las llaves primarias tengan asignados valores
	foreach( QString pk, getPKAttributesList() )
	{
		QVariant value = property(pk.toLocal8Bit());
		if ( ! verifyValue( value ) )
		{
			error.setType( QSqlError::UnknownError );
			error.RecordMessage="Select: El atributo "+
					pk+" que pertenece a la llave primaria de la tabla "+
					TABLENAME+" no tiene asignado un valor";
			error.showMessages();
			return error;
		}
		sg.addWhereAttribute( pk , value );
	}

	LASTQUERY=sg.getSelectQuery();
	QSqlQuery query(LASTQUERY,DB);

	error.RecordMessage = "Select: Error al seleccionar los atributos";
	error.RecordQuery = LASTQUERY;
	error = query.lastError();

	if ( error.type() == QSqlError::NoError )
	{
		showLastQuery("Select");
		setRecordValues(query);
	}

	return error;
}

TSqlError RecordSimpleBase::insert()
{
	TSqlError error;

	//verificando que las llaves primarias tengan asignados valores
	foreach( QString pk, getPKAttributesList() )
	{
		//verificando si el atributo de la llave primaria es autoincrementable
		if ( getPKAutoIncrementAttributesList().contains(pk) )
		{
			qDebug() << TABLENAME << ": Insert: El atributo autoincrementable ya contiene un valor, al insertar" <<
						"el nuevo registro el autoincrementable cambiara.";
			continue;
		}

		QVariant value = property(pk.toLocal8Bit());

		if ( ! verifyValue( value ) )
		{
			error.setType( QSqlError::UnknownError );
			error.RecordMessage="Insert: El atributo "+
					pk+" que pertenece a la llave primaria de la tabla "+
					TABLENAME+" no tiene asignado un valor";
			error.showMessages();
			return error;
		}
	}

	TSqlGenerator sg(TABLENAME,&DB);

	//Lista de atributos a insertar, si enabledInsertUpdateOnlyHaveChanged es verdadero solo se insertan
	//los atributos que se modificaron si no se insertan en la consulta todos los atributos.
	QStringList lstAtts;
	if ( enabledInsertUpdateOnlyHaveChanged )
		lstAtts = lstAttInsertUpdate;
	else
		lstAtts = getAttributesList();

	//insertar nuevo registro
	foreach ( QString attribute, lstAtts )
	{
		if ( getPKAutoIncrementAttributesList().contains(attribute) )
			continue;

		sg.addInsertAttribute( attribute, property(attribute.toLocal8Bit()));
	}

	//iniciamos transaccion
	if ( DB.driver()->hasFeature( QSqlDriver::Transactions ) )
		DB.transaction();
	else
		qDebug() << "RecordSimpleBase: Insert: " << DB.driverName() << " No soporta transacciones";

	LASTQUERY=sg.getInsertQuery();
	QSqlQuery query(DB);
	query.prepare( LASTQUERY );

	//si el registro tiene datos binarios como blob se asignan esos valores para la consulta
	if ( LASTQUERY.contains(":BINDVALUE") )
	{
		QRegExp rx(":BINDVALUE.+VALUE");
		QStringList list;
		int pos = 0;

		while ((pos = rx.indexIn(LASTQUERY, pos)) != -1) {
			list << rx.cap(0);
			pos += rx.matchedLength();
		}

		foreach ( QString str, list )
		{
			QString att = str;
			att = att.left( att.size() - 5 );
			att = att.right( att.size() - 10 );

			query.bindValue(str, property(att.toLocal8Bit()).toByteArray() );
		}
	}
	query.exec();

	error.RecordMessage = "Insert: Error al insertar los atributos";
	error.RecordQuery = LASTQUERY;
	error = query.lastError();

	if ( error.type() == QSqlError::NoError )
	{
		showLastQuery("Insert");

		//aplicando los cambios hechos en el backup al principal
		enabledRecordBackup=false;
		foreach ( QString att, lstAttInsertUpdate )
			setProperty( att.toLocal8Bit(), getBackUpRecord()->property( att.toLocal8Bit() ) );
		enabledRecordBackup=true;
		lstAttInsertUpdate.clear();
		emit hasValuesWithOutSave(false,this);

		setRecordBaseIsSettingAttsValues(true);

		//Si tiene autoincrementable o datestamp consultamos el ultimo insertado para obtener el valor que se asigno
		if ( getPKAutoIncrementAttributesList().size() > 0  &&
			 getDateTimeAttributesList().size() > 0 )
		{
			//se consulta el autoincrementable y el de fecha
			QSqlQuery query("Select max("+getPKAutoIncrementAttributesList().at(0)+"),max("+
							getDateTimeAttributesList().at(0)+") from "+TABLENAME);			
			query.first();
			setProperty( getPKAutoIncrementAttributesList().at(0).toLocal8Bit(),
						 query.value(0) );
			setProperty( getDateTimeAttributesList().at(0).toLocal8Bit(),
						 query.value(1) );
		}
		else if ( getPKAutoIncrementAttributesList().size() > 0  &&
				  getDateTimeAttributesList().size() == 0)
		{
			//se consulta el autoincrementable
			QSqlQuery query("Select max("+getPKAutoIncrementAttributesList().at(0)+") from "+
							TABLENAME);
			query.first();
			setProperty( getPKAutoIncrementAttributesList().at(0).toLocal8Bit(),
						 query.value(0) );
		}
		else if ( getPKAutoIncrementAttributesList().size() == 0  &&
				  getDateTimeAttributesList().size() > 0 )
		{
			//se consulta la fecha
			QSqlQuery query("Select max("+getDateTimeAttributesList().at(0)+") from "+
							TABLENAME);
			query.first();
			setProperty( getDateTimeAttributesList().at(0).toLocal8Bit(),
						 query.value(0) );
		}

		setRecordBaseIsSettingAttsValues(false);

		DB.commit();
	}
	else
		DB.rollback();

	return error;
}

TSqlError RecordSimpleBase::delete_()
{
	TSqlError error;
	TSqlGenerator sg(TABLENAME,&DB);

	//verificando que las llaves primarias tengan asignados valores
	foreach( QString pk, getPKAttributesList() )
	{
		QVariant value = property(pk.toLocal8Bit());

		if ( ! verifyValue( value ) )
		{
			error.setType( QSqlError::UnknownError );
			error.RecordMessage="Delete: El atributo "+
					pk+" que pertenece a la llave primaria de la tabla "+
					TABLENAME+" no tiene asignado un valor";
			error.showMessages();
			return error;
		}
		sg.addWhereAttribute( pk, value );
	}

	LASTQUERY=sg.getDeleteQuery();
	QSqlQuery query(LASTQUERY,DB);

	error.RecordMessage = "Delete: Error al eliminar el registro";
	error.RecordQuery = LASTQUERY;
	error = query.lastError();

	if ( error.type() == QSqlError::NoError )
		showLastQuery("Delete");

	return error;
}

//RecordInheritsBase
//***********************************************************************************************************

RecordInheritsBase::RecordInheritsBase(QObject *qparent,
									   RecordBase *rparent,
									   QSqlDatabase db) :
	RecordBase(qparent,rparent,db)
{
}

TSqlError RecordInheritsBase::update()
{
	TSqlError error;

	//iniciamos transaccion
	if ( DB.driver()->hasFeature( QSqlDriver::Transactions ) )
		DB.transaction();
	else
		qDebug() << "RecordInheritsBase: Update: " << DB.driverName() << " No soporta transacciones";

	QString executedQuerys;

	foreach ( QString table, lstTables )
	{
		TSqlGenerator sg(table,&DB);

		//agregando los atributos a actualizar
		bool valuesToUpdate = false;
		foreach ( QString attribute, property( QString(table+"AttributesList").toLocal8Bit() ).toStringList() )
		{
			if ( lstAttInsertUpdate.contains( attribute ) )
			{
				sg.addUpdateAttribute( attribute, property(attribute.toLocal8Bit()));
				valuesToUpdate=true;
			}
		}

		//si no hay atributos que actualizar de esta tabla seguimos con la siguiente
		if ( !valuesToUpdate )
			continue;

		//verificando que las llaves primarias tengan asignados valores
		foreach( QString pk, property( QString(table+"PKAttributesList").toLocal8Bit() ).toStringList() )
		{
			QVariant value = property(pk.toLocal8Bit());

			if ( ! verifyValue( value ) )
			{
				error.setType( QSqlError::UnknownError );
				error.RecordMessage="Update: La llave primaria "+
						pk+" que pertenece al conjuto de tablas de las que hereda "+
						TABLENAME+" no tiene asignado un valor";
				error.showMessages();
				DB.rollback();
				return error;
			}
			sg.addWhereAttribute( pk , value );
		}

		LASTQUERY=sg.getUpdateQuery();
		QSqlQuery query(DB);
		query.prepare( LASTQUERY );

		//si el registro tiene datos binarios como blob se asignan esos valores para la consulta
		if ( LASTQUERY.contains(":BINDVALUE") )
		{
			QRegExp rx(":BINDVALUE.+VALUE");
			QStringList list;
			int pos = 0;

			while ((pos = rx.indexIn(LASTQUERY, pos)) != -1) {
				list << rx.cap(0);
				pos += rx.matchedLength();
			}

			foreach ( QString str, list )
			{
				QString att = str;
				att = att.left( att.size() - 5 );
				att = att.right( att.size() - 10 );

				query.bindValue(str, property(att.toLocal8Bit()).toByteArray() );
			}
		}
		query.exec();

		error.clear();
		error.RecordMessage = "Update: Error al actualizar los atributos";
		error.RecordQuery = executedQuerys+LASTQUERY;
		error = query.lastError();

		if ( error.type() != QSqlError::NoError )
		{
			DB.rollback();
			return error;
		}

		showLastQuery("Update");
		executedQuerys+="Consulta ejecutada correctamente: "+LASTQUERY+"\n\n";
	}

	//aplicando los cambios hechos en el backup al principal
	enabledRecordBackup=false;
	foreach ( QString att, lstAttInsertUpdate )
		setProperty( att.toLocal8Bit(), getBackUpRecord()->property( att.toLocal8Bit() ) );
	enabledRecordBackup=true;
	lstAttInsertUpdate.clear();
	emit hasValuesWithOutSave( false,this );

	DB.commit();
	return error;
}

TSqlError RecordInheritsBase::select()
{
	if ( PARENT != NULL )
	{
		TSqlError error;
		error.setType( QSqlError::UnknownError );
		error.RecordMessage = "Select: Attribute hijo de otro campo, no se puede actualizar";
		error.showMessages();
		return error;
	}

	TSqlGenerator sg(TABLENAME,&DB);
	sg.setLimit(1);

	QStringList lstT;
	foreach( QString table, lstTables )
	{
		if ( table != TABLENAME )
			lstT.append(table);

		//preparando la ruta del atributo
		QString path;
		foreach ( QString t, lstT )
		{
			if ( path.isEmpty() )
				path=t;
			else
				path+=","+t;
		}

		//agregando los atributos de todas las tablas a la consulta
		foreach ( QString att, property(QString(table+"AttributesList").toLocal8Bit()).toStringList() )
		{
			if ( path.isEmpty() )
				sg.addAttributeToSelect(getLastChildDefaultRecord(),att);
			else
				sg.addAttributeToSelect(getLastChildDefaultRecord(),path+","+att);
		}

		//agregando las condiciones segun las llaves primarias de todas las tablas
		foreach ( QString pk, property( QString(table+"PKAttributesList").toLocal8Bit() ).toStringList() )
		{
			QVariant value = property(pk.toLocal8Bit());
			if ( ! verifyValue( value ) )
			{
				TSqlError error;
				error.setType( QSqlError::UnknownError );
				error.RecordMessage="Select: La llave primaria "+
						pk+" de la tabla "+table+
						" que pertenece al conjuto de tablas de las que hereda "+
						TABLENAME+" no tiene asignado un valor";
				error.showMessages();
				return error;
			}
			sg.addWhereTableAttribute(table,pk,value);
		}
	}

	LASTQUERY=sg.getSelectQuery();
	QSqlQuery query(LASTQUERY,DB);

	TSqlError error;
	error.RecordMessage = "Select: Error al seleccionar los atributos";
	error.RecordQuery = LASTQUERY;
	error = query.lastError();

	if ( error.type() == QSqlError::NoError )
	{
		showLastQuery("Select");
		setRecordValues(query);
	}

	return error;
}

TSqlError RecordInheritsBase::insert()
{
	TSqlError error;

	//iniciamos transaccion
	if ( DB.driver()->hasFeature( QSqlDriver::Transactions ) )
		DB.transaction();
	else
		qDebug() << "RecordInheritsBase: Insert: " << DB.driverName() << " No soporta transacciones";

	QString executedQuerys;

	//lstTables contiene las tablas desde el hijo hasta el padre mayor, necesitamos insertar los datos al contrario
	//del padre mayor hasta el ultimo hijo
	for ( int c=lstTables.size()-1; c>=0; c-- )
	{
		QString table = lstTables.at(c);
		TSqlGenerator sg(table,&DB);

		//verificando que las llaves primarias tengan asignados valores
		foreach( QString pk, property( QString(table+"PKAttributesList").toLocal8Bit() ).toStringList() )
		{
			//verificando si el atributo de la llave primaria es autoincrementable, la bd establece ese valor
			if ( property( QString(table+"PKAutoIncrementAttribute").toLocal8Bit() ).toString() == pk )
				continue;

			//Como pueden haber varias pk en una tabla, puede que hayan de tipo date o datetime, si las hay
			//se asume que es la BD la que asignará ese valor
			if ( property( QString(table+"DateTimeAttributesList").toLocal8Bit() ).toString() == pk )
				continue;

			QVariant value = property(pk.toLocal8Bit());

			if ( ! verifyValue( value ) )
			{
				error.setType(QSqlError::UnknownError);
				error.RecordMessage="Insert: La llave primaria "+
						pk+" que pertenece al conjuto de tablas de las que hereda "+
						TABLENAME+" no tiene asignado un valor";
				error.showMessages();
				DB.rollback();
				return error;
			}
		}

		//Lista de atributos a insertar, si enabledInsertUpdateOnlyHaveChanged es verdadero solo se insertan
		//los atributos que se modificaron si no se insertan en la consulta todos los atributos.
		QStringList lstAtts;
		if ( enabledInsertUpdateOnlyHaveChanged )
		{
			foreach ( QString att,property( QString(table+"AttributesList").toLocal8Bit()).toStringList() )
				if ( lstAttInsertUpdate.contains( att ) )
					lstAtts.append(att);
		}
		else
			lstAtts = property( QString(table+"AttributesList").toLocal8Bit() ).toStringList();

		if ( lstAtts.isEmpty() )
		{
			error.setType(QSqlError::UnknownError);
			error.RecordMessage="Insert: La tabla "+table+
					" que es padre de la tabla "+TABLENAME+" no tiene atributos para insertar";
			error.showMessages();
			DB.rollback();
			return error;
		}

		//generando el insert
		foreach ( QString att, lstAtts )
		{
			//verificando si el atributo es autoincrementable
			if ( property( QString(table+"PKAutoIncrementAttribute").toLocal8Bit() ).toString() == att )
				continue;

			//verificando si el atributo es date o datetime de pk
			if ( property( QString(table+"PKAttributesList").toLocal8Bit() ).toStringList().contains(att) &&
				 property( QString(table+"DateTimeAttributesList").toLocal8Bit() ).toString() == att )
				continue;

			sg.addInsertAttribute( att, property(att.toLocal8Bit()));
		}

		LASTQUERY=sg.getInsertQuery();
		QSqlQuery query(DB);
		query.prepare( LASTQUERY );

		//si el registro tiene datos binarios como blob se asignan esos valores para la consulta
		if ( LASTQUERY.contains(":BINDVALUE") )
		{
			QRegExp rx(":BINDVALUE.+VALUE");
			QStringList list;
			int pos = 0;

			while ((pos = rx.indexIn(LASTQUERY, pos)) != -1) {
				list << rx.cap(0);
				pos += rx.matchedLength();
			}

			foreach ( QString str, list )
			{
				QString att = str;
				att = att.left( att.size() - 5 );
				att = att.right( att.size() - 10 );

				query.bindValue(str, property(att.toLocal8Bit()).toByteArray() );
			}
		}
		query.exec();

		error.clear();
		error.RecordMessage = "Insert: Error al insertar los atributos";
		error.RecordQuery = executedQuerys+"\n--Ultima consulta: "+LASTQUERY;
		error = query.lastError();

		if ( error.type() != QSqlError::NoError )
		{
			lstAttInsertUpdate.clear();
			DB.rollback();
			return error;
		}

		showLastQuery("Insert");
		executedQuerys+="\n--Consulta ejecutada correctamente: "+LASTQUERY;

		//estableciendo valores a las llaves foraneas que son primarias del padre que se acaba de insertar
		//estableciendo valores a los atributos que la base de datos asigna

		//buscando si hay atributos que hayan sido establecidos por la base de datos para consultarlos
		QString dt=property( QString(table+"DateTimeAttributesList").toLocal8Bit()).toString();
		QString pkau=property( QString(table+"PKAutoIncrementAttribute").toLocal8Bit()).toString();
		QStringList pklst=property( QString(table+"PKAttributesList").toLocal8Bit()).toStringList();
		QStringList asignedValues;

		error.clear();
		error.RecordMessage = "Insert: Error al consultar los datos asignados por la BD de la tabla "+
				table;
		error.RecordQuery = executedQuerys+" "+LASTQUERY;

		setRecordBaseIsSettingAttsValues(true); //iniciando mofificacion de atributos

		if ( !dt.isEmpty() && !pkau.isEmpty() )
		{
			//consultar tipo tiempo y autoincrementable
			QSqlQuery query( "Select max("+dt+"),max("+pkau+")"+
							 " from "+table,DB );
			error=query.lastError();
			if ( error.type() != QSqlError::NoError )
			{
				DB.rollback();
				return error;
			}
			query.first();
			setProperty( QString(dt).toLocal8Bit(),query.value(0) );
			setProperty( QString(pkau).toLocal8Bit(), query.value(1) );
			setProperty( QString(table+"_"+dt).toLocal8Bit(),query.value(0) );
			setProperty( QString(table+"_"+pkau).toLocal8Bit(), query.value(1) );
			asignedValues.append( dt );
			asignedValues.append( pkau );
		}
		else if ( dt.isEmpty() && !pkau.isEmpty() )
		{
			//consultar solo el autoincrementable
			QSqlQuery query( "Select max("+pkau+")"+
							 " from "+table,DB );
			error=query.lastError();
			if ( error.type() != QSqlError::NoError )
			{
				DB.rollback();
				return error;
			}
			query.first();
			setProperty( QString(pkau).toLocal8Bit(), query.value(0) );
			setProperty( QString(table+"_"+pkau).toLocal8Bit(), query.value(0) );
			asignedValues.append( pkau );
		}
		else if ( !dt.isEmpty() && pkau.isEmpty() )
		{
			//consultar el de tiempo
			QSqlQuery query( "Select max("+dt+")"+
							 " from "+table,DB );
			error=query.lastError();
			if ( error.type() != QSqlError::NoError )
			{
				DB.rollback();
				return error;
			}
			query.first();
			setProperty( QString(dt).toLocal8Bit(),query.value(0) );
			setProperty( QString(table+"_"+dt).toLocal8Bit(),query.value(0) );
			asignedValues.append( dt );
		}

		//asignando los valores a las llaves foraneas que no se llenaron
		foreach ( QString pk, pklst )
		{
			if ( asignedValues.contains( pk ) )
				continue;
			setProperty( QString(table+"_"+pk).toLocal8Bit(), property( pk.toLocal8Bit() ) );
		}

		setRecordBaseIsSettingAttsValues(false);
	}

	//aplicando los cambios hechos en el backup al principal
	enabledRecordBackup=false;
	foreach ( QString att, lstAttInsertUpdate )
		setProperty( att.toLocal8Bit(), getBackUpRecord()->property( att.toLocal8Bit() ) );
	enabledRecordBackup=true;
	lstAttInsertUpdate.clear();
	emit hasValuesWithOutSave( false,this );

	DB.commit();
	return error;
}

TSqlError RecordInheritsBase::delete_()
{
	TSqlError error;

	//iniciamos transaccion
	if ( DB.driver()->hasFeature( QSqlDriver::Transactions ) )
		DB.transaction();
	else
		qDebug() << "RecordInheritsBase: Delete: " << DB.driverName() << " No soporta transacciones";

	TSqlGenerator sg(TABLENAME,&DB);

	//lstTables contiene las tablas desde el hijo hasta el padre mayor, borramos del hijo hasta al padre
	foreach ( QString table, lstTables )
	{
		//verificando que las llaves primarias tengan asignados valores
		foreach( QString pk, property( QString(table+"PKAttributesList").toLocal8Bit()).toStringList() )
		{
			QVariant value = property(pk.toLocal8Bit());

			if ( ! verifyValue( value ) )
			{
				error.setType( QSqlError::UnknownError );
				error.RecordMessage="Delete: El atributo "+
						pk+" que pertenece a la llave primaria de la tabla "+
						table+" no tiene asignado un valor";
				error.showMessages();
				return error;
			}
			sg.addWhereAttribute( pk, value );
		}

		LASTQUERY=sg.getDeleteQuery();
		QSqlQuery query(LASTQUERY,DB);

		error.RecordMessage = "Delete: Error al eliminar el registro";
		error.RecordQuery = LASTQUERY;
		error = query.lastError();

		if ( error.type() != QSqlError::NoError )
		{
			DB.rollback();
			return error;
		}
	}
	DB.commit();

	//para que al compilar no saque la advertencia de que se devuelve void cuando debe de ser TSqlError
	return TSqlError();
}

QStringList RecordInheritsBase::getAttributesList()
{
	QStringList atts;
	foreach ( QString table, lstTables )
		atts.append( property( QString(table+"AttributesList").toLocal8Bit() ).toStringList() );

	return atts;
}

QStringList RecordInheritsBase::getPKAttributesList()
{
	QStringList atts;
	foreach ( QString table, lstTables )
		atts.append( property( QString(table+"PKAttributesList").toLocal8Bit() ).toStringList() );

	return atts;
}

QStringList RecordInheritsBase::getPKAutoIncrementAttributesList()
{
	QStringList atts;
	foreach ( QString table, lstTables )
		atts.append( property( QString(table+"PKAutoIncrementAttribute").toLocal8Bit() ).toString() );

	return atts;
}

QStringList RecordInheritsBase::getDateTimeAttributesList()
{
	QStringList atts;
	foreach ( QString table, lstTables )
		atts.append( property( QString(table+"DateTimeAttributesList").toLocal8Bit() ).toString() );

	return atts;
}

