#include "froladminpage.h"
#include "ui_froladminpage.h"

FRolAdminPage::FRolAdminPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FRolAdminPage)
{
    ui->setupUi(this);
	seleccionado = NULL;
	rolSeleccionado = NULL;

    permisoModel = new PermisoModel(this);
    arbolPermisos = new modeloArbolPermisos(this);
	boolColor = new BooleanColor(this);

	ui->tvwPermisos->setItemDelegateForColumn(1,boolColor);
	ui->tvwPermisos->setItemDelegateForColumn(2,boolColor);
	ui->tvwPermisos->setColumnWidth(0,250);
    ui->tvwPermisos->setColumnWidth(1,50);
    ui->tvwPermisos->setColumnWidth(2,50);
    ui->tvwPermisos->setAlternatingRowColors(true);
	ui->tvwPermisos->setModel(arbolPermisos);

    rolModel = new RolModel(this);
    rolModel->configureQuery()->allAttributes();
    rolModel->configureQuery()->addOrderBy("Rol");
    ui->lvwRoles->setModel(rolModel);

    actualizarRoles();
}

FRolAdminPage::~FRolAdminPage()
{
    delete ui;
}

QWidget *FRolAdminPage::widget()
{
    return this;
}

void FRolAdminPage::actualizarRoles()
{
    rolModel->select();
    ui->lvwRoles->setModelColumn(1);
}

void FRolAdminPage::on_btnAdd_clicked()
{
    QString rol = QInputDialog::getText(this,"Nuevo rol","Ingrese el nombre del nuevo rol");

    if ( rol.isEmpty() )
        return;

    RolRecord r;
    r.setRol(rol);
    TSqlError error;

    error = r.insert();
    if ( error.isError() )
    {
        QMessageBox::critical(this,"Error","No se pudo crear el nuevo rol");
        return;
    }
    actualizarRoles();
}

void FRolAdminPage::on_lvwRoles_clicked(const QModelIndex &index)
{
    rolSeleccionado = ui->lvwRoles->getSelectedRecords<RolRecord*>().at(0);
	arbolPermisos->filtrar(rolSeleccionado->idRol());
    ui->tvwPermisos->reset();
	ui->tvwPermisos->expandAll();
	ui->tvwPermisos->resizeColumnToContents( 0 );
}

void FRolAdminPage::on_tvwPermisos_clicked(const QModelIndex &index)
{
	if ( ! rolSeleccionado )
		return;

	if ( ! arbolPermisos->hasChildren( index ) )
	{
		ui->tvwPermisos->resizeColumnToContents( 0 );
		seleccionado = arbolPermisos->nodoDesdeIndice( index );
	}
	else
		seleccionado = NULL;
}

void FRolAdminPage::on_tvwPermisos_doubleClicked(const QModelIndex &index)
{
	Q_UNUSED(index);
	on_btnEditarPermisos_clicked();
}

void FRolAdminPage::on_btnEditarPermisos_clicked()
{
	if ( seleccionado )
	{
		FRolPersmisosModificar *v = new FRolPersmisosModificar(seleccionado->getIdDB(),
															   seleccionado->permisoR,
															   seleccionado->permisoW,
															   this);
		v->exec();
		delete v;
		arbolPermisos->filtrar( rolSeleccionado->idRol() );
	}
}
