#include "fejemplodialog.h"
#include "ui_fejemplodialog.h"

FEjemploDialog::FEjemploDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FEjemploDialog)
{
	ui->setupUi(this);
	//en el contructor no hacer consultas sql porfavor, eso hacerlo en el openReport()
}

FEjemploDialog::~FEjemploDialog()
{
    delete ui;
}

void FEjemploDialog::openReport()
{
	//ejecutando el dialogo
	exec();
}

void FEjemploDialog::on_pushButton_clicked()
{
	//consultas, etc.

	generador = new genORPT(this);

	//todo lo necesario

	QMessageBox::information(this,"reporte","Mostrando reporte");
}

//como este plugin de reporte esta dentro de un plugin de colleccion no es necesario poner Q_EXPORT_PLUGIN2()

void FEjemploDialog::on_btnODS_clicked()
{
    //Ejemplo de reporte ods

    configOdsReport *odsReport;

    odsReport = new configOdsReport(this);
    QStringList cabeceras;

    cabeceras<<"Prueba"<<"Prueba2";

    odsReport->agregarCabecera(cabeceras);
    odsReport->forzarFilaANumero(6);

    QStringList data;

    for(int c=0; c<10; c++)
    {
        data << "1";
        data << "2";
        odsReport->agregarFila(data);
        data.clear();
    }
    odsReport->exportar();
}
