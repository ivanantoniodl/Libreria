#include "tlistviewmodelrecord.h"

TListViewModelRecord::TListViewModelRecord(QWidget *parent) :
	QListView(parent)
{
}

/*! Establece el modelo a utilizar.
  Antes de establecer el modelo se hacen las conexiones necesarias entre el modelo y la lista para que este último pueda emitir las señales model_actualizado(), navNext(), navPrevious().
  Con esto se pueden realizar conexiones entre la lista y los botones de navegación en Qt Designer.
\param model Modelo a utilizar.
Reimplementado de QListView::setModel().
*/
void TListViewModelRecord::setModel ( QAbstractItemModel * m )
{
	connect(m,SIGNAL(modelReset()),
			this,SLOT(model_actualizado()) );
	connect(m,SIGNAL(navNext(bool)),
			this,SIGNAL(navNext(bool)));
	connect(m,SIGNAL(navPrevious(bool)),
			this,SIGNAL(navPrevious(bool)));
	connect(m,SIGNAL(hasRecordsWithOutSave(bool)),
			this,SIGNAL(hasRecordsWithOutSave(bool)));

	int cv = modelColumn();

	QListView::setModel(m);

	setModelColumn( cv );
}

/*! Evento cuando se suelta el botón del raton.
  Sirve para saber si se tienen seleccionados elementos en la lista y emite la señal selectedItem().
  \param event Evento.
Reimplementado de QListView::mouseReleaseEvent().
*/
void TListViewModelRecord::mouseReleaseEvent ( QMouseEvent * event )
{
	QListView::mouseReleaseEvent(event);

	if ( selectedIndexes().size() > 0 )
		emit selectedItem(true);
	else
		emit selectedItem(false);
}

/*! Se ejecuta cuado el modelo se actualiza.
  Emite que ningun elemento esta seleccionado con valor \a false con la señal selectedItem().
*/
void TListViewModelRecord::model_actualizado()
{
	emit selectedItem(false);
}

//!Actualiza el modelo para que consulte los siguientes registros y los muestra.
void TListViewModelRecord::navToNext()
{
	ModelBase *m=(ModelBase*)model();
	m->navToNext();
}

//!Actualiza el modelo para que consulte los registros anteriores y los muestra.
void TListViewModelRecord::navToPrevious()
{
	ModelBase *m=(ModelBase*)model();
	m->navToPrevious();
}
