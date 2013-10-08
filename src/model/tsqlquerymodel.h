#ifndef TSQLQUERYMODEL_H
#define TSQLQUERYMODEL_H

#include <QSqlQueryModel>
#include <QDebug>
#include "qantmv_global.h"

/*!
\class TSqlQueryModel
\brief Este modelo trabaja con una consulta SQL establecida.

	Sirve para cuando la consulta es muy compleja para generarla con TSqlGenerator.

\b Navegación

	Se le debe establecer la consulta sin limit y offset ya que este modelo lo controlará y permitira la navegación emitiendo las señales navNext(), navPrevious() y ejecutandose navToNext() y navToPrevious().

	Si el limite es 50 la consulta se realiza con \a limit + 1, en este caso con 51, con ellos se sabe si hay mas datos a mostrar. A la hora de mostrar los datos solo se muestran los 50.
*/

class QANTMVSHARED_EXPORT TSqlQueryModel : public QSqlQueryModel
{
	Q_OBJECT
private:
	//navegacion
	int limit;
	int offset;
	int actualQuerySize;
	bool primeraConsulta;

	QString lastQuery;
	QSqlDatabase lastDB;
public:
    explicit TSqlQueryModel(QObject *parent = 0);
	void setQuery ( const QString & query, const QSqlDatabase & db = QSqlDatabase() );
	int	rowCount ( const QModelIndex & parent = QModelIndex() ) const;

	//navegacion
	void setSelectQueryLimit(int);

signals:
	//navegacion

	/*!Se emite cuando se actualiza el contenido del modelo.
	\param[out] next Se puede navegar hacia los siguientes registros. */
	void navNext(bool);

	/*!Se emite cuando se actualiza el contenido del modelo.
	\param[out] prev Se puede navegar hacia los registros anteriores. */
	void navPrevious(bool);

public slots:
	//navegacion
	void navToNext();
	void navToPrevious();

};

/*! @} */

#endif // TSQLQUERYMODEL_H
