#include "fprincipallibro.h"
#include "ui_fprincipallibro.h"

fprincipallibro::fprincipallibro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fprincipallibro)
{
    ui->setupUi(this);
}

fprincipallibro::~fprincipallibro()
{
    delete ui;
}
