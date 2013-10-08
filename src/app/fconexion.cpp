#include "fconexion.h"
#include "ui_fconexion.h"
#include "fconfconexion.h"
#include <QSettings>

FConexion::FConexion(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::FConexion)
{
    m_ui->setupUi(this);

    QSettings settings;
    settings.beginGroup("DB");
    m_ui->ledUsuario->setText( settings.value("user").toString() );
	//m_ui->ledClave->setText( settings.value("pass").toString() );
    settings.endGroup();

    if(m_ui->ledUsuario->text().isEmpty())
        m_ui->ledUsuario->setFocus();
    else
        m_ui->ledClave->setFocus();
}

FConexion::~FConexion()
{
    delete m_ui;
}

void FConexion::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void FConexion::on_btnConfigurar_clicked()
{
    fConfConexion *confWind = new fConfConexion(this);
    confWind->exec();
    delete confWind;
}

void FConexion::on_pushButton_clicked()
{
    qApp->exit(0);
}

void FConexion::on_btnConectar_clicked()
{
    setSettings();
}

void FConexion::setSettings()
{
    QSettings settings;
    settings.beginGroup("DB");
    settings.setValue("user",m_ui->ledUsuario->text());
	//settings.setValue("pass",m_ui->ledClave->text());
    settings.endGroup();
}

QString FConexion::getUsuario()
{
    return m_ui->ledUsuario->text();
}

QString FConexion::getPass()
{
    return m_ui->ledClave->text();
}
