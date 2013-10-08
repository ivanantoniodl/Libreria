#include "flugartipopage.h"
#include "ui_flugartipopage.h"

FLugarTipoPage::FLugarTipoPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FLugarTipoPage)
{
    ui->setupUi(this);

	model = new LugarTipoModel(this);
	model->configureQuery()->allAttributes();
	model->configureQuery()->addOrderBy( "Tipo" );
	model->select();
	ui->lvwTipo->setModel(model);
	ui->lvwTipo->setModelColumn(1);
}

FLugarTipoPage::~FLugarTipoPage()
{
    delete ui;
}

QWidget *FLugarTipoPage::widget() { return this; }

void FLugarTipoPage::on_btnNuevo_clicked()
{
	QString tipo = QInputDialog::getText(this,"Nuevo tipo","Ingrese el nombre del nuevo tipo");

	if ( tipo.isEmpty() )
		return;

	LugarTipoRecord r;
	r.setTipo( tipo );
	TSqlError error;

	error = r.insert();
	if ( error.isError() )
	{
		QMessageBox::critical(this,"Error","No se pudo crear el tipo");
		return;
	}
	updatePage();
}

bool FLugarTipoPage::apply()
{
	return true;
}

void FLugarTipoPage::updatePage()
{
	model->select();
	ui->lvwTipo->setModelColumn(1);
}
