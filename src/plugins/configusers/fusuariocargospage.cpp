#include "fusuariocargospage.h"
#include "ui_fusuariocargospage.h"

FUsuarioCargosPage::FUsuarioCargosPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FUsuarioCargosPage)
{
    ui->setupUi(this);

    model = new UsuarioCargoModel(this);
    model->configureQuery()->allAttributes();
    model->configureQuery()->addOrderBy("Cargo");
    ui->lvwUsuarios->setModel(model);
}

FUsuarioCargosPage::~FUsuarioCargosPage()
{
    delete ui;
}

QWidget *FUsuarioCargosPage::widget()
{
    return this;
}

void FUsuarioCargosPage::updatePage()
{
    model->select();
    ui->lvwUsuarios->setModelColumn(1);
}

void FUsuarioCargosPage::on_btnNuevo_clicked()
{
    QString cargo = QInputDialog::getText(this,"Nuevo cargo","Ingrese el nombre del nuevo cargo");

    if ( cargo.isEmpty() )
        return;

    UsuarioCargoRecord r;
    r.setCargo(cargo);
    TSqlError error;

    error = r.insert();
    if ( error.isError() )
    {
        QMessageBox::critical(this,"Error","No se pudo crear el cargo");
        return;
    }
    updatePage();
}
