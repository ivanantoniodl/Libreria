#ifndef IMGBUTTON_H
#define IMGBUTTON_H

#include <QAbstractButton>
#include <QWidget>
#include "configusers_global.h"

class CONFIGUSERSSHARED_EXPORT imgButton : public QAbstractButton
{
Q_OBJECT
public:
    explicit imgButton(QWidget *parent = 0);
    QSize sizeHint() const;
protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:

};

#endif // IMGBUTTON_H
