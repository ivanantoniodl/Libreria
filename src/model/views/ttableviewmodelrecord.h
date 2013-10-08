#ifndef TTABLEVIEWMODELRECORD_H
#define TTABLEVIEWMODELRECORD_H

#include <QTableView>
#include "../qantmv_global.h"

#if defined(QANTDESIGNER)
	#include "../generatecode/files/modelbase.h"
#else
	#include "../om/modelbase.h"
#endif

/*!
\class TTableViewModelRecord
\brief Clase que hereda de QTableView y le agrega la capacidad de trabajar con los registros (Record) como elementos del mismo.

Esta clase le permite al QtableView trabajar los elementos como registros (Record).
*/

class QANTMVSHARED_EXPORT TTableViewModelRecord : public QTableView
{
    Q_OBJECT
protected:
	void mouseReleaseEvent ( QMouseEvent * event );

public:
    explicit TTableViewModelRecord(QWidget *parent = 0);

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

/*! Devuelve los elementos seleccionados en la tabla como registros (Record)
\return Registros seleccionados.
*/
template<class T> QList<T> TTableViewModelRecord::getSelectedRecords()
{
	QList<T> lst;
	ModelBase *modelo=(ModelBase*)model();

	QList<int> lstFilas;
	foreach ( QModelIndex index, selectedIndexes() )
	{
		if ( lstFilas.indexOf(index.row()) != -1 )
			continue;

		lst.append( (T)modelo->getRecord( index.row()  ));
		lstFilas.append(index.row());
	}
	return lst;
}

/*! Devuelve los elementos seleccionados en la tabla como un modelo (ModelBase)
\return Modelo conteniendo los registros seleccionados.
*/
template<class T> T TTableViewModelRecord::getModelSelectedRecords()
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

#endif // TTABLEVIEWMODELRECORD_H
