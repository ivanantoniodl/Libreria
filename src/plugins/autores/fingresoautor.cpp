#include "fingresoautor.h"
#include "ui_fingresoautor.h"

fIngresoAutor::fIngresoAutor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fIngresoAutor)
{
    ui->setupUi(this);
}

fIngresoAutor::~fIngresoAutor()
{
    delete ui;
}

void fIngresoAutor::on_btnGuardar_clicked()
{
    AutorRecord autor=new AutorRecord(this);
    TSqlError error;
    autor.setNombre(ui->ledNombre->text());
    autor.setDireccion(ui->ledDireccion->text());
    error=autor.insert();

}
