#ifndef COMBO_H
#define COMBO_H

#include <QDialog>
#include <tcomboboxmodelrecord.h>
#include <QKeyEvent>
#include "common_global.h"
#include <QAbstractItemView>


class COMMONSHARED_EXPORT combo : public TComboBoxModelRecord
{
    Q_OBJECT
public:
    explicit combo(QWidget *parent = 0);

    
signals:
    void keyReturnPressed();
    void keyPressEvent(QKeyEvent *event);
    
public slots:
    void comboboxKeyPressed(QKeyEvent *event);
    
};

#endif // COMBO_H
