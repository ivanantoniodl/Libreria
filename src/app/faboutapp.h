#ifndef FABOUTAPP_H
#define FABOUTAPP_H

#include <QDialog>

namespace Ui {
    class FAboutApp;
}

class FAboutApp : public QDialog
{
    Q_OBJECT

public:
    explicit FAboutApp(QWidget *parent = 0);
    ~FAboutApp();

private:
    Ui::FAboutApp *ui;
};

#endif // FABOUTAPP_H
