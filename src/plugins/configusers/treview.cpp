#include "treview.h"

TreView::TreView(QWidget *parent) :
    QTreeView(parent)
{
}

void TreView::commitData ( QWidget * editor )
{
	imgButton *img = static_cast<imgButton*>(editor);
	//qDebug() << "se ejecuto commitData" << img->objectName() << img->isChecked();

	QTreeView::commitData( editor );
}

void TreView::closeEditor ( QWidget * editor, QAbstractItemDelegate::EndEditHint hint )
{
	imgButton *img = static_cast<imgButton*>(editor);
	//qDebug() << "se ejecuto closeEditor" << img->objectName() << img->isChecked();

	QTreeView::closeEditor( editor,hint );
}
