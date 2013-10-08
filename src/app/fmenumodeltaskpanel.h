#ifndef FMENUMODEL_H
#define FMENUMODEL_H

#include <QtGui>
#include "twidgets.h"

//MenuOptions
//*****************************************************************************

struct menuconf
{
	QString menu;
	QString text;
	bool checkable;
	QString icon;
	QString description;
};

class MenuOptions
{
private:
	static QList<menuconf*> lstMenuConf;
public:
	static void addMenu(QString text,
						QString menu,
						QString iconpath,
						QString description,
						bool checkable=true);
	static QList<menuconf*> getLstMenuConf() { return lstMenuConf; }
	static QList<menuconf*> getLstMenuConf(QString group);
};

//TipTaskPanel
//*****************************************************************************

class TipTaskPanel : public QWidget
{
Q_OBJECT
public:
	explicit TipTaskPanel(QWidget *parent = 0);
	void actualizarColores();
	void setSize(int h);

	void buildMenu();
private:
	int height;
	QString lastGroup;
	QColor color1,color2;
	QWidget *Parent;
	QGraphicsScene *scene;
	QStateMachine machine;
	QGraphicsView *view;
	QVBoxLayout *layoutWidget;

	QSignalMapper *signalMapper;

	TPixmap *pixmap;

	struct buildedMenu
	{
		QString menu;
		TMenuWidget *widget;
	};
	QList<buildedMenu*> lstBuildedMenus;

	void abrirColores();

signals:

	void buttonClicked(QWidget*);
	void buttonClickedPath(QString,QString);

private slots:
	void privateButtonClicked_widget(QWidget*);
public slots:
	void setSelectedMenu(QString,QString);
};

//OptionModel
//****************************************************************************
class OptionModel : public QAbstractTableModel
{
Q_OBJECT
private:
	QString group;
public:
	OptionModel(QObject* parent=0);

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex & parent = QModelIndex()) const;

	void showGroup(QString);
};

//FMenuModel
//*****************************************************************************

namespace Ui {
	class FMenuModel;
}

class FMenuModel : public QWidget
{
	Q_OBJECT
private:
	OptionModel *model;
	QString group;

public:
	FMenuModel(QWidget *parent = 0);
	~FMenuModel();

	void showGroup(QString);

protected:
	void changeEvent(QEvent *e);

private:
	Ui::FMenuModel *m_ui;
	QWidget *Parent;

private slots:
	void privateModelClicked_widget(const QModelIndex);

signals:
	void itemClickedPath(QString,QString);

};

#endif
