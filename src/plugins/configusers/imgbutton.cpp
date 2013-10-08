#include "imgbutton.h"
#include <QPainter>
#include <QPaintEvent>

imgButton::imgButton(QWidget *parent) :
    QAbstractButton(parent)
{
	setCheckable(true);
}

QSize imgButton::sizeHint() const
{
    return QSize(24,17);
}

void imgButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    if (isChecked())
        painter.drawPixmap(0,0,24,17,QPixmap(":/pics/permisoPermitidoBoton.png"));
    else
        painter.drawPixmap(0,0,24,17,QPixmap(":/pics/permisoNoPermitidoBoton.png"));
}
