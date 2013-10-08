#include "fusersadminpage.h"
#include "ui_fusersadminpage.h"

FUsersAdminPage::FUsersAdminPage(QWidget *parent) :
    QRecordWidgetMapper(parent),
    ui(new Ui::FUsersAdminPage)
{
    ui->setupUi(this);

	usuarioModel = new UsuarioModel(this);
	connect(usuarioModel,SIGNAL(modelReset()),this,SLOT(principalModel_updated()));

	usuarioModel->configureQuery()->allAttributes();
	usuarioModel->configureQuery()->addOrderBy("usuario");
	usuarioModel->select();
	ui->lvwUsuarios->setModel(usuarioModel);
	ui->lvwUsuarios->setModelColumn(6);

	rolModel = new RolModel(this);
	empresaModel = new EmpresaModel(this);
	cargoModel = new UsuarioCargoModel(this);

	rolModel->configureQuery()->allAttributes();
	rolModel->configureQuery()->addOrderBy("Rol");
	ui->cbxRol->setModel(rolModel);
	ui->cbxRol->setModelColumn(1);

	empresaModel->configureQuery()->allAttributes();
	empresaModel->configureQuery()->addOrderBy("Nombre");
	ui->cbxEmpresa->setModel(empresaModel);
	ui->cbxEmpresa->setModelColumn(1);

	cargoModel->configureQuery()->allAttributes();
	cargoModel->configureQuery()->addOrderBy("Cargo");
	ui->cbxCargo->setModel(cargoModel);
	ui->cbxCargo->setModelColumn(1);

	ui->btnModificarClave->setVisible(false);

	insertandoNuevo=false;

	//mapper

	setModel(usuarioModel);

	addMapper( "Usuario", ui->ledUsuario );
	addMapper( "Empresa_idEmpresa",ui->cbxEmpresa );
	addMapper( "Rol_idRol",ui->cbxRol );
	addMapper( "UsuarioCargo_idUsuarioCargo",ui->cbxCargo );
	addMapper( "Nombres", ui->ledNombres );
	addMapper( "Apellidos", ui->ledApellidos );
}

FUsersAdminPage::~FUsersAdminPage()
{
    delete ui;
}

QWidget *FUsersAdminPage::widget()
{
    return this;
}

bool FUsersAdminPage::apply()
{
    return true;
}

void FUsersAdminPage::updatePage()
{
	rolModel->select();
	cargoModel->select();
	empresaModel->select();
}

void FUsersAdminPage::on_btnNuevo_clicked()
{
	newRecord();
	insertandoNuevo=true;
	ui->btnNuevo->setEnabled(false);
	ui->grbxUsuarioDatos->setEnabled(true);
	ui->ledUsuario->setEnabled(true);
	ui->btnModificarClave->setVisible(false);
}

QSqlDatabase FUsersAdminPage::getRootDBConecction(bool &ok)
{
	if ( MaquinaModel::currentDBUser() != "root" )
	{
		QSqlDatabase mie = QSqlDatabase::database();
		QString rootPwd = QInputDialog::getText(this,"Clave de root",
												"Ingrese la clave de root de la base de datos",
												QLineEdit::Password);

		QSqlDatabase rootDB = QSqlDatabase::addDatabase("QMYSQL");
		rootDB.setHostName( mie.hostName() );
		rootDB.setDatabaseName( mie.databaseName() );
		rootDB.setPort( mie.port() );
		rootDB.setUserName( "root" );
		rootDB.setPassword( rootPwd );

		if ( rootDB.open() )
		{
			ok=true;
			return rootDB;
		}
		else
		{
			QMessageBox::critical(this,"Error",
								  "No se pudo conectar a la base de datos.\nLa clave de root es incorrecta");
			ok=false;
			return QSqlDatabase();
		}
	}
	else
	{
		ok=true;
		return QSqlDatabase::database();
	}
}

void FUsersAdminPage::on_btnGuardar_clicked()
{
	if ( insertandoNuevo )
	{
		//insertando un nuevo usuario

		//clave del nuevo usuario
		QString userPwd1 = QInputDialog::getText(this,"Clave del nuevo usuario",
												 "Ingrese la clave del nuevo usuario",
												 QLineEdit::Password);
		QString userPwd2 = QInputDialog::getText(this,"Clave del nuevo usuario",
												 "Ingrese nuevamente la clave del nuevo usuario",
												 QLineEdit::Password);
		if ( userPwd1 != userPwd2 )
		{
			QMessageBox::critical( this,"Error","Las claves del nuevo usuario no coinciden." );
			return;
		}

		bool ok;
		QSqlDatabase database = getRootDBConecction(ok);
		if ( !ok )
			return;
		TSqlError error;

		//ya somos root iniciamos la transaccion
		database.transaction();

		//creando el usuario de la base de datos
		QSqlQuery query( database );
        query.prepare(" CREATE USER '"+ QString(CUSTOMER)+"_"+ui->ledUsuario->text() +"'@'%' IDENTIFIED BY  '"+userPwd1+"'");
		query.exec();
		error = query.lastError();
		if ( error.isError() )
		{
			QMessageBox::critical(this,"Error","No se pudo crear el nuevo usuario");
			database.rollback();
			return;
		}

        query.prepare("GRANT SELECT,INSERT,UPDATE,DELETE,FILE ON * . * TO  '"+QString(CUSTOMER)+"_"+ui->ledUsuario->text()+
					  "'@'%' IDENTIFIED BY  '"+userPwd1+
					  "' WITH MAX_QUERIES_PER_HOUR 0 MAX_CONNECTIONS_PER_HOUR 0 MAX_UPDATES_PER_HOUR 0 MAX_USER_CONNECTIONS 0");
		query.exec();
		error = query.lastError();
		if ( error.isError() )
		{
			QMessageBox::critical(this,"Error","No se pudo crear el nuevo usuario");
			database.rollback();
			return;
		}

        query.prepare(" CREATE USER '"+ QString(CUSTOMER)+"_"+ui->ledUsuario->text() +"'@'localhost' IDENTIFIED BY  '"+userPwd1+"'");
		query.exec();
		error = query.lastError();
		if ( error.isError() )
		{
			QMessageBox::critical(this,"Error","No se pudo crear el nuevo usuario");
			database.rollback();
			return;
		}

        query.prepare("GRANT SELECT,INSERT,UPDATE,DELETE,FILE ON * . * TO  '"+QString(CUSTOMER)+"_"+ui->ledUsuario->text()+
					  "'@'localhost' IDENTIFIED BY  '"+userPwd1+
					  "' WITH MAX_QUERIES_PER_HOUR 0 MAX_CONNECTIONS_PER_HOUR 0 MAX_UPDATES_PER_HOUR 0 MAX_USER_CONNECTIONS 0");
		query.exec();
		error = query.lastError();
		if ( error.isError() )
		{
			QMessageBox::critical(this,"Error","No se pudo crear el nuevo usuario");
			database.rollback();
			return;
		}

		//Guardando los datos de usuario
		error = submit();
		if ( error.isError() )
		{
			QMessageBox::critical(this,"Error","No se pudo crear el nuevo usuario");
			database.rollback();
			return;
		}

		insertandoNuevo=false;
		database.commit();
		toLast();
	}
	else
	{
		//modificando el usuario
		TSqlError error;
		error = submitAll();
		if ( error.isError() )
		{
			QMessageBox::critical(this,"Error","No se pudo crear el nuevo usuario");
			return;
		}
	}
	ui->grbxUsuarioDatos->setEnabled(false);
}

void FUsersAdminPage::on_btnCancelar_clicked()
{
	if ( insertandoNuevo )
		revert();
	else
		revertAll();
	ui->grbxUsuarioDatos->setEnabled(false);
	ui->btnModificarClave->setVisible(false);
}

void FUsersAdminPage::on_lvwUsuarios_clicked(const QModelIndex &index)
{
	ui->grbxUsuarioDatos->setEnabled(true);
	ui->btnModificarClave->setVisible(true);
	ui->ledUsuario->setEnabled(false);
	ui->btnNuevo->setEnabled(true);
	if ( insertandoNuevo )
	{
		insertandoNuevo=false;
		cancelNewRecord();
	}
	toRecord( index.row() );
    usuarioSeleccionadoRecord = ui->lvwUsuarios->getSelectedRecords<UsuarioRecord*>().at(0);
	ui->btnEliminar->setEnabled(true);
}

void FUsersAdminPage::on_btnModificarClave_clicked()
{
	rolModel->select();

	//clave del nuevo usuario
	QString userPwd1 = QInputDialog::getText(this,"Clave de usuario",
											 "Ingrese la nueva clave de usuario",
											 QLineEdit::Password);
	QString userPwd2 = QInputDialog::getText(this,"Clave del nuevo usuario",
											 "Ingrese nuevamente la nueva clave de usuario",
											 QLineEdit::Password);
	if ( userPwd1 != userPwd2 )
	{
		QMessageBox::critical( this,"Error","Las claves de usuario no coinciden." );
		return;
	}

	bool ok;
	QSqlDatabase database = getRootDBConecction(ok);
	if ( !ok )
		return;
	TSqlError error;

	database.transaction();

	QSqlQuery query(database);
    query.prepare( "SET PASSWORD FOR  '"+QString(CUSTOMER)+"_"+ui->ledUsuario->text()+"'@'localhost' = PASSWORD(  '"+userPwd1+"' )" );
	query.exec();
	error = query.lastError();
	if ( error.isError() )
	{
		QMessageBox::critical(this,"Error",tr("No se pudo modificar la contraseña del usuario"));
		database.rollback();
		return;
	}

    query.prepare( "SET PASSWORD FOR  '"+QString(CUSTOMER)+"_"+ui->ledUsuario->text()+"'@'%' = PASSWORD(  '"+userPwd1+"' )" );
	query.exec();
	error = query.lastError();
	if ( error.isError() )
	{
		QMessageBox::critical(this,"Error",tr("No se pudo modificar la contraseña del usuario"));
		database.rollback();
		return;
	}

	database.commit();
}

void FUsersAdminPage::on_btnEliminar_clicked()
{
	if ( QMessageBox::question(this,"Eliminar usuario",tr("¿Realmente desea eliminar el usuario?"),
							   QMessageBox::Yes,QMessageBox::No) != QMessageBox::Yes )
		return;

	bool ok;
	QSqlDatabase database = getRootDBConecction(ok);
	if ( !ok )
		return;
	TSqlError error;

	database.transaction();

	QSqlQuery query(database);
    query.prepare( "DROP USER '"+QString(CUSTOMER)+"_"+usuarioSeleccionadoRecord->Usuario()+"'@'%'" );
	query.exec();
	error = query.lastError();
	if ( error.isError() )
	{
		QMessageBox::critical(this,"Error",tr("No se pudo eliminar el usuario"));
		database.rollback();
		return;
	}

    query.prepare( "DROP USER '"+QString(CUSTOMER)+"_"+usuarioSeleccionadoRecord->Usuario()+"'@'localhost'" );
	query.exec();
	error = query.lastError();
	if ( error.isError() )
	{
		QMessageBox::critical(this,"Error",tr("No se pudo eliminar el usuario"));
		database.rollback();
		return;
	}

	query.prepare( "delete from Usuario where idUsuario="+QString::number( usuarioSeleccionadoRecord->idUsuario() ) );
	query.exec();
	error = query.lastError();
	if ( error.isError() )
	{
		QMessageBox::critical(this,"Error",tr("No se pudo eliminar el usuario"));
		database.rollback();
		return;
	}

	usuarioModel->select();
	cleanWidgets();
	database.commit();

	ui->grbxUsuarioDatos->setEnabled(false);
}

void FUsersAdminPage::principalModel_updated()
{
	ui->btnEliminar->setEnabled(false);
}
