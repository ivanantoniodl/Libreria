#include "faboutplugins.h"
#include "ui_faboutplugins.h"

#include "mainwindow.h"
#include "../plugins/coreplugin/iplugin.h"

FAboutPlugins::FAboutPlugins(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FAboutPlugins)
{
    ui->setupUi(this);
	ui->ledDesarrollador->setReadOnly(true);

	foreach ( IPlugin *ip, MainWindow::instance()->getLstConfigPagePlugins() )
		lstPlugins.append(ip);

	foreach ( IPlugin *ip, MainWindow::instance()->getLstPrincipalFormPlugins() )
		lstPlugins.append(ip);

	lstPlugins.append( MainWindow::instance()->getLstIplugins() );

	QStringList lst;
	foreach ( IPlugin *ip , lstPlugins )
		lst.append( ip->name() );

	model = new QStringListModel(lst,this);
	ui->lstPlugins->setModel(model);
}

FAboutPlugins::~FAboutPlugins()
{
    delete ui;
}

void FAboutPlugins::on_lstPlugins_clicked(const QModelIndex &index)
{
	IPlugin *ip = lstPlugins.at(index.row());

	ui->txedDependencias->setPlainText( ip->dependencies().join("\n") );
	ui->txedDescripcion->setPlainText( ip->description() );
	ui->ledDesarrollador->setText( ip->developer() );
}
