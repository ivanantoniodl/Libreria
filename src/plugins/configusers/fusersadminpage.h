#ifndef FUSERSADMINPAGE_H
#define FUSERSADMINPAGE_H

#include <QRecordWidgetMapper>
#include <QInputDialog>
#include "configplugin.h"

#include "usuariomodel.h"
#include "empresamodel.h"
#include "usuariocargomodel.h"
#include "rolmodel.h"
#include "usuariomodel.h"
#include "maquinamodel.h"
#include "configusers_global.h"

namespace Ui {
    class FUsersAdminPage;
}

class CONFIGUSERSSHARED_EXPORT FUsersAdminPage : public QRecordWidgetMapper, public ConfigPage
{
    Q_OBJECT

private:
	QSqlDatabase getRootDBConecction(bool&);
	UsuarioRecord *usuarioSeleccionadoRecord;

public:
    FUsersAdminPage(QWidget *parent = 0);
    ~FUsersAdminPage();

    QString shortTitle() { return "Usuarios"; }
    QWidget *widget();

    bool apply();
    bool showApplyOk() { return false; }
	void updatePage();

private slots:
	void on_btnNuevo_clicked();
	void on_btnGuardar_clicked();
	void on_lvwUsuarios_clicked(const QModelIndex &index);
	void on_btnCancelar_clicked();
	void on_btnModificarClave_clicked();
	void on_btnEliminar_clicked();
	void principalModel_updated();

private:
    Ui::FUsersAdminPage *ui;
	bool insertandoNuevo;

	UsuarioModel *usuarioModel;
	EmpresaModel *empresaModel;
	RolModel *rolModel;
	UsuarioCargoModel *cargoModel;

	QVariantList lastCargoSelected,lastEmpresaSelected,lastRolSelected;
};

#endif // FUSERSADMINPAGE_H
