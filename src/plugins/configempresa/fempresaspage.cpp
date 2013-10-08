#include "fempresaspage.h"
#include "ui_fempresaspage.h"

FEmpresasPage::FEmpresasPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FEmpresasPage)
{
    ui->setupUi(this);

    model = new EmpresaModel(this);
    model->configureQuery()->allAttributes();

    ui->lvwUsuarios->setModel(model);
    ui->cbxEmpresa->setModel(model);

    QSettings settings;
    settings.beginGroup("Empresa");
    ActualIdEmpresa = settings.value("idEmpresa").toInt();
    settings.endGroup();

    actualizar();
}

FEmpresasPage::~FEmpresasPage()
{
    delete ui;
}

void FEmpresasPage::actualizar()
{
    model->select();

    ui->lvwUsuarios->setModelColumn(1);
    ui->cbxEmpresa->setModelColumn(1);

    if ( ActualIdEmpresa == 0 )
        ui->cbxEmpresa->setCurrentIndex(0);
    else
        ui->cbxEmpresa->setCurrentPKValues( QVariantList() << ActualIdEmpresa );
}

QWidget *FEmpresasPage::widget()
{
    return this;
}

bool FEmpresasPage::apply()
{
    EmpresaRecord *record = new EmpresaRecord;
    record->setIdEmpresa( ui->cbxEmpresa->currentPKValues().at(0).toInt() );
    TSqlError error;
    error = record->select();
    if ( error.isError() )
        return false;

    QSettings settings;
    settings.beginGroup("Empresa");
    settings.setValue("idEmpresa",ui->cbxEmpresa->currentPKValues().at(0).toInt());
    settings.endGroup();

    delete MaquinaModel::CurrentEmpresaRecord;

    MaquinaModel::CurrentEmpresaRecord=record;

    ActualIdEmpresa = ui->cbxEmpresa->currentPKValues().at(0).toInt();
    return true;
}

ConfigEmpresa::ConfigEmpresa()
{
    addPage( new FEmpresasPage );
}

QIcon ConfigEmpresa::icon()
{
    return QIcon(":/pics/edificio.png");
}

void FEmpresasPage::on_btnNuevo_clicked()
{
    QString empresa = QInputDialog::getText(this,"Nueva empresa","Ingrese el nombre de la nueva empresa");

    if ( empresa.isEmpty() )
        return;

    EmpresaRecord r;
    r.setNombre(empresa);
    TSqlError error;

    error = r.insert();
    if ( error.isError() )
    {
        QMessageBox::critical(this,"Error","No se pudo crear la empresa");
        return;
    }
    actualizar();
}


Q_EXPORT_PLUGIN2(ConfigEmpresa, ConfigEmpresa)
