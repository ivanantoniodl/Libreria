#ifndef FROLADMINPAGE_H
#define FROLADMINPAGE_H

#include <QWidget>
#include "configplugin.h"

#include "rolmodel.h"
#include "rolpermisomodel.h"
#include "permisomodel.h"

#include "modeloarbolpermisos.h"
#include "booleancolor.h"

#include "configusers_global.h"
#include "frolpersmisosmodificar.h"

namespace Ui {
    class FRolAdminPage;
}

class CONFIGUSERSSHARED_EXPORT FRolAdminPage : public QWidget , public ConfigPage
{
    Q_OBJECT
private:
    Ui::FRolAdminPage *ui;
	NodoPermisos *seleccionado;

    PermisoModel *permisoModel;
    RolModel *rolModel;
    RolPermisoModel *rolPermisoModel;

    BooleanColor *boolColor;
    modeloArbolPermisos *arbolPermisos;

	RolRecord *rolSeleccionado;

    void actualizarRoles();

public:
    FRolAdminPage(QWidget *parent = 0);
    ~FRolAdminPage();

    QString shortTitle() { return "Roles"; }
    QWidget *widget();

	bool apply() { return true; }
	bool showApplyOk() { return false; }
private slots:
    void on_btnAdd_clicked();
    void on_lvwRoles_clicked(const QModelIndex &index);
    void on_tvwPermisos_clicked(const QModelIndex &index);

	void on_tvwPermisos_doubleClicked(const QModelIndex &index);
	void on_btnEditarPermisos_clicked();
};

#endif // FROLADMINPAGE_H
