#include "tsqlerror.h"
#include <qdebug.h>

TSqlError::TSqlError() :
	QSqlError()
{
	ShowMessages=true;
	NumberInFile=0;
	WIDGET=NULL;
}

TSqlError::TSqlError(const TSqlError& other):
	QSqlError(other)
{
	ShowMessages=true;
	NumberInFile=0;
	WIDGET=NULL;
	setValues(other);
}

TSqlError::TSqlError(const QSqlError& other):
	QSqlError(other)
{
	ShowMessages=true;
	NumberInFile=0;
	WIDGET=NULL;
	setValues(other);
}

bool TSqlError::isError()
{
	if ( type() != QSqlError::NoError )
		return true;
	else
		return false;
}

void TSqlError::setValues(const QSqlError &other)
{
	setDatabaseText( other.databaseText() );
	setDriverText( other.driverText() );
	setType( other.type() );
	setNumber( other.number() );
}

void TSqlError::clear()
{
	Error.clear();
	Message.clear();
	RecordMessage.clear();
	RecordQuery.clear();
	ModelMessage.clear();
	ModelQuery.clear();
	File.clear();
	NumberInFile=0;
	WIDGET=NULL;
}

TSqlError& TSqlError::operator=(const TSqlError& other)
{
	setValues(other);

	if ( type() != QSqlError::NoError )
		showMessages();

	return *this;
}

TSqlError& TSqlError::operator=(const QSqlError& other)
{
	setValues(other);

	//Si other es QSqlError es porque viene de una funcion sql de Qt

	if ( type() != QSqlError::NoError )
		showMessages();

	return *this;
}

void TSqlError::showMessages()
{
	qDebug() << "SQL Error ----------------------------------------------------------------------------------\n";
	if ( ! File.isEmpty() )
		qDebug() << "File: "<<File;
	if ( NumberInFile>0 )
		qDebug() << "Number: "<<QString::number(NumberInFile)<<"\n";
	if ( ! Error.isEmpty() )
		qDebug() << Error << "\n";

	if ( !Message.isEmpty() && WIDGET != NULL )
		QMessageBox::critical(WIDGET,"Error",Message);

#if defined(QANTDEBUG)

	qDebug() << "Sql Number Error: "<<QString::number(number());
	qDebug() << "Sql Error: "<<text()<<"\n";

#endif

	if ( ! RecordMessage.isEmpty() )
		qDebug() << "Record Message: "<<RecordMessage;

	if ( ! ModelMessage.isEmpty() )
		qDebug() << "Model Message: "<<ModelMessage;

#if defined(QANTDEBUG)
	if ( ! RecordQuery.isEmpty() )
		qDebug() << "Record Query: "<<RecordQuery<<"\n";

	if ( ! ModelQuery.isEmpty() )
		qDebug() << "Model Query: "<<ModelQuery<<"\n";
#endif
}
