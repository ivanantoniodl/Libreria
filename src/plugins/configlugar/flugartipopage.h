#ifndef FLUGARTIPOPAGE_H
#define FLUGARTIPOPAGE_H

#include <QWidget>
#include <QInputDialog>

#include "configpage.h"
#include "lugartipomodel.h"
#include "configlugar_global.h"

namespace Ui {
    class FLugarTipoPage;
}

class CONFIGLUGARSHARED_EXPORT FLugarTipoPage : public QWidget , public ConfigPage
{
    Q_OBJECT

public:
    explicit FLugarTipoPage(QWidget *parent = 0);
    ~FLugarTipoPage();

	QString shortTitle() { return "Tipo de lugar"; }
	QWidget *widget();

	bool apply();
	bool showApplyOk() { return false; }

	void updatePage();

private slots:
	void on_btnNuevo_clicked();

private:
    Ui::FLugarTipoPage *ui;

	LugarTipoModel *model;
};

#endif // FLUGARTIPOPAGE_H
