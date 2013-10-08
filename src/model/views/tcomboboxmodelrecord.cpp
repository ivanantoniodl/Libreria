#include "tcomboboxmodelrecord.h"

TComboBoxModelRecord::TComboBoxModelRecord(QWidget *parent) :
    QComboBox(parent)
{
    currentModelColumn=0;
    editable_=false;
    connect( this,SIGNAL(currentIndexChanged(int)),SLOT(currentIndexChangedSlot(int)) );
}

///*! Devuelve el valor de la llave primaria del elemento seleccionado en el ComboBox
//\return Valor de la llave primaria.
//*/
QVariantList TComboBoxModelRecord::currentPKValues()
{
    if ( count() == 0 )
        return QVariantList();

    ModelBase* m=(ModelBase*)originalModel;
    QVariantList values;

    if ( currentIndex() < 0 )
        return QVariantList();

    if ( currentIndex() == 0 && editable_ )
        return QVariantList();

    RecordBase *record = m->getRecord( editable_ ? lstFiltrados.at(currentIndex()) : currentIndex() );

    foreach ( QString pk,
             record->property(QString(m->getTableName()+"PKAttributesList").toLocal8Bit()).toStringList() )
        values.append( record->property( pk.toLocal8Bit() ) );

    return values;
}

///*! Selecciona el elemento en el ComboBox cuyo registro (Record) tenga la llave primaria \a id
//\param id Valor de la llave primaria a seleccionar.
//*/
void TComboBoxModelRecord::setCurrentPKValues(QVariantList lst)
{
    if ( count() == 0 )
        return;

    ModelBase* m=(ModelBase*)model();
    if ( m->getRecord(0)->property(QString(m->getTableName()+"PKAttributesList").toLocal8Bit()).toStringList().size()!=
            lst.size())
        return;

    for ( int f=0; f<m->modelSize(); f++ )
    {
        RecordBase *record=m->getRecord(f);

        bool error=false;
        QStringList lstpk=record->property(QString(m->getTableName()+"PKAttributesList").toLocal8Bit()).toStringList();
        for ( int c=0; c<lstpk.size(); c++)
        {
            QString pk=lstpk.at(c);
            if ( record->property(pk.toLocal8Bit()) != lst.at(c))
            {
                error=true;
                break;
            }
        }
        if ( error )
            continue;

        setCurrentIndex(f);
        break;
    }
}

void TComboBoxModelRecord::setCurrentRecord(RecordBase* record)
{
    if ( count() == 0 )
        return;

    ModelBase* m=(ModelBase*)model();
    for ( int f=0; f<m->modelSize(); f++ )
    {
        RecordBase *r=m->getRecord(f);
        if ( r->comparePK( record ) )
        {
            setCurrentIndex(f);
            break;
        }
    }
}

void TComboBoxModelRecord::setModel ( QAbstractItemModel * m )
{
    if ( editable_ )
    {
        lst.clear();
        for ( int c=0; c<m->rowCount(); c++ )
        {
            lst.append( m->sibling(c,0,QModelIndex()).data().toString() );
            lstFiltrados.append( c );
        }
    }

    connect(m,SIGNAL(beginResetModelSignal()),this,SIGNAL(modelBeginResetModel()));
    connect(m,SIGNAL(endResetModelSignal()),this,SIGNAL(modelEndResetModel()));

    connect(m,SIGNAL(endResetModelSignal()),this,SLOT(model_endResetModelSignal()));

    originalModel=m;

    //emitimos la señal ya que al establecer el modelo en el QComboBox este emitira la señal de que cambio
    emit modelBeginResetModel();
    QComboBox::setModel(m);
    emit modelEndResetModel();

    if ( editable_ )
        setCurrentIndex(-1);
    else
        setCurrentIndex( 0 );
}

void TComboBoxModelRecord::setModelColumn(int visibleColumn)
{
    if ( editable_ )
    {
        lst.clear();
        for ( int c=0; c<model()->rowCount(); c++ )
            lst.append( model()->sibling(c,visibleColumn,QModelIndex()).data().toString() );
    }

    currentModelColumn=visibleColumn;
    QComboBox::setModelColumn(visibleColumn);
}

void TComboBoxModelRecord::setEditable ( bool editable )
{
    editable_=editable;
    QComboBox::setEditable(editable);
    setCompleter(0);
    setInsertPolicy( QComboBox::NoInsert );
    m=NULL;
    lstview = new QListView;
    lstview->installEventFilter( this );
    setView( lstview );
}

void TComboBoxModelRecord::currentIndexChangedSlot(int index)
{
    Q_UNUSED(index);
    if ( currentPKValues().size() == 0 )
        return;

    currentSelectedRecord = currentPKValues();
}

void TComboBoxModelRecord::model_endResetModelSignal()
{
    emit modelBeginResetModel();

    QComboBox::setModelColumn(currentModelColumn);

    if ( ! currentSelectedRecord.isEmpty() )
        setCurrentPKValues( currentSelectedRecord );
    else
        setCurrentIndex(0);

    emit modelEndResetModel();
}

void TComboBoxModelRecord::filtrar(int code)
{
    QChar c( code );
    if ( c.isLetterOrNumber() || c.isSymbol() || code == Qt::Key_Backspace )
    {
        QStringList lstMie;
        lstFiltrados.clear();

        if ( m )
            delete m;

        m=new QStringListModel;

        for ( int c=0;c<lst.size(); c++ )
        {
            QString item=lst.at( c );
            if ( item.left( escrito.size() ).compare( escrito, Qt::CaseInsensitive ) == 0 )
            {
                lstMie.append( item );
                lstFiltrados.append( c );
            }
        }
        m->setStringList( lstMie );

        QComboBox::setModel( m );
        QComboBox::setModelColumn(0);
        setCurrentIndex(-1);
        setCompleter(0);
        setEditText(escrito);
        showPopup();
    }
}

QAbstractItemModel *TComboBoxModelRecord::model () const
{
    return originalModel;
}

void TComboBoxModelRecord::popupView_keyEvent( QKeyEvent* e)
{
    QChar c( e->key() );
    if ( c.isLetterOrNumber() ||
         c.isSymbol() ||
         c.isSpace() )
    {
        escrito+=e->text();
        filtrar( e->key() );
    }
    else if ( e->key() == Qt::Key_Backspace )
    {
        escrito = escrito.left( escrito.size()-1 );
        filtrar( e->key() );
    }
}

void TComboBoxModelRecord::keyPressEvent ( QKeyEvent * e )
{
    if ( e->key() == Qt::Key_Return || e->key() == Qt::Key_Escape )
        hidePopup();
    else
    {
        QComboBox::keyPressEvent(e);
        escrito=currentText();
        filtrar( e->key() );
    }
}

bool TComboBoxModelRecord::eventFilter(QObject *obj, QEvent *event)
{
    if ( event->type() == QEvent::KeyPress )
    {
        QKeyEvent *e=dynamic_cast<QKeyEvent*>(event);
        popupView_keyEvent( e );
    }
    else
        return QObject::eventFilter( obj,event );
}
