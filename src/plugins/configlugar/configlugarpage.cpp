#include "configlugarpage.h"

ConfigLugarPage::ConfigLugarPage()
{
}

QWidget *ConfigLugarPage::widget()
{
	QWidget *w = new QWidget;
	ui.setupUi(w);

	model = new LugarModel(this);
	model->configureQuery()->idLugar();
	model->configureQuery()->Nombre();
	model->configureQuery()->addOrderBy("Nombre");

	ui.cbxLugar->setModel(model);
	ui.cbxLugar->setModelColumn(1);

	QSettings settings;
	settings.beginGroup("Lugar");
	int idlugar = settings.value("idLugar").toInt();
	settings.endGroup();

	if ( idlugar != 0 )
	{
		QVariantList lst;
		lst.append(idlugar);
		ui.cbxLugar->setCurrentPKValues( lst );
	}

	return w;
}

bool ConfigLugarPage::apply()
{
	LugarRecord *record = new LugarRecord;
	record->setIdLugar( ui.cbxLugar->currentPKValues().at(0).toInt() );
	TSqlError error;
	error = record->select();
	if ( error.isError() )
		return false;

	QSettings settings;
	settings.beginGroup("Lugar");
	settings.setValue("idLugar",ui.cbxLugar->currentPKValues().at(0).toInt());
	settings.endGroup();

	delete MaquinaModel::CurrentLugarRecord;

	MaquinaModel::CurrentLugarRecord=record;
	return true;
}

void ConfigLugarPage::updatePage()
{
	model->select();
}
