#ifndef BOOLEANCOLOR_H
#define BOOLEANCOLOR_H

#include <QAbstractItemDelegate>
#include <QObject>
#include <QtGui>
#include "configusers_global.h"

class CONFIGUSERSSHARED_EXPORT BooleanColor: public QItemDelegate
{
	Q_OBJECT
public:
    BooleanColor(QObject *parent=0);
    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const;
//    QWidget *createEditor( QWidget *parent,
//                           const QStyleOptionViewItem &option,
//                           const QModelIndex &index) const;
//    void setEditorData( QWidget *editor,
//                        const QModelIndex &index) const;
//    void setModelData( QWidget *editor,
//                       QAbstractItemModel *model,
//                       const QModelIndex &index ) const;
//    void updateEditorGeometry( QWidget *editor,
//                               const QStyleOptionViewItem &option,
//                               const QModelIndex &index ) const;
};

#endif // BOOLEANCOLOR_H
