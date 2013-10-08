#ifndef FMAQUINASPAGE_H
#define FMAQUINASPAGE_H

#include <QRecordWidgetMapper>

#include "configpage.h"
#include "maquinamodel.h"
#include "lugarmodel.h"
#include "configlugar_global.h"

namespace Ui {
    class FMaquinasPage;
}

class CONFIGLUGARSHARED_EXPORT FMaquinasPage : public QRecordWidgetMapper, public ConfigPage
{
    Q_OBJECT

public:
    explicit FMaquinasPage(QWidget *parent = 0);
    ~FMaquinasPage();

	QString shortTitle() { return "Maquinas"; }
	bool showApplyOk() { return false; }
	bool apply() { return true; }
	QWidget *widget();
	void updatePage();

private slots:
	void on_btnNuevo_clicked();
	void on_btnCancelar_clicked();
	void on_btnGuardar_clicked();

	void on_tbvwMaquinas_clicked(const QModelIndex &index);

private:
    Ui::FMaquinasPage *ui;
	MaquinaModel *model;
	LugarModel *lugarModel;
};

#endif // FMAQUINASPAGE_H
