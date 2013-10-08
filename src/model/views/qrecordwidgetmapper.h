#ifndef QRECORDWIDGETMAPPER_H
#define QRECORDWIDGETMAPPER_H

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

/*!
\class QRecordWidgetMapper
\brief Esta clase provee un mecanismo de asignación entre los atributos de los registros y los widgets.

	La asignación consiste en tomar el valor de un registro y mostrarlo en un widget para su modificación. Los datos se toman de las propiedades de los objetos heredados de Record y se escriben en el widget utilizando una propiedad especificada o uno por defecto.

	Supongamos que tenemos la tabla Persona con los atributos idPersona, Nombre, Direccion.

	<TABLE>
		<TR>
			<TD>\b idPersona</TD>
			<TD>\b Nombre</TD>
			<TD>\b Direccion</TD>
		</TR>
		<TR>
			<TD>1</TD>
			<TD>Pedro</TD>
			<TD>4 av 8-31 Z8</TD>
		</TR>
		<TR>
			<TD>2</TD>
			<TD>Juan</TD>
			<TD>6 calle 3-52 Z10</TD>
		</TR>
	</TABLE>

	El siguiente código asigna los atributos a los widgets:

	\code
	QRecordWidgetMapper *rwm=new QRecordWidgetMapper(this);
	rwm->setModel(model);
	rwm->addMapper("idPersona",label);
	rwm->addMapper("Nombre",lineEditNombre);
	rwm->addMapper("Direccion",lineEditDireccion);
	rwm->toFirst();
	\endcode

	Despues de toFirst() label mostrará <b>1</b>, lineEditNombre mostrará <b>Pedro</b> y lineEditDireccion mostrará <b>4 av 8-31 Z8</b>

\note Esta clase esta inspirada en QDataWidgetMapper, la diferencia con esta última es que esta asigna una columna de un modelo con un widget, a diferencia de QRecordWidgetMapper que asigna el atributo de un registro (objeto heredero de Record) a un widget.

\note Con QDataWidgetMapper al editarse un widget se actualiza el modelo, si lo utiliza con modelos herederos de ModelBase no podrá (por el momento) actualizar los datos ya que estos modelos no pueden actualizar los valores de los registros.
*/

class QANTMVSHARED_EXPORT QRecordWidgetMapper : public QWidget
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
	QRecordWidgetMapper(ModelBase *Model,
					   QWidget *parent = 0);
	QRecordWidgetMapper(QWidget *parent = 0);
	~QRecordWidgetMapper();

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

#endif // QRECORDWIDGETMAPPER_H
