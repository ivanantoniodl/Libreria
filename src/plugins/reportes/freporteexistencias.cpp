#include "freporteexistencias.h"
#include "ui_freporteexistencias.h"

freporteexistencias::freporteexistencias(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::freporteexistencias)
{
    ui->setupUi(this);
}

freporteexistencias::~freporteexistencias()
{
    delete ui;
}


void  freporteexistencias::openReport()
{
	exec();

	//todo lo necesario

	//QMessageBox::information(this,"reporte","Mostrando reporte");

}

void freporteexistencias::on_btnVerReporte_clicked()
{
	//consultas, etc.

	genORPT *generador = new genORPT(this);

	QString filename;

	filename.append(QApplication::applicationDirPath());
	filename.append("/reportes/ReporteExistencias.xml");

	if(!filename.isEmpty())
	{

		generador->parametro()->clear();


		generador->parametro()->append("existencia",ui->spxExistencias->value());

		generador->abrirArchivo(filename);
		generador->imprimir(true,1);
	}
	else
		QMessageBox::critical(this,"Error","no se encontro el reporte:w");



}
