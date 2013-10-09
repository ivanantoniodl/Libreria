#include "flibros.h"
#include "ui_flibros.h"

flibros::flibros(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::flibros)
{
    ui->setupUi(this);
    libros =new LibroModel(this);
    cargarLibros();
    ui->tvwLibros->setModel(libros);
    ui->tvwLibros->resizeColumnsToContents();
    ui->tvwLibros->setColumnHidden(0,true);
}

flibros::~flibros()
{
    delete ui;
}


void flibros::cargarLibros()
{
    libros->clearQuery();
    libros->configureQuery()->id();
    libros->configureQuery()->Nombre();
    libros->select();
}


void flibros::on_btnNuevo_clicked()
{
    fIngreso *v =new fIngreso(this);
    v->exec();

    cargarLibros();
}
