#include "tlineedit.h"

#include <QKeyEvent>

TLineEdit::TLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
}

void TLineEdit::keyReleaseEvent ( QKeyEvent * event )
{
	if ( event->key() == Qt::Key_Down )
	{
		emit personalizatedKeyPressed(event->key());
	}
	else
		QLineEdit::keyReleaseEvent(event);
}
