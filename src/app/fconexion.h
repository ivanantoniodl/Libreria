#ifndef FCONEXION_H
#define FCONEXION_H

#include <QtGui/QDialog>

namespace Ui {
    class FConexion;
}

class FConexion : public QDialog {
    Q_OBJECT
public:
    FConexion(QWidget *parent = 0);
    ~FConexion();
    QString getUsuario();
    QString getPass();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::FConexion *m_ui;

private slots:
    void on_btnConectar_clicked();
    void on_pushButton_clicked();
    void on_btnConfigurar_clicked();
    void setSettings();
};

#endif // FCONEXION_H
