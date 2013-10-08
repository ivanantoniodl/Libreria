#include "frolpersmisosmodificar.h"
#include "ui_frolpersmisosmodificar.h"

FRolPersmisosModificar::FRolPersmisosModificar(int id, bool r, bool w,QWidget *parent) :
	QDialog(parent),
    ui(new Ui::FRolPersmisosModificar)
{
    ui->setupUi(this);
	idpr=id;

	ui->chbxR->setChecked( r );
	ui->chbxW->setChecked( w );
}

FRolPersmisosModificar::~FRolPersmisosModificar()
{
    delete ui;
}

void FRolPersmisosModificar::on_btnAceptar_clicked()
{
	short int permisos = 0;

	if ( ui->chbxR->isChecked() )
		permisos |= 4;
	if ( ui->chbxW->isChecked() )
		permisos |= 8;

	RolPermisoRecord r;
	r.setIdRolPermiso( idpr );
	r.setPermiso( permisos );
	r.update();
	close();
}
