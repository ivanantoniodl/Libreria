#ifndef CONFIGLUGARPAGE_H
#define CONFIGLUGARPAGE_H

#include "configpage.h"
#include "lugarmodel.h"
#include "maquinamodel.h"

#include "ui_flugarconfig.h"
#include "configlugar_global.h"

class CONFIGLUGARSHARED_EXPORT ConfigLugarPage : public QObject, public ConfigPage
{
Q_OBJECT
private:
	Ui::FLugarConfig ui;
	LugarModel *model;

public:
	ConfigLugarPage();

	QString shortTitle() { return "Lugar actual"; }
	QWidget *widget();

	bool apply();
	bool showApplyOk() { return true; }

	void updatePage();
};

#endif // CONFIGLUGARPAGE_H
