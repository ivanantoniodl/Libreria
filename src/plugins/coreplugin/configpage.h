#ifndef CONFIGPAGE_H
#define CONFIGPAGE_H

#include <QtCore>
#include "core_global.h"

class ConfigDialog;

class CORESHARED_EXPORT ConfigPage
{
friend class ConfigDialog;
public:
    ConfigPage();
    virtual ~ConfigPage();
	virtual QString shortTitle() = 0;
	virtual QWidget *widget() = 0;
    virtual bool showApplyOk() = 0;
	virtual bool apply() = 0;
    virtual void updatePage();
};

#endif // CONFIGPAGE_H
