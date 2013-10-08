#ifndef QRECORDWIDGETMAPPERDIALOG_H
#define QRECORDWIDGETMAPPERDIALOG_H

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QPlainTextEdit>
#include <QTextEdit>
#include <QDateTimeEdit>
#include <QComboBox>
#include "../qantmv_global.h"

#if defined(QANTDESIGNER)
	#include "../generatecode/files/modelbase.h"
#else
	#include "../om/modelbase.h"
#endif

//ya que Qt no soporta que una clase tenga dos padres que hereden de QObject y que usen Q_OBJECT
//repetimos el codigo para QRecordWidgetMapperDialog

class QANTMVSHARED_EXPORT QRecordWidgetMapperDialog : public QDialog
{
Q_OBJECT
private:
	ModelBase *model; //fuentes de datos
	QList<RecordBase*> lstRecords; //fuentes de datos
	RecordBase *actualRecord;
	int pos; //posicion actual de la lista de lstRecords
	bool newrecord;
	QSignalMapper *signalMapper;
	
	/*! Representa una asignación entre un widget y un atributo o entre un atributo y un valor */
	struct confMapper
	{
		QStringList recordProperties; //!<Propiedad del registro
		QWidget *widget; //!<Widget a establecer el valor
		QString widgetProperty; //!<Propiedad del widget a utilizar para establecer el valor
		QVariant value; //!<Valor a establecer en el registro
	};

	QList<confMapper*> lstConfMappers;

	void mapper();
	QString getWidgetProperty(QWidget*);
	void cleanWidget(QWidget*);
	void connectDataChanged(QWidget*);

	TSqlError applyChanges();
	TSqlError saveNewRecord();

	void modelToLstRecord(ModelBase*);
public:
	QRecordWidgetMapperDialog(ModelBase *Model,
					   QWidget *parent = 0);
	QRecordWidgetMapperDialog(QWidget *parent = 0);
	~QRecordWidgetMapperDialog();

	void setModel(ModelBase*);

	void addValueMapper(QString recordProperty,QVariant value);
	void addMapper(QString recordProperty,QWidget *widget,QString widgetProperty=QString());
	void addMultipleMapper(QStringList lstAtts, QWidget *widget);
	void removeMapper(QString property);
	void removeMapper(QWidget *widget);

	void emitNavigationSignals();

signals:
	/*!Se emite cada vez que se asigna los valores de los atributos a los widgets. Indica si se puede navegar hacia el siguiente registro.

	  \param[out] st Se puede navegar hacia adelante. */
	void navNext(bool st);
	/*!Se emite cada vez que se asigna los valores de los atributos a los widgets. Indica si se puede navegar hacia el registro anterior.

	  \param[out] st Se puede navegar hacia atras. */
	void navPrevious(bool st);
	/*!Se emite cada vez que se asigna los valores de los atributos a los widgets. Indica si se puede navegar hacia el primer registro.

	  \param[out] st Se puede navegar hacia el primer registro. */
	void navFirst(bool st);
	/*!Se emite cada vez que se asigna los valores de los atributos a los widgets. Indica si se puede navegar hacia el último registro.

	  \param[out] st Se puede navegar hacia el último registro. */
	void navLast(bool st);

	void hasRecordsWithOutSave(bool);

private slots:
	void beginWidgetChangedByModel();
	void endWidgetChangedByModel();
	void model_modelReset();
	void dataChanged(QWidget*);

public slots:
	void toFirst();
	void toLast();
	void toNext();
	void toPrevious();
	void toRecord(int index);
	void toRecord(const QModelIndex & index);
	void newRecord();
	void cancelNewRecord();
	void revert();
	void revertAll();
	void cleanWidgets();

	TSqlError submit();
	TSqlError submitAll();
};

#endif // QRECORDWIDGETMAPPERDIALOG_H
