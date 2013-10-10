#ifndef FLIBROS_H
#define FLIBROS_H

#include <QDialog>
#include "libromodel.h"
#include "fingreso.h"
#include "QMessageBox"

namespace Ui {
class flibros;
}

class flibros : public QDialog
{
    Q_OBJECT
    
public:
    explicit flibros(QWidget *parent = 0);
    ~flibros();
    
private slots:
    void on_btnNuevo_clicked();

    void on_tvwLibros_clicked(const QModelIndex &index);

private:
    Ui::flibros *ui;
    LibroModel *libros;
    int id;
    void cargarLibros();
};

#endif // FLIBROS_H
