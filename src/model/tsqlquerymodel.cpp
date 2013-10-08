#include "tsqlquerymodel.h"

/*! Contruye el modelo con \a parent como padre.
  Establece el limite por defecto a 50.
  \param parent Padre del widget.
*/
TSqlQueryModel::TSqlQueryModel(QObject *parent) :
    QSqlQueryModel(parent)
{
	limit=50;
	offset=0;
	primeraConsulta=true;
}

/*! Establece la consulta.
  Esta consulta no debe tener el limit y el offset.
  \param query Consulta a establecer.
  \param db Conexión a la base de datos.
Reimplementado de QSqlQueryModel::setQuery().
*/
void TSqlQueryModel::setQuery ( const QString & query, const QSqlDatabase & db )
{
	if ( primeraConsulta )
	{
		offset=0;
		primeraConsulta=false;
	}

	QString nq = query;
	lastQuery=nq;
	lastDB=db;

	nq+=" LIMIT "+QString::number(limit+1);
	if ( offset > 0 )
		nq+=" OFFSET "+QString::number(offset);

	QSqlQueryModel::setQuery(nq,db);

	//navegacion
	emit navPrevious( ! (offset == 0) );
	emit navNext( QSqlQueryModel::rowCount() > limit );

	reset();
}

/*! Devuelve la cantidad de filas del modelo.
  Si las filas de la consulta es mayor al limite (solo puede ser mayor por uno) se muestra solo el limite, de lo contrario se muestran todos.
  \param parent Indice padre, al ser modelo de tabla no es necesario.
  \return Número de filas del modelo.
*/
int	TSqlQueryModel::rowCount ( const QModelIndex & parent ) const
{
	//no mostramos la ultima fila que es para mostrarse en la siguiente consulta
	int fi=QSqlQueryModel::rowCount(parent);
	if ( fi == limit+1 )
		return fi-1;
	else
		return fi;
}

/*! Establece el limite de la consulta.
  \param l Limite de la consulta.
*/
void TSqlQueryModel::setSelectQueryLimit(int l)
{
	if ( l < 1 )
		return;
	limit=l;
}

//navegacion

//!Aumenta offset y realiza la consulta para que se obtengan las siguientes filas de la base de datos.
void TSqlQueryModel::navToNext()
{
	offset+=limit;
	setQuery(lastQuery,lastDB);
}

//!Disminuye offset y realiza la consulta para que se obtengan las filas anteriores de la base de datos.
void TSqlQueryModel::navToPrevious()
{
	offset-=limit;
	setQuery(lastQuery,lastDB);
}

