#include "iplugin.h"

closeEater::closeEater(QObject *parent):
    QObject(parent)
{
    newWidget=NULL;
}

bool closeEater::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Close)
    {
        if ( ! newWidget )
            emit close();
        else
            emit close(newWidget);
        return true;
    }
    else
        // standard event processing
        return QObject::eventFilter(obj, event);
}

//******************************************************************************************

WidgetPluginMainWindow *WidgetPluginMainWindow::INSTANCE=NULL;

WidgetPluginMainWindow::WidgetPluginMainWindow():
    QObject(0)
{}

void WidgetPluginMainWindow::privateEmit(QWidget *widget,QString text, closeEater *eater)
{
    emit showNewPage( widget,text,eater );
}

void WidgetPluginMainWindow::currentWidgetShowNewPage(QWidget *principalWidget,QWidget *newWidget,QString text)
{
    closeEater *ce = new closeEater;
    ce->setNewWidget( newWidget );
    newWidget->installEventFilter( ce );

    WidgetPluginMainWindow *w = instance();
    w->privateEmit(newWidget,text,ce);

    QObject::connect( ce,SIGNAL(close(QWidget*)),principalWidget,SLOT(secundaryWidgetClosed(QWidget*)) );
    QObject::connect( newWidget,SIGNAL(destroyed()),ce,SLOT(deleteLater()) );
}

WidgetPluginMainWindow *WidgetPluginMainWindow::instance()
{
    if ( INSTANCE==NULL )
        INSTANCE=new WidgetPluginMainWindow;

    return INSTANCE;
}

//******************************************************************************************

IPlugin::IPlugin()
{
}

IPlugin::~IPlugin()
{}
