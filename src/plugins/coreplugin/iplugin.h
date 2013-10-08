#ifndef IPLUGIN_H
#define IPLUGIN_H

#include <QWidget>
#include <QCloseEvent>
#include <QDebug>
#include <QString>
#include "core_global.h"

class CORESHARED_EXPORT closeEater : public QObject
{
Q_OBJECT
private:
    QWidget* newWidget;
protected:
    bool eventFilter(QObject *obj, QEvent *event);
public:
    closeEater(QObject *parent=0);
    void setNewWidget(QWidget *nwidget) { newWidget=nwidget; }
signals:
    void close();
    void close(QWidget*);
};

//*****************************************************************************************

class CORESHARED_EXPORT WidgetPluginMainWindow : public QObject
{
Q_OBJECT
private:
    WidgetPluginMainWindow();
    static WidgetPluginMainWindow *INSTANCE;
    void privateEmit(QWidget *widget,QString text,closeEater *eater);
public:
    static WidgetPluginMainWindow *instance();
    static void currentWidgetShowNewPage(QWidget *principalWidget,QWidget *newWidget, QString text);
signals:
    void showNewPage(QWidget *w, QString t, closeEater* eater);
};

//******************************************************************************************

class CORESHARED_EXPORT IPlugin
{
protected:

public:
    IPlugin();
    virtual ~IPlugin();
	virtual QString name() = 0;
	virtual QString description() = 0;
	virtual QStringList dependencies() = 0;
	virtual QString developer() { return "TipSA."; }
};

Q_DECLARE_INTERFACE(IPlugin,"IPlugin")

#endif // IPLUGIN_H
