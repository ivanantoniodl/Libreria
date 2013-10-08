#ifndef CONFIGPLUGIN_H
#define CONFIGPLUGIN_H

#include <QWidget>

#include "iplugin.h"
#include "configpage.h"

class ConfigDialog;

class CORESHARED_EXPORT ConfigPlugin : public IPlugin
{
friend class ConfigDialog;
private:
	QList<ConfigPage*> lstPages;
public:
    ConfigPlugin();
    ~ConfigPlugin();
	virtual QString shortTitle() = 0;
	virtual QIcon icon() = 0;

	void addPage(ConfigPage*);
};

Q_DECLARE_INTERFACE(ConfigPlugin,"ConfigPlugin")

#endif // CONFIGLUGIN_H
