#ifndef TLINEEDIT_H
#define TLINEEDIT_H

#include <QLineEdit>
#include "common_global.h"

class QKeyEvent;

class COMMONSHARED_EXPORT TLineEdit : public QLineEdit
{
    Q_OBJECT
public:
	TLineEdit(QWidget *parent = 0);
protected:
	void keyReleaseEvent ( QKeyEvent * event );
signals:
	void personalizatedKeyPressed(int);
};

#endif // TLINEEDIT_H
