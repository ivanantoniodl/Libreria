#ifndef TLISTVIEWMODELRECORD_H
#define TLISTVIEWMODELRECORD_H

#include <QListView>
#include "../qantmv_global.h"

#if defined(QANTDESIGNER)
	#include "../generatecode/files/modelbase.h"
#else
	#include "../om/modelbase.h"
#endif

/*!
\class TListViewModelRecord
\brief Clase que hereda de QListView y le agrega la capacidad de trabajar con los registros (Record) como elementos del mismo.

Esta clase le permite al QListView trabajar los elementos como registros (Record).
*/

class QANTMVSHARED_EXPORT TListViewModelRecord : public QListView
{
	Q_OBJECT
protected:
	void mouseReleaseEvent ( QMouseEvent * event );

public:
	explicit TListViewModelRecord(QWidget *parent = 0);

	template <class T> QList<T> getSelectedRecords();
	template <class T> T getModelSelectedRecords();

	void setModel ( QAbstractItemModel * model ) ;

private slots:
	void model_actualizado();

signals:
	void selectedItem(bool);

	void navNext(bool);
	void navPrevious(bool);
	void hasRecordsWithOutSave(bool);

public slots:
	void navToNext();
	void navToPrevious();

};

/*! Devuelve los elementos seleccionados en la lista como registros (Record)
\return Registros seleccionados.
*/
template <class T> QList<T> TListViewModelRecord::getSelectedRecords()
{
	QList<T> lst;
	ModelBase *modelo=dynamic_cast<ModelBase*>(model());

	QList<int> lstFilas;
	foreach ( QModelIndex index, selectedIndexes() )
	{
		if ( lstFilas.indexOf(index.row()) != -1 )
			continue;

		lst.append( (T)modelo->getRecord( index.row() ) );
		lstFilas.append(index.row());
	}

	return lst;
}

/*! Devuelve los elementos seleccionados en la tabla como un modelo (ModelBase)
\return Modelo conteniendo los registros seleccionados.
*/
template <class T> T TListViewModelRecord::getModelSelectedRecords()
{
	T modelo = (T)model();

	QList<int> lst;
	foreach ( QModelIndex index, selectedIndexes() )
	{
		if ( lst.indexOf(index.row()) != -1 )
			continue;

		lst.append( index.row() );
	}

	return (T)modelo->getModelRecords(lst);
}

#endif // TLISTVIEWMODELRECORD_H
