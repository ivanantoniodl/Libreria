#include "fautores.h"
#include "ui_fautores.h"

fautores::fautores(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fautores)
{
    ui->setupUi(this);
    autores =new AutorModel(this);
    cargarAutores();
    ui->tvwAutores->setModel(autores);
    ui->tvwAutores->resizeColumnsToContents();
}

fautores::~fautores()
{
    delete ui;
}

void fautores::cargarAutores()
{
    autores->clearQuery();
    autores->configureQuery()->Nombre();
    autores->configureQuery()->Direccion();
    autores->select();
}

void fautores::on_btnNuevo_clicked()
{
    fIngresoAutor *autor =new fIngresoAutor(this);
    autor->exec();
    cargarAutores();
}
