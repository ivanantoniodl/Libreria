#ifndef TWIDGETS_H
#define TWIDGETS_H

#include <QDebug>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QFocusEvent>
#include <QGraphicsObject>
#include <QPainter>
#include <QLineEdit>
#include <QTableWidget>
#include <QVBoxLayout>

class TPixmap : public QGraphicsObject
{
	Q_OBJECT
public:
	TPixmap(const  QPixmap &pix);
	void paint(QPainter *painter,  const QStyleOptionGraphicsItem *, QWidget *);
	QRectF boundingRect() const;

private:
	QPixmap p;
};

class TMenuWidget : public QFrame
{
Q_OBJECT
private:
	QVBoxLayout *lyt;
	QWidgetList lstButtons;
public:
	TMenuWidget(QWidget* parent=0);

	void lytAddButton(QWidget*, int index=-1);
	QVBoxLayout *layout();
	QWidgetList getLstButtons();

protected:
};


class TMenuButton : public QPushButton
{
Q_OBJECT
private:
	QString Menu;
	QString Itext;
public:
	TMenuButton(QWidget *parent=0);
	void setMenu(QString);
	void setIText(QString);

	QString menu();
	QString itext();
};

#endif // TWIDGETS_H
