#include "fingreso.h"
#include "ui_fingreso.h"

fIngreso::fIngreso(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fIngreso)
{
    ui->setupUi(this);
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
    error=libro.insert();
    close();

}
