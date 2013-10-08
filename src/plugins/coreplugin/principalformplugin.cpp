#include "principalformplugin.h"

PrincipalFormPlugin::PrincipalFormPlugin( PrincipalFormPlugin::TypeForm t )
{
    TYPE=t;
}

PrincipalFormPlugin::~PrincipalFormPlugin()
{}

QWidget *PrincipalFormPlugin::widget() { return NULL; }

QDialog *PrincipalFormPlugin::dialog() { return NULL; }

QDialog *PrincipalFormPlugin::dialogFromWidget(QWidget* w)
{
    closeEater *ce = new closeEater;
    w->installEventFilter( ce );

    QDialog *d = new QDialog;
    d->setLayout( new QHBoxLayout );
    d->layout()->addWidget( w );

    QObject::connect( ce,SIGNAL(close()),d,SLOT(close()) );
    QObject::connect( d,SIGNAL(destroyed()),w,SLOT(deleteLater()) );
    QObject::connect( w,SIGNAL(destroyed()),ce,SLOT(deleteLater()) );
    return d;
}


