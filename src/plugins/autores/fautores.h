#ifndef FAUTORES_H
#define FAUTORES_H

#include <QDialog>
#include "autormodel.h"
#include "fingresoautor.h"

namespace Ui {
class fautores;
}

class fautores : public QDialog
{
    Q_OBJECT
    
public:
    explicit fautores(QWidget *parent = 0);
    ~fautores();
    
private slots:
    void on_btnNuevo_clicked();

private:
    Ui::fautores *ui;
    AutorModel *autores;
    void cargarAutores();

};

#endif // FAUTORES_H
