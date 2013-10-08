#include "twidgets.h"

//TPixmap
//**********************************************************************************

TPixmap::TPixmap(const QPixmap &pix) :
		QGraphicsObject(), p(pix)
{
}

void TPixmap::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	painter->drawPixmap(QPointF(), p);
}

QRectF TPixmap::boundingRect() const
{
	return QRectF( QPointF(0, 0), p.size());
}

//TMenuWidget
//********************************************************************************************

TMenuWidget::TMenuWidget(QWidget* parent):
	QFrame(parent)
{
	lyt = new QVBoxLayout(this);
	setLayout( lyt );
}

void TMenuWidget::lytAddButton(QWidget* button, int index)
{
	if ( index == -1 )
	{
		lstButtons.append(button);
		lyt->addWidget( button ,1 );
	}
	else
	{
		lstButtons.insert(index,button);
		lyt->insertWidget( index, button, 1 );
	}
}

QVBoxLayout *TMenuWidget::layout()
{
	return lyt;
}


QWidgetList TMenuWidget::getLstButtons() { return lstButtons; }

//TMenuButton
//********************************************************************************************

TMenuButton::TMenuButton(QWidget *parent):
	QPushButton(parent)
{}

void TMenuButton::setMenu(QString menu) { Menu=menu; }

void TMenuButton::setIText(QString text) { Itext=text; }

QString TMenuButton::menu() { return Menu; }

QString TMenuButton::itext() { return Itext; }

