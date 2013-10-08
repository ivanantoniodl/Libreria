#include "booleancolor.h"
#include "imgbutton.h"

BooleanColor::BooleanColor(QObject *parent) : QItemDelegate(parent)
{
}

void BooleanColor::paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const
{
    if (option.state & QStyle::State_Selected)
        painter->fillRect(option.rect, option.palette.highlight());

    bool valor = index.model()->data(index, Qt::DisplayRole).toBool();
    painter->save();

    if (valor)
        painter->drawPixmap(option.rect.x(),option.rect.y(),
                            24, 17,QPixmap(":/pics/permisoPermitido.png"));
    else
        painter->drawPixmap(option.rect.x(),option.rect.y(),
                            24, 17,QPixmap(":/pics/permisoNoPermitido.png"));
    painter->restore();
}

QSize BooleanColor::sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const
{
    return QSize(24,17);
}

//QWidget *BooleanColor::createEditor( QWidget *parent,
//                       const QStyleOptionViewItem &option,
//                       const QModelIndex &index) const
//{
//    imgButton *botonSwitch = new imgButton(parent);
//	//botonSwitch->installEventFilter( qobject_cast<BooleanColor*>(this) );
//	connect( botonSwitch,SIGNAL(toggled(bool)),this,SLOT(commitAndCloseEditor(bool)) );
//    return botonSwitch;
//}

//void BooleanColor::setEditorData( QWidget *editor,
//                    const QModelIndex &index) const
//{
//    bool valor = index.model()->data(index, Qt::DisplayRole).toBool();
//	qobject_cast<imgButton*>(editor)->setChecked(!valor);
//}

//void BooleanColor::setModelData( QWidget *editor,
//                   QAbstractItemModel *model,
//                   const QModelIndex &index ) const
//{
//	qDebug() << "grabando los datos en el modelo";
//	model->setData( index, qobject_cast<imgButton*>(editor)->isChecked());
//}

//void BooleanColor::updateEditorGeometry( QWidget *editor,
//                           const QStyleOptionViewItem &option,
//                           const QModelIndex &index ) const
//{
//    editor->setGeometry(option.rect);
//}

//void BooleanColor::commitAndCloseEditor(bool a)
//{
//	//qDebug() << "cambio a " << a;
//	imgButton *editor = qobject_cast<imgButton*>(sender());
//	emit commitData( editor );
//	emit closeEditor( editor );
//}
