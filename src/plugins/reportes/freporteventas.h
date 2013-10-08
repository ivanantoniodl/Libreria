#ifndef FREPORTEVENTAS_H
#define FREPORTEVENTAS_H

#include <QDialog>
#include "reportes_global.h"

namespace Ui {
    class freporteventas;
}

class REPORTESSHARED_EXPORT freporteventas : public QDialog
{
    Q_OBJECT

public:
    explicit freporteventas(QWidget *parent = 0);
    ~freporteventas();

private:
    Ui::freporteventas *ui;
};

#endif // FREPORTEVENTAS_H
