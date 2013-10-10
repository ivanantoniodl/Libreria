#ifndef FINGRESO_H
#define FINGRESO_H

#include <QDialog>
#include "librorecord.h"
#include "tsqlerror.h"

namespace Ui {
class fIngreso;
}

class fIngreso : public QDialog
{
    Q_OBJECT
    
public:
    explicit fIngreso(QWidget *parent = 0);
    explicit fIngreso(int idL,QWidget *parent = 0);
    ~fIngreso();
    
private slots:
    void on_btnGuardar_clicked();

private:
    Ui::fIngreso *ui;
    int id;
};

#endif // FINGRESO_H
