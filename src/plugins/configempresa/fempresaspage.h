#ifndef FEMPRESASPAGE_H
#define FEMPRESASPAGE_H

#include <QWidget>
#include <QInputDialog>

#include "configplugin.h"

#include "empresamodel.h"
#include "maquinamodel.h"

#include "configempresa_global.h"

namespace Ui {
    class FEmpresasPage;
}

class CONFIGEMPRESASHARED_EXPORT FEmpresasPage : public QWidget, public ConfigPage
{
    Q_OBJECT
private:
    EmpresaModel *model;
    int ActualIdEmpresa;

    void actualizar();

public:
    FEmpresasPage(QWidget *parent = 0);
    ~FEmpresasPage();

    QString shortTitle() { return "Empresas"; }
    QWidget *widget();

    bool apply();
    bool showApplyOk() { return true; }

private slots:
    void on_btnNuevo_clicked();

private:
    Ui::FEmpresasPage *ui;
};

class CONFIGEMPRESASHARED_EXPORT ConfigEmpresa : public QObject, public ConfigPlugin
{
    Q_OBJECT
    Q_INTERFACES(ConfigPlugin)

public:
    ConfigEmpresa();
    QString name() { return "ConfigurarEmpresa"; }
    QStringList dependencies() { return QStringList(); }
    QString description() {	 return "Configura las empresas y el de la maquina actual"; }

    QString shortTitle() { return "Empresa"; }
    QIcon icon();
};

#endif // FEMPRESASPAGE_H
