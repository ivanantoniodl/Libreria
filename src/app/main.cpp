#include <QtGui/QApplication>
#include "mainwindow.h"


#include "empresarecord.h"
#include "grupopermisorecord.h"
#include "lugarrecord.h"
#include "lugartiporecord.h"
#include "maquinarecord.h"
#include "permisorecord.h"
#include "rolrecord.h"
#include "rolpermisorecord.h"
#include "usuariorecord.h"
#include "usuariocargorecord.h"

#include "fconexion.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	QCoreApplication::setOrganizationName("TipSA");
	QCoreApplication::setOrganizationDomain("http://www.solucionestip.com/");
    QCoreApplication::setApplicationName("Libreria");

    qRegisterMetaType<RecordBase*>();
    qRegisterMetaType<RecordSimpleBase*>();
    qRegisterMetaType<RecordInheritsBase*>();
    qRegisterMetaType<UInt>("UInt");
    qRegisterMetaType<UInt>("LongLong");
    qRegisterMetaType<UInt>("ULongLong");
    qRegisterMetaType<GrupoPermisoRecordBase*>();
    qRegisterMetaType<LugarRecordBase*>();
    qRegisterMetaType<LugarTipoRecordBase*>();
    qRegisterMetaType<MaquinaRecordBase*>();
    qRegisterMetaType<PermisoRecordBase*>();
    qRegisterMetaType<RolRecordBase*>();
    qRegisterMetaType<RolPermisoRecordBase*>();
    qRegisterMetaType<UsuarioRecordBase*>();
    qRegisterMetaType<UsuarioCargoRecordBase*>();

    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

	QTranslator qtTranslator;
	qtTranslator.load("qt_" + QLocale::system().name(),
					  QLibraryInfo::location(QLibraryInfo::TranslationsPath));
	a.installTranslator(&qtTranslator);

	FConexion *flogin = new FConexion;
	int contador=0;
	int MAXNUMLOGIN=3;
	while ((flogin->exec() == QDialog::Accepted) && (contador < MAXNUMLOGIN))
	{
		QSettings settings;
		settings.beginGroup("DB Settings");
		QString servidor = settings.value("Host").toString();
		QString BD = settings.value("BD").toString();
		int puerto = settings.value("Puerto").toInt();
		QString Opciones;
		if (settings.value("SSL").toBool())
			Opciones.append("CLIENT_SSL=1");
		if (settings.value("Compresion").toBool())
		{
			if (!Opciones.isEmpty())
				Opciones.append(";");
			Opciones.append("CLIENT_COMPRESS=1");
		}
		if (!Opciones.isEmpty())
			Opciones.append(";");
		Opciones.append("CLIENT_NO_SCHEMA=1");
		settings.endGroup();

		// inicio de la conexion

		QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
		db.setHostName(servidor);
		db.setDatabaseName(BD);
        if ( flogin->getUsuario() != "root" )
            db.setUserName( QString(CUSTOMER)+"_"+flogin->getUsuario() );
        else
            db.setUserName( flogin->getUsuario() );
		db.setPassword(flogin->getPass());
		if (! db.open() )
		{
			//qDebug()<<conexion->lastError().text();
			//QMessageBox::critical(0,"Error",conexion->lastError().text());
			QMessageBox::critical(0,"Error","No se pudo conectar");
			contador++;
			continue;
		}

		delete flogin;
		MainWindow w;
		w.show();
		return a.exec();
	}
	if (contador >= 3)
		QMessageBox::critical(0,"Error de Seguridad","Ha intentado ingresar mas de "
							  +QString::number(MAXNUMLOGIN)+" veces sin éxito");
}
