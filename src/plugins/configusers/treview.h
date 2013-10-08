#ifndef TREVIEW_H
#define TREVIEW_H

#include <QTreeView>
#include <QDebug>
#include "imgbutton.h"
#include "configusers_global.h"

class CONFIGUSERSSHARED_EXPORT TreView : public QTreeView
{
    Q_OBJECT
public:
    explicit TreView(QWidget *parent = 0);

signals:

protected slots:
	void commitData ( QWidget * editor );
	void closeEditor ( QWidget * editor, QAbstractItemDelegate::EndEditHint hint );
};

#endif // TREVIEW_H
