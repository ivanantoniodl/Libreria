#ifndef FCONFCONEXION_H
#define FCONFCONEXION_H

#include <QtGui/QDialog>

namespace Ui {
    class fConfConexion;
}

class fConfConexion : public QDialog {
    Q_OBJECT
public:
    fConfConexion(QWidget *parent = 0);
    ~fConfConexion();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::fConfConexion *m_ui;
    bool guardarPathScript;

private slots:
    void on_btnExaminar_clicked();
    void on_cbxTipoServidor_currentIndexChanged(int index);
    void on_btnAceptar_clicked();
};

#endif // FCONFCONEXION_H
