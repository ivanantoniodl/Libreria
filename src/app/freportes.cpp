#include "freportes.h"
#include "ui_freportes.h"

#include "mainwindow.h"

FReportes::FReportes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FReportes)
{
    ui->setupUi(this);
	lstReports = MainWindow::instance()->getLstReportPlugins();

	foreach ( ReportPlugin* plugin, lstReports )
	{
		int filas = ui->tbvwReportes->rowCount();
		ui->tbvwReportes->setRowCount(filas+1);

		QTableWidgetItem *item0 = new QTableWidgetItem;
		item0->setData ( Qt::DisplayRole , plugin->name() );
		item0->setFlags ( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
		ui->tbvwReportes->setItem (filas, 0, item0 );

		QTableWidgetItem *item1 = new QTableWidgetItem;
		item1->setData ( Qt::DisplayRole , plugin->description() );
		item1->setFlags ( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
		ui->tbvwReportes->setItem (filas, 1, item1 );
	}
	ui->tbvwReportes->resizeColumnsToContents();
}

FReportes::~FReportes()
{
    delete ui;
}

void FReportes::on_tbvwReportes_clicked(const QModelIndex &index)
{
	seleccionado=index.row();
	ui->btnAbrirReporte->setEnabled(true);
}

void FReportes::on_tbvwReportes_doubleClicked(const QModelIndex &index)
{
	on_btnAbrirReporte_clicked();
}

void FReportes::on_btnAbrirReporte_clicked()
{
	ReportPlugin *plugin = lstReports.at(seleccionado);
	plugin->openReport();
}
