#include "qrecordwidgetmapperdialog.h"
#include "tlistviewmodelrecord.h"
#include "tcomboboxmodelrecord.h"
#include "ttableviewmodelrecord.h"

//QRecordWidgetMapperDialog
//********************************************************************************************************

/*! Contruye un nuevo QRecordWidgetMapper con padre \a parent y asigna el modelo \a Model para su uso.

Del modelo se extraen los registros y se trabaja como que si se hubiera establecido una lista de registros.

\param Model Modelo a utilizar
\param parent Objecto QObject padre
*/
QRecordWidgetMapperDialog::QRecordWidgetMapperDialog(ModelBase *Model,
									   QWidget *parent) :
	QDialog(parent)
{
	signalMapper = new QSignalMapper(this);
	setModel(Model);
}

QRecordWidgetMapperDialog::QRecordWidgetMapperDialog(QWidget *parent):
	QDialog(parent)
{
	signalMapper = new QSignalMapper(this);
	model = NULL;
	pos=-1;
	actualRecord=NULL;
}

QRecordWidgetMapperDialog::~QRecordWidgetMapperDialog()
{
	qDeleteAll(lstConfMappers);
	lstConfMappers.clear();
}

void QRecordWidgetMapperDialog::setModel(ModelBase *Model)
{
	model=Model;
	modelToLstRecord( model );
	actualRecord=NULL;
	pos=-1;
	newrecord = false;
	connect(model,SIGNAL(hasRecordsWithOutSave(bool)),this,SIGNAL(hasRecordsWithOutSave(bool)));
	connect(model,SIGNAL(modelReset()),this,SLOT(model_modelReset()));
}

/*! Agrega una asignación entre un atributo y un valor.*/
void QRecordWidgetMapperDialog::addValueMapper(QString recordProperty,
								   QVariant value)
{
	//verificando si ya existe la asignación

	foreach ( confMapper *cm, lstConfMappers )
	{
		//verificando si el atributo ya se asigno
		if ( cm->recordProperties.contains( recordProperty ) )
		{
			cm->widget=NULL;
			cm->widgetProperty="";
			cm->value = value;
			return;
		}
	}

	confMapper *cm=new confMapper;
	cm->recordProperties.append(recordProperty);
	cm->widget=NULL;
	cm->widgetProperty="";
	cm->value=value;
	lstConfMappers.append(cm);
}

/*! Agrega una asignación entre un atributo y un widget.

\param property Nombre de la propiedad del registro a asignar (El nombre de la propiedad es el nombre exacto del atributo de la tabla).
\param widget Widget al que se asignará el valor de la propiedad.
\param widgetProperty El widget utilizará esta propiedad para escribir y leer el valor del atributo, si no se establece se utilizará la propiedad por defecto del widget.

\note
\arg Si el widget ya esta asignado a un atributo, o el atributo ya esta asignado a un widget, la vieja asignación será reemplazada por la nueva.
\arg Solo asignaciones uno a uno entre widgets y atributos están permitidas. No es posible asignar un solo atributo a varios widgets, o varios widgets a un solo atributo.
*/
void QRecordWidgetMapperDialog::addMapper(QString recordProperty,
								   QWidget *widget,
								   QString widgetProperty)
{
	//QComboBox no se puede usar ya que el mapper esta controlando constantemente los cambios y
	//si se actualiza el modelo en este hay problemas ya que los registros desaparecen y el mapper intenta asignar los
	//cambios, para eso se debe usar TComboBoxModelRecord que controlan este problema
	if ( widget->inherits("QComboBox") && ! widget->inherits("TComboBoxModelRecord"))
	{
		qDebug() << "En lugar de usar QComboBox se debe usar TComboBoxModelRecord";
		return;
	}
	if ( widget->inherits("QListView") )
	{
		qDebug() << "No se puede usar QListView en el asignador";
		return;
	}
	if ( widget->inherits("QTableView") )
	{
		qDebug() << "En se puede usar QTableView en el asignador";
		return;
	}
	if ( widget->inherits("QColumnView") )
	{
		qDebug() << "En se puede usar QColumnView en el asignador";
		return;
	}

	//verificando si ya existe la asignación
	foreach ( confMapper *cm, lstConfMappers )
	{
		//verificando si el widget ya esta asignado
		if ( cm->widget == widget )
		{
			cm->recordProperties.clear();
			cm->recordProperties.append(recordProperty);
			cm->widgetProperty = widgetProperty;
			return;
		}
		//verificando si el atributo ya se asigno
		if ( cm->recordProperties.contains( recordProperty ) )
		{
			cm->widget=widget;
			cm->widgetProperty=widgetProperty;
			return;
		}
	}
	
	if ( widget->inherits("TComboBoxModelRecord") )
	{
		connect(widget,SIGNAL(modelBeginResetModel()),this,SLOT(beginWidgetChangedByModel()));
		connect(widget,SIGNAL(modelEndResetModel()),this,SLOT(endWidgetChangedByModel()));
	}

	confMapper *cm=new confMapper;
	cm->recordProperties.append(recordProperty);
	cm->widget=widget;
	if ( ! widgetProperty.isEmpty() )
		cm->widgetProperty=widgetProperty;
	else
		cm->widgetProperty=getWidgetProperty(cm->widget);

	lstConfMappers.append(cm);
	connectDataChanged( cm->widget );
}

void QRecordWidgetMapperDialog::addMultipleMapper(QStringList lstAtts, QWidget *widget)
{
	if ( ! widget->inherits("TComboBoxModelRecord") ) //con multiple atributos solo esta soportado TComboBoxModelRecord
		return;

	if ( lstAtts.size() == 0 )
		return;

	foreach ( confMapper *cm, lstConfMappers )
	{
		//verificando si el widget ya esta asignado
		if ( cm->widget == widget )
		{
			cm->recordProperties.clear();
			cm->recordProperties = lstAtts;
			cm->widgetProperty = "currentPKValues";
			return;
		}
		//verificando si el atributo ya se asigno
		foreach ( QString att, lstAtts )
		{
			if ( cm->recordProperties.contains( att ) )
				return;
		}
	}

	if ( widget->inherits("TComboBoxModelRecord") )
	{
		connect(widget,SIGNAL(modelBeginResetModel()),this,SLOT(beginWidgetChangedByModel()));
		connect(widget,SIGNAL(modelEndResetModel),this,SLOT(endWidgetChangedByModel()));
	}

	confMapper *cm=new confMapper;
	cm->recordProperties = lstAtts;
	cm->widget=widget;
	cm->widgetProperty="currentPKValues";
	lstConfMappers.append(cm);
	connectDataChanged( cm->widget );
}

/*! Remueve una asignación entre un atributo y un widget o valor.

  \param property Propiedad a quitar.
*/
void QRecordWidgetMapperDialog::removeMapper(QString recordProperty)
{
	for ( int c=0; c<lstConfMappers.size(); c++ )
	{
		confMapper *con = lstConfMappers.at(c);
		if ( con->recordProperties.contains(recordProperty) )
		{
			cleanWidget( con->widget );
			lstConfMappers.removeAt(c);
			break;
		}
	}
}

/*! Remueve una asignación entre un atributo y un widget.

  \param widget Widget a quitar.
*/
void QRecordWidgetMapperDialog::removeMapper(QWidget *widget)
{
	for ( int c=0; c<lstConfMappers.size(); c++ )
	{
		confMapper *con = lstConfMappers.at(c);
		if ( con->widget == widget )
		{
			lstConfMappers.removeAt(c);
			cleanWidget( con->widget );
			break;
		}
	}
}

/*! Llena los widgets con los valores de los atributos del primer registro del modelo */
void QRecordWidgetMapperDialog::toFirst()
{
	if ( newrecord )
	{
		cancelNewRecord();
		newrecord = false;
	}
	pos=0;
	mapper();
}

/*! Llena los widgets con los valores de los atributos del último registro del modelo */
void QRecordWidgetMapperDialog::toLast()
{
	if ( newrecord )
	{
		cancelNewRecord();
		newrecord = false;
	}
	pos=lstRecords.size()-1;
	mapper();
}

/*! Llena los widgets con los valores de los atributos del siguiente registro del modelo */
void QRecordWidgetMapperDialog::toNext()
{
	if ( pos >= lstRecords.size()-1 )
		return;

	if ( newrecord )
	{
		cancelNewRecord();
		newrecord = false;
	}
	pos++;
	mapper();
}

/*! Llena los widgets con los valores de los atributos del registro anterior del modelo */
void QRecordWidgetMapperDialog::toPrevious()
{
	if ( pos <= 0 )
		return;

	if ( newrecord )
	{
		cancelNewRecord();
		newrecord = false;
	}
	pos--;
	mapper();
}

void QRecordWidgetMapperDialog::toRecord(int index)
{
	if ( newrecord )
	{
		cancelNewRecord();
		newrecord = false;
	}
	if ( index < 0 || index > lstRecords.size()-1 )
	{
		//fuera del rango, entonces se limpian los widgets
		foreach ( confMapper *cm , lstConfMappers )
			cleanWidget( cm->widget );
	}
	else
	{
		pos = index;
		mapper();
	}
}

void QRecordWidgetMapperDialog::toRecord(const QModelIndex & index)
{
	toRecord( index.row() );
}

/*! Llena los widgets con los valores de los atributos del registro posicionados en la fila \pos del modelo.

\param nuevo Si nuevo es true se limpian los widgets para que el usuario ingrese los valores y así crear un nuevo registro.
*/
void QRecordWidgetMapperDialog::mapper()
{
	disconnect(signalMapper,SIGNAL(mapped(QWidget*)),
			this,SLOT(dataChanged(QWidget*)));

	if ( lstRecords.size() == 0 && !newrecord )
		return;

	if ( pos >= lstRecords.size() )
		pos=lstRecords.size()-1;

	if ( ! newrecord )
		actualRecord = lstRecords.at(pos);

	emitNavigationSignals();

	foreach ( confMapper *cm , lstConfMappers )
	{
		if ( cm->widget == NULL )
			continue;

		if ( newrecord )
			cleanWidget( cm->widget );
		else
		{
			if ( cm->widgetProperty == "currentPKValues" )
			{
				QVariantList lstValues;

				foreach ( QString att, cm->recordProperties )
					lstValues.append( actualRecord->property( att.toLocal8Bit() ) );

				cm->widget->setProperty( cm->widgetProperty.toLocal8Bit() , lstValues );
			}
			else
				cm->widget->setProperty( cm->widgetProperty.toLocal8Bit() ,
										actualRecord->property(
											cm->recordProperties.at(0).toLocal8Bit()));
		}
	}

	connect(signalMapper,SIGNAL(mapped(QWidget*)),
			this,SLOT(dataChanged(QWidget*)));
}

void QRecordWidgetMapperDialog::emitNavigationSignals()
{
	if ( newrecord ) //si se esta insertando un nuevo registro;
	{
		emit navNext(false);
		emit navPrevious(false);
		emit navFirst(false);
		emit navLast(false);
	}
	else
	{
		if ( pos == 0 )
		{
			emit navPrevious(false);
			emit navFirst(false);
		}
		else
		{
			emit navPrevious(true);
			emit navFirst(true);
		}
		if ( pos == lstRecords.size()-1 )
		{
			emit navLast(false);
			emit navNext(false);
		}
		else
		{
			emit navLast(true);
			emit navNext(true);
		}
	}
}

/*! Devuelve la propiedad por defecto del widget \a widget.

  Las propiedades por defecto son:

	<TABLE>
		<TR>
			<TD><b>Widget ó heredado de</b></TD>
			<TD><b>Propiedad por defecto</b></TD>
		</TR>
		<TR>
			<TD>QLineEdit</TD>
			<TD>text</TD>
		</TR>
		<TR>
			<TD>QLabel</TD>
			<TD>text</TD>
		</TR>
		<TR>
			<TD>QTextEdit</TD>
			<TD>plaintext</TD>
		</TR>
		<TR>
			<TD>QPlainTextEdit</TD>
			<TD>plaintext</TD>
		</TR>
		<TR>
			<TD>QSpinBox</TD>
			<TD>value</TD>
		</TR>
		<TR>
			<TD>QDoubleSpinBox</TD>
			<TD>value</TD>
		</TR>
		<TR>
			<TD>QTimeEdit</TD>
			<TD>time</TD>
		</TR>
		<TR>
			<TD>QDateEdit</TD>
			<TD>date</TD>
		</TR>
		<TR>
			<TD>QDateTimeEdit</TD>
			<TD>dateTime</TD>
		</TR>
		<TR>
			<TD>QComboBox</TD>
			<TD>id*</TD>
		</TR>
	</TABLE>

	\param Widget que se desea saber su propiedad por defecto.
	\return Texto que representa el nombre de la propiedad por defecto.

	\note *Para las asignaciones con combobox el widget debe ser TComboBoxModelRecord o un heredado de este ya que se utiliza la propiedad \b id que no posee QComboBox
*/
QString QRecordWidgetMapperDialog::getWidgetProperty(QWidget *widget)
{
	if ( widget->inherits("QLineEdit") ||
		 widget->inherits("QLabel")  )
		return "text";

	if ( widget->inherits("QTextEdit") ||
		 widget->inherits("QPlainTextEdit"))
		return "plainText";

	if ( widget->inherits("QSpinBox") ||
		 widget->inherits("QDoubleSpinBox"))
		return "value";

	if ( widget->inherits("QTimeEdit") )
		return "time";

	if ( widget->inherits("QDateEdit") )
		return "date";

	if ( widget->inherits("QDateTimeEdit") )
		return "dateTime";

	if ( widget->inherits("TComboBoxModelRecord") )
		return "currentPKValues";

	if ( widget->inherits("QCheckBox") )
		return "checked";

	return "";
}

/*! Limpia un widget

  \param widget Widget a limpiar.
*/
void QRecordWidgetMapperDialog::cleanWidget(QWidget *widget)
{
	if ( widget->inherits("QLineEdit") ||
		 widget->inherits("QLabel")  )
		widget->setProperty("text","");

	if ( widget->inherits("QTextEdit") ||
		 widget->inherits("QPlainTextEdit"))
		widget->setProperty("plainText","");

	if ( widget->inherits("QSpinBox") ||
		 widget->inherits("QDoubleSpinBox"))
		widget->setProperty("value",0);

	if ( widget->inherits("QTimeEdit") )
		widget->setProperty("time",QTime(0,0,0));

	if ( widget->inherits("QDateEdit") )
		widget->setProperty("date",QDate(0,0,0));

	if ( widget->inherits("QDateTimeEdit") )
	{
		QDate d(0,0,0);
		QTime t(0,0,0);
		QDateTime dt(d,t);
		widget->setProperty("dateTime",dt);
	}

	if ( widget->inherits("TComboBoxModelRecord") )
		widget->setProperty("currentIndex",0);

	if ( widget->inherits("QCheckBox") )
		widget->setProperty("checked",false);
}

void QRecordWidgetMapperDialog::connectDataChanged(QWidget *widget)
{
	if ( widget->inherits("QLineEdit") )
	{
		QLineEdit *w = (QLineEdit*)widget;
		connect(w, SIGNAL(textEdited(QString)), signalMapper, SLOT(map()));
		signalMapper->setMapping(w,w);
	}
	else if ( widget->inherits("QTextEdit") )
	{
		QTextEdit *w = (QTextEdit*)widget;
		connect(w, SIGNAL(textChanged()), signalMapper, SLOT(map()));
		signalMapper->setMapping(w,w);
	}
	else if ( widget->inherits("QPlainTextEdit") )
	{
		QPlainTextEdit *w = (QPlainTextEdit*)widget;
		connect(w, SIGNAL(textChanged()), signalMapper, SLOT(map()));
		signalMapper->setMapping(w,w);
	}
	else if ( widget->inherits("QSpinBox") )
	{
		QSpinBox *w = (QSpinBox*)widget;
		connect(w, SIGNAL(valueChanged(int)), signalMapper, SLOT(map()));
		signalMapper->setMapping(w,w);
	}
	else if ( widget->inherits("QDoubleSpinBox") )
	{
		QDoubleSpinBox *w = (QDoubleSpinBox*)widget;
		connect(w, SIGNAL(valueChanged(double)), signalMapper, SLOT(map()));
		signalMapper->setMapping(w,w);
	}
	else if ( widget->inherits("QTimeEdit") )
	{
		QTimeEdit *w = (QTimeEdit*)widget;
		connect(w, SIGNAL(timeChanged(QTime)), signalMapper, SLOT(map()));
		signalMapper->setMapping(w,w);
	}
	else if ( widget->inherits("QDateEdit") )
	{
		QDateEdit *w = (QDateEdit*)widget;
		connect(w, SIGNAL(dateChanged(QDate)), signalMapper, SLOT(map()));
		signalMapper->setMapping(w,w);
	}
	else if ( widget->inherits("QDateTimeEdit") )
	{
		QDateTimeEdit *w = (QDateTimeEdit*)widget;
		connect(w, SIGNAL(dateTimeChanged(QDateTime)), signalMapper, SLOT(map()));
		signalMapper->setMapping(w,w);
	}
	else if ( widget->inherits("TComboBoxModelRecord") )
	{
		QLineEdit *w = (QLineEdit*)widget;
		connect(w, SIGNAL(currentIndexChanged(int)), signalMapper, SLOT(map()));
		signalMapper->setMapping(w,w);
	}
	else if ( widget->inherits("QCheckBox") )
	{
		QComboBox *w = (QComboBox*)widget;
		connect(w, SIGNAL(stateChanged(int)), signalMapper, SLOT(map()));
		signalMapper->setMapping(w,w);
	}
}

/*! Actualiza los atributos del registro con los valores de los widgets.
  \return Resultado de la acción.
*/
TSqlError QRecordWidgetMapperDialog::applyChanges()
{
	TSqlError error;
	error.RecordMessage = "QRecordWidgetMapperDialog: Update: Error al actualizar los atributos";
	error=actualRecord->update();

	if ( error.type() != QSqlError::NoError )
		return error;

	model->resetModel();
	emitNavigationSignals();

	return error;
}

/*! Inserta un nuevo registro con los valores de los widgets.
  \return Resultado de la acción.
*/
TSqlError QRecordWidgetMapperDialog::saveNewRecord()
{
	TSqlError error;
	error.RecordMessage = "QRecordWidgetMapperDialog: Insert: Error al insertar los atributos";
	error=actualRecord->insert();

	if ( error.type() != QSqlError::NoError )
		return error;

	model->addRecord( actualRecord );
	lstRecords.append( actualRecord );
	model->resetModel();

	pos = lstRecords.size()-1;
	emitNavigationSignals();
	
	newrecord=false;

	return error;
}

/*! Aplica en la base de datos las acciones del usuario.
  Si se esta modificando un registro llama a applyChanges(), si se esta insertando un nuevo registro se llama a saveNewRecord().
  \return Resultado de la acción.
*/
TSqlError QRecordWidgetMapperDialog::submit()
{
	TSqlError error;
	error.RecordMessage = "QRecordWidgetMapperDialog: Submit: Error, No se ha establecido un modelo o no contiene registros";
	error.setType(QSqlError::UnknownError);

	if ( model == NULL || actualRecord == NULL )
		return error;

	if ( newrecord )
	{
		//en el caso de insertar un registro, establecemos los valores de los widgets en el record que estan
		//en el mapper por si no se modifico, ejemplo un combobox que ya tenia valor y no se toco
		dataChanged(NULL); //si es nulo modifica todos los atributos que estan en la configuracion del mapper

		TSqlError error = saveNewRecord();
		return error;
	}
	else
		return applyChanges();
}

TSqlError QRecordWidgetMapperDialog::submitAll()
{
	TSqlError error;
	error.RecordMessage = "QRecordWidgetMapper: SubmitAll: Error, No se ha establecido un modelo o no contiene registros";
	error.setType(QSqlError::UnknownError);

	if ( model == NULL || actualRecord == NULL )
		return error;

	if ( newrecord )
	{
		//en el caso de insertar un registro, establecemos los valores de los widgets en el record que estan
		//en el mapper por si no se modifico, ejemplo un combobox que ya tenia valor y no se toco
		dataChanged(NULL); //si es nulo modifica todos los atributos que estan en la configuracion del mapper

		TSqlError error = saveNewRecord();
		return error;
	}
	else
		return model->submitAll();
}

/*! Limpia los widgets y se prepara para insertar un nuevo registro. */
void QRecordWidgetMapperDialog::newRecord()
{
	newrecord=true;
	actualRecord=model->getNewRecord();
	mapper();
}

void QRecordWidgetMapperDialog::cancelNewRecord()
{
	if ( !newrecord )
		return;

	newrecord=false;
	delete actualRecord; //este fue el que se obtuvo del modelo con getNewRecord

	mapper();
	emitNavigationSignals();
}

void QRecordWidgetMapperDialog::revert()
{
	actualRecord->revert();
	mapper();
}

void QRecordWidgetMapperDialog::revertAll()
{
	foreach ( RecordBase *record, lstRecords )
		record->revert();
	mapper();
}

void QRecordWidgetMapperDialog::cleanWidgets()
{
	foreach ( confMapper *cm , lstConfMappers )
		cleanWidget( cm->widget );
}

/*! Establece los registros del modelo \a m como la lista de registro a utilizar. */
void QRecordWidgetMapperDialog::modelToLstRecord(ModelBase* m)
{
	//no borramos los punteros ya que el modelo de donde venia los va a borrar, solo borramos el contenido de la lista
	lstRecords.clear();
	for ( int c=0; c<m->rowCount(); c++ )
		lstRecords.append( m->getRecord(c) );
}

void QRecordWidgetMapperDialog::dataChanged(QWidget *widget)
{
	if ( actualRecord == NULL )
		return;

	foreach ( confMapper *cm, lstConfMappers )
	{		
		if ( cm->widget == widget || widget == NULL )
		{
			if ( cm->widgetProperty == "currentPKValues" )
			{
				QVariantList lstValues = cm->widget->property( cm->widgetProperty.toLocal8Bit()).toList();
				for ( int c=0; c<cm->recordProperties.size(); c++ )
					actualRecord->setProperty( cm->recordProperties.at(c).toLocal8Bit(),
											  lstValues.at(c));
			}
			else
				actualRecord->setProperty( cm->recordProperties.at(0).toLocal8Bit(),
										  cm->widget->property( cm->widgetProperty.toLocal8Bit()));
		}
	}
}

void QRecordWidgetMapperDialog::beginWidgetChangedByModel()
{
	disconnect(signalMapper,SIGNAL(mapped(QWidget*)),
			this,SLOT(dataChanged(QWidget*)));
}

void QRecordWidgetMapperDialog::endWidgetChangedByModel()
{
	connect(signalMapper,SIGNAL(mapped(QWidget*)),
			this,SLOT(dataChanged(QWidget*)));
}

void QRecordWidgetMapperDialog::model_modelReset()
{
	modelToLstRecord( model );
}
