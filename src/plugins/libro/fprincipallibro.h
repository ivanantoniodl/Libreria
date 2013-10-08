#ifndef FPRINCIPALLIBRO_H
#define FPRINCIPALLIBRO_H

#include <QDialog>

namespace Ui {
class fprincipallibro;
}

class fprincipallibro : public QDialog
{
    Q_OBJECT
    
public:
    explicit fprincipallibro(QWidget *parent = 0);
    ~fprincipallibro();
    
private:
    Ui::fprincipallibro *ui;
};

#endif // FPRINCIPALLIBRO_H
