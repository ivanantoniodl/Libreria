#ifndef REPORTPLUGIN_H
#define REPORTPLUGIN_H

#include "iplugin.h"

class CORESHARED_EXPORT ReportPlugin : public IPlugin
{
public:
    ReportPlugin();
    ~ReportPlugin();
	virtual void openReport() = 0;
};

Q_DECLARE_INTERFACE(ReportPlugin,"ReportPlugin")

#endif // REPORTPLUGIN_H
