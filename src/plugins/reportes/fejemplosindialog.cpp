#include "fejemplosindialog.h"

FEjemploSinDialog::FEjemploSinDialog()
{
	//en el contructor no hacer consultas sql porfavor, eso hacerlo en el openReport()
}

void FEjemploSinDialog::openReport()
{
	//consultas, etc.

	genORPT *generador = new genORPT(this);

	//todo lo necesario

	QMessageBox::information(this,"reporte","Mostrando reporte");
}

//como este plugin de reporte esta dentro de un plugin de colleccion no es necesario poner Q_EXPORT_PLUGIN2()
