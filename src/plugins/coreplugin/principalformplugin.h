#ifndef PRINCIPALFORMPLUGIN_H
#define PRINCIPALFORMPLUGIN_H

#include <QDialog>
#include <QLayout>
#include "iplugin.h"

class CORESHARED_EXPORT PrincipalFormPlugin : public IPlugin
{
public:
    enum TypeForm
    {
        TypeWidget,
        TypeDialog
    };

    PrincipalFormPlugin(TypeForm t=TypeWidget);
    ~PrincipalFormPlugin();
	virtual QString menuGroup() = 0;
	virtual QString menuName() = 0;
    virtual QWidget *widget();
    virtual QDialog *dialog();
    TypeForm getTypeForm() { return TYPE; }

    static QDialog *dialogFromWidget(QWidget *);
private:
    TypeForm TYPE;
};

Q_DECLARE_INTERFACE(PrincipalFormPlugin,"PrincipalFormPlugin")

#endif // PRINCIPALFORMPLUGIN_H

