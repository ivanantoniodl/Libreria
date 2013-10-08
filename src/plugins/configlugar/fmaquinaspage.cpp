#include "fmaquinaspage.h"
#include "ui_fmaquinaspage.h"

FMaquinasPage::FMaquinasPage(QWidget *parent) :
    QRecordWidgetMapper(parent),
    ui(new Ui::FMaquinasPage)
{
    ui->setupUi(this);
	model = new MaquinaModel(this);
	model->configureQuery()->idMaquina();
	model->configureQuery()->Ip();
	model->configureQuery()->RLugar_()->Nombre();
	model->setHeaderData(3,Qt::Horizontal,"Lugar");
	ui->tbvwMaquinas->setModel(model);

	lugarModel = new LugarModel(this);
	lugarModel->configureQuery()->idLugar();
	lugarModel->configureQuery()->Nombre();
	lugarModel->configureQuery()->addOrderBy("Nombre");
	ui->cbxLugar->setModel(lugarModel);
	ui->cbxLugar->setModelColumn(1);

	setModel(model);
	addMapper("Ip",ui->ledIp);
	addMapper("Lugar_idLugar",ui->cbxLugar);
}

FMaquinasPage::~FMaquinasPage()
{
    delete ui;
}

QWidget *FMaquinasPage::widget() { return this; }

void FMaquinasPage::updatePage()
{
	model->select();
	ui->tbvwMaquinas->hideColumn(0);
	ui->tbvwMaquinas->hideColumn(2);
	lugarModel->select();
}

void FMaquinasPage::on_btnNuevo_clicked()
{
	ui->grbxMaquina->setEnabled(true);
	newRecord();
}

void FMaquinasPage::on_btnCancelar_clicked()
{
	ui->grbxMaquina->setEnabled(false);
	revertAll();
}

void FMaquinasPage::on_btnGuardar_clicked()
{
	TSqlError error;
	error = submitAll();
	ui->grbxMaquina->setEnabled(false);
}

void FMaquinasPage::on_tbvwMaquinas_clicked(const QModelIndex &index)
{
	ui->grbxMaquina->setEnabled(true);
}
