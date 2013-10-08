#include "freporteventas.h"
#include "ui_freporteventas.h"

freporteventas::freporteventas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::freporteventas)
{
    ui->setupUi(this);
}

freporteventas::~freporteventas()
{
    delete ui;
}
