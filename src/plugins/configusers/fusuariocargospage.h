#ifndef FUSUARIOCARGOSPAGE_H
#define FUSUARIOCARGOSPAGE_H

#include <QWidget>
#include <QInputDialog>

#include "configplugin.h"
#include "usuariocargomodel.h"
#include "configusers_global.h"

namespace Ui {
    class FUsuarioCargosPage;
}

class CONFIGUSERSSHARED_EXPORT FUsuarioCargosPage : public QWidget, public ConfigPage
{
    Q_OBJECT

public:
    FUsuarioCargosPage(QWidget *parent = 0);
    ~FUsuarioCargosPage();

    QString shortTitle() { return "Cargos"; }
    QWidget *widget();

    bool apply() { return true; }
    bool showApplyOk() { return false; }
    void updatePage();

private slots:
    void on_btnNuevo_clicked();

private:
    Ui::FUsuarioCargosPage *ui;
    UsuarioCargoModel *model;
};

#endif // FUSUARIOCARGOSPAGE_H
