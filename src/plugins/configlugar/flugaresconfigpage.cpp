#include "flugaresconfigpage.h"
#include "ui_flugaresconfigpage.h"

FLugaresConfigPage::FLugaresConfigPage(QWidget *parent) :
    QRecordWidgetMapper(parent),
    ui(new Ui::FLugaresConfigPage)
{
    ui->setupUi(this);
	lugarRecordSeleccionado=NULL;

	lugarModel = new LugarModel(this);
	lugarModel->configureQuery()->allAttributes();
	lugarModel->configureQuery()->addOrderBy("Nombre");
	lugarModel->select();
	setModel( lugarModel );

	ui->lvwLugares->setModel( lugarModel );
	ui->lvwLugares->setModelColumn( 3 );

	lugarTipoModel = new LugarTipoModel(this);
	lugarTipoModel->configureQuery()->Tipo();
	ui->cbmrTipo->setModel(lugarTipoModel);
	ui->cbmrTipo->setModelColumn(1);

	empresaModel = new EmpresaModel(this);
	empresaModel->configureQuery()->Nombre();
	ui->cbmrEmpresa->setModel(empresaModel);
	ui->cbmrEmpresa->setModelColumn(1);

	addMapper("Empresa_idEmpresa",ui->cbmrEmpresa);
	addMapper("LugarTipo_idLugarTipo",ui->cbmrTipo);
	addMapper("Nombre",ui->ledNombre);
	addMapper("Direccion",ui->ledDireccion);
	addMapper("Telefono",ui->ledTelefono);

	insertandoNuevo=false;
}

FLugaresConfigPage::~FLugaresConfigPage()
{
    delete ui;
}

void FLugaresConfigPage::updatePage()
{
	empresaModel->select();
	lugarTipoModel->select();
}

QWidget *FLugaresConfigPage::widget()
{
	return this;
}

bool FLugaresConfigPage::apply()
{
	return true;
}

void FLugaresConfigPage::on_btnNuevo_clicked()
{
	newRecord();
	insertandoNuevo=true;
	ui->groupBox->setEnabled(true);
	ui->ledNombre->setFocus();
}

void FLugaresConfigPage::on_lvwLugares_clicked(const QModelIndex &index)
{
	toRecord( index.row() );
	ui->groupBox->setEnabled(true);
	insertandoNuevo=false;
	ui->ledNombre->setFocus();
}

void FLugaresConfigPage::on_btnGuardar_clicked()
{
	TSqlError error;

	if ( insertandoNuevo )
		error = submit();
	else
		error = submitAll();

	ui->groupBox->setEnabled(false);
}

void FLugaresConfigPage::on_btnCancelar_clicked()
{
	revertAll();
	insertandoNuevo=false;
	ui->groupBox->setEnabled(false);
}
