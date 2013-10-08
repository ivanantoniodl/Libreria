#ifndef TCOMBOBOXMODELRECORD_H
#define TCOMBOBOXMODELRECORD_H

#include <QComboBox>
#include <QComboBox>
#include <QKeyEvent>
#include <QDebug>
#include <QFrame>
#include <QAbstractItemView>
#include <QModelIndex>
#include <QStringListModel>
#include <QCompleter>
#include <QListView>

#include "../qantmv_global.h"

#if defined(QANTDESIGNER)
    #include "../generatecode/files/modelbase.h"
#else
    #include "../om/modelbase.h"
#endif

/*!
\class TComboBoxModelRecord
\brief Clase que hereda de QComboBox y le agrega la capacidad de trabajar con los registros (Record) como elementos del mismo.

Esta clase le permite al QComboBox trabajar los elementos como registros (Record).
*/

class QRecordWidgetMapper;
class QRecordWidgetMapperDialog;

class QANTMVSHARED_EXPORT TComboBoxModelRecord : public QComboBox
{
friend class QRecordWidgetMapper;
friend class QRecordWidgetMapperDialog;
Q_OBJECT
Q_PROPERTY(QVariantList currentPKValues READ currentPKValues WRITE setCurrentPKValues )
private:
    int currentModelColumn;
    QVariantList currentSelectedRecord;
    void filtrar(int code);
    QStringList lst;
    QListView *lstview;
    QString escrito;
    QStringListModel *m;
    bool editable_;
    QList<int> lstFiltrados;

protected:
    QAbstractItemModel *originalModel;
    virtual void keyPressEvent ( QKeyEvent * e );
    bool eventFilter(QObject *obj, QEvent *event);

public:
    explicit TComboBoxModelRecord(QWidget *parent = 0);

    template <class T> T getSelectedRecord();

    QVariantList currentPKValues();
    void setCurrentPKValues(QVariantList);
    void setCurrentRecord(RecordBase*);

    void setModel (QAbstractItemModel * m );
    void setModelColumn(int visibleColumn);

    void setEditable(bool editable);

    QAbstractItemModel *model () const;

signals:
    void modelBeginResetModel();
    void modelEndResetModel();
private slots:
    void currentIndexChangedSlot(int);
    void model_endResetModelSignal();
    void popupView_keyEvent(QKeyEvent* e);
};

/*! Devuelve el elemento seleccionado en el ComboBox como registro (Record)
\return Registros seleccionado.
*/
template <class T> T TComboBoxModelRecord::getSelectedRecord()
{
    ModelBase* m=(ModelBase*)originalModel;
    return (T)m->getRecord( editable_ ? lstFiltrados.at(currentIndex()) : currentIndex() );
}

#endif // TCOMBOBOXMODELRECORD_H

