#ifndef TIPTASKPANEL_H
#define TIPTASKPANEL_H

#include <QtGui>
#include "twidgets.h"

class TipTaskPanel : public QWidget
{
Q_OBJECT
public:
    explicit TipTaskPanel(QWidget *parent = 0);
	void actualizarColores();
	void setSize(int h);

	void addMenu(QString text,QString menu,bool checkable=true);
	void buildMenu();
private:
	int height;
	QColor color1,color2;
	QWidget *Parent;
	QGraphicsScene *scene;
	QStateMachine machine;
	QGraphicsView *view;
	QVBoxLayout *layoutWidget;

	QSignalMapper *signalMapper;

	TPixmap *pixmap;

	struct menuconf
	{
		QString menu;
		QString text;
		bool checkable;
	};
	QList<menuconf*> lstMenuConf;

	struct buildedMenu
	{
		QString menu;
		TMenuWidget *widget;
	};
	QList<buildedMenu*> lstBuildedMenus;

	void abrirColores();

signals:
	void buttonClicked(QWidget*);

public slots:
	void mie(QWidget*);
};

#endif // TIPTASKPANEL_H
