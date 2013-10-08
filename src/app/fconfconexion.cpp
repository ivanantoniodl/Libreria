#include "fconfconexion.h"
#include "ui_fconfconexion.h"

#include <QMessageBox>
#include <QSettings>
#include <QCheckBox>
#include <QFileDialog>
#include <QFile>

fConfConexion::fConfConexion(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::fConfConexion)
{
    m_ui->setupUi(this);
    QSettings settings;
    guardarPathScript = false;
    settings.beginGroup("DB Settings");
    m_ui->ledServidor->setText(settings.value("Host","localhost").toString());
    m_ui->ledBaseDatos->setText(settings.value("BD","BDPoliclinica").toString());
    m_ui->ledPuerto->setText(settings.value("Puerto","3306").toString());
    m_ui->cbxSSL->setChecked(settings.value("SSL").toBool());
    m_ui->cbxCompresion->setChecked(settings.value("Compresion").toBool());
    m_ui->cbxTipoServidor->setCurrentIndex(settings.value("ServerType").toInt());
    m_ui->ledProxyPath->setText(settings.value("ProxyScript").toString());
    settings.endGroup();
}

fConfConexion::~fConfConexion()
{
    delete m_ui;
}

void fConfConexion::changeEvent(QEvent *e)
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

void fConfConexion::on_btnAceptar_clicked()
{
	QSettings settings;
	settings.beginGroup("DB Settings");
	settings.setValue("Host",m_ui->ledServidor->text());
	settings.setValue("BD",m_ui->ledBaseDatos->text());
	settings.setValue("Puerto",m_ui->ledPuerto->text());
	settings.setValue("SSL", m_ui->cbxSSL->isChecked());
	settings.setValue("Compresion", m_ui->cbxCompresion->isChecked());
    settings.setValue("ServerType",m_ui->cbxTipoServidor->currentIndex());
    if (guardarPathScript)
        settings.setValue("ProxyScript", m_ui->ledProxyPath->text());
	settings.endGroup();
}

void fConfConexion::on_cbxTipoServidor_currentIndexChanged(int index)
{
    if (index == 0)
        m_ui->ledPuerto->setText("3306");
    else
        m_ui->ledPuerto->setText("4040");
}

void fConfConexion::on_btnExaminar_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,
         tr("Abrir Script"), "/home", tr("Bash Script (*.sh)"));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(0,"Error","El archivo no existe");
        guardarPathScript = false;
    }
    else
    {
        m_ui->ledProxyPath->setText(fileName);
        guardarPathScript = true;
    }
    file.close();
}
