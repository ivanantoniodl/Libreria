#ifndef FROLPERSMISOSMODIFICAR_H
#define FROLPERSMISOSMODIFICAR_H

#include <QDialog>
#include "rolpermisomodel.h"
#include "configusers_global.h"

namespace Ui {
    class FRolPersmisosModificar;
}

class CONFIGUSERSSHARED_EXPORT FRolPersmisosModificar : public QDialog
{
    Q_OBJECT

public:
	explicit FRolPersmisosModificar(int id, bool r, bool w,QWidget *parent = 0);
    ~FRolPersmisosModificar();

private slots:
	void on_btnAceptar_clicked();

private:
    Ui::FRolPersmisosModificar *ui;
	int idpr;
};

#endif // FROLPERSMISOSMODIFICAR_H
