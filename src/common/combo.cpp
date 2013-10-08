#include "combo.h"

combo::combo(QWidget *parent) :
    TComboBoxModelRecord(parent)
{
    view()->installEventFilter(this);
    connect(this,SIGNAL(keyPressEvent(QKeyEvent*)),this,SLOT(comboboxKeyPressed(QKeyEvent*)));
}

void combo::comboboxKeyPressed(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Return:
        emit keyReturnPressed();
        break;
    }

    TComboBoxModelRecord::keyPressEvent(event);

}

