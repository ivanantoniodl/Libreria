#ifndef FINGRESOAUTOR_H
#define FINGRESOAUTOR_H

#include <QDialog>
#include "autorrecord.h"
#include "tsqlerror.h"
namespace Ui {
class fIngresoAutor;
}

class fIngresoAutor : public QDialog
{
    Q_OBJECT
    
public:
    explicit fIngresoAutor(QWidget *parent = 0);
    ~fIngresoAutor();
    
private slots:
    void on_btnGuardar_clicked();

private:
    Ui::fIngresoAutor *ui;
};

#endif // FINGRESOAUTOR_H
