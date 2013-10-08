#ifndef TSQLERROR_H
#define TSQLERROR_H

#include <QSqlError>
#include <QString>
#include <QWidget>
#include <QMessageBox>
#include <QDebug>
#include "../qantmv_global.h"

class QANTMVSHARED_EXPORT TSqlError : public QSqlError
{
friend class RecordSimpleBase;
friend class RecordInheritsBase;
friend class ModelBase;
friend class QRecordWidgetMapper;
friend class QRecordWidgetMapperDialog;
private:
	QString Error; //!< Error para mostrar con qDebug
	QString Message; //!< Mensaje a mostrar al usuario
	QString RecordMessage; //!< Mensaje de Record
	QString RecordQuery;
	QString ModelMessage; //!< Mensaje de Record
	QString ModelQuery;
	QString File; //!< Archivo donde esta la consulta realizada
	int NumberInFile; //!< Numero de consulta, sirve para identificar un error entre todas las consultas de un archivo
	QWidget *WIDGET;
	bool ShowMessages;

	void setValues(const QSqlError&);
	void showMessages();

public:
	TSqlError();
	TSqlError(const TSqlError&);
	TSqlError(const QSqlError&);

	bool isError();

	void setError(QString error) { Error=error; }
	void setMessage(QString msg) { Message=msg; }
	void setSourceFile(QString file) { File=file; }
	void setRowNumber(int number) { NumberInFile=number; }

	void setWidget(QWidget *widget) { WIDGET=widget; }

	void clear();

	TSqlError& operator=(const TSqlError&);
	TSqlError& operator=(const QSqlError&);
};

#endif // TSQLERROR_H
