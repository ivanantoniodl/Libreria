#include "faboutapp.h"
#include "ui_faboutapp.h"

FAboutApp::FAboutApp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FAboutApp)
{
    ui->setupUi(this);
}

FAboutApp::~FAboutApp()
{
    delete ui;
}
