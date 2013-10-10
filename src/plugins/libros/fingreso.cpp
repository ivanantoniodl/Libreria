#include "fingreso.h"
#include "ui_fingreso.h"

fIngreso::fIngreso(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fIngreso)
{
    ui->setupUi(this);
    id=0;
}

fIngreso::fIngreso(int idL,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fIngreso)
{
    ui->setupUi(this);

    id=idL;

    LibroRecord Libro;

    Libro.setId(id);
    Libro.select();

    ui->ledNombre->setText(Libro.Nombre());
    ui->ledAnio->setText(Libro.AnioImp());

}

fIngreso::~fIngreso()
{
    delete ui;
}

void fIngreso::on_btnGuardar_clicked()
{
    LibroRecord libro;
    TSqlError error;

    libro.setNombre(ui->ledNombre->text());
    libro.setAnioImp(ui->ledAnio->text());

    if(id>0)
    {
        libro.setId(id);
        error = libro.update();
    }
    else
        error=libro.insert();

    close();

}
