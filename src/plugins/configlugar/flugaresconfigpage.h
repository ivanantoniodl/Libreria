#ifndef FLUGARESCONFIGPAGE_H
#define FLUGARESCONFIGPAGE_H

#include <QRecordWidgetMapper>
#include "configpage.h"

#include "lugarmodel.h"
#include "lugartipomodel.h"
#include "empresamodel.h"
#include "configlugar_global.h"

namespace Ui {
    class FLugaresConfigPage;
}

class CONFIGLUGARSHARED_EXPORT FLugaresConfigPage : public QRecordWidgetMapper , public ConfigPage
{
    Q_OBJECT

public:
    explicit FLugaresConfigPage(QWidget *parent = 0);
    ~FLugaresConfigPage();

	QString shortTitle() { return "Lugares"; }
	QWidget *widget();

	bool apply();
	bool showApplyOk() { return false; }

	void updatePage();

private slots:
	void on_btnNuevo_clicked();

	void on_lvwLugares_clicked(const QModelIndex &index);

	void on_btnGuardar_clicked();

	void on_btnCancelar_clicked();

private:
    Ui::FLugaresConfigPage *ui;

	LugarTipoModel *lugarTipoModel;
	EmpresaModel *empresaModel;
	LugarModel* lugarModel;

	LugarRecord* lugarRecordSeleccionado;

	bool insertandoNuevo;
};

#endif // FLUGARESCONFIGPAGE_H
