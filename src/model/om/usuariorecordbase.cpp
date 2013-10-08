#include "usuariorecordbase.h"

/*! Contructor.
  El padre del registro puede ser nulo u otro registro.

  Un objeto que tiene atributos que representan llaves foráneas será el padre de los objetos que regresentan a las tablas foráneas.

  \param qparent Padre del objeto.
  \param rparent Padre del registro.

  \b Ejemplo:

  Tabla: Lugar\n
  Llave primaria: idLugar\n

  Tabla: Persona\n
  Llave primaria: idPersona\n
  Llave foranea: Lugar_idLugar\n

  Persona padre de Lugar.

  Esta relación de padres e hijos se utiliza entre la clase instanciada y sus miembros heredados de Record que representan sus llaves foraneas.
*/
UsuarioRecordBase::UsuarioRecordBase(QObject *qparent,
							 RecordBase *rparent,
							 QSqlDatabase db):
RecordSimpleBase(qparent,rparent,db)
{
	TABLENAME="Usuario";
	
	ISBACKUPRECORUSELOCALATT=false;
	BACKUPRECORD = new UsuarioRecordBase(false,qparent,rparent,db);

	init();
	initValues();
}

//!Constructor copia.
UsuarioRecordBase::UsuarioRecordBase(const UsuarioRecordBase &other):
RecordSimpleBase(other.QPARENT,other.PARENT,other.DB)
{
	init();

	foreach ( QString att, USUARIOATTRIBUTESLIST )
		setProperty( att.toLocal8Bit(),
					other.property( att.toLocal8Bit() ));

	if ( other.TABLENAME == "Usuario" )
	{
		TABLENAME = other.TABLENAME;
		
		ISBACKUPRECORUSELOCALATT = false; //este es el papa mayor, aqui si va
		BACKUPRECORD = new UsuarioRecordBase(false,other.QPARENT,other.PARENT,other.DB);
	}
}

UsuarioRecordBase::UsuarioRecordBase(bool conf,
							   QObject *qparent,
							   RecordBase *rparent,
							   QSqlDatabase db):
	RecordSimpleBase(qparent,rparent,db) //todos los hijos van asi
{
	if ( ! conf )
	{
		//es false, Entonces es la copia
		TABLENAME="Usuario";
		ISBACKUPRECORUSELOCALATT = true;
		BACKUPRECORD=NULL;
	}

	

	init();
	initValues();
}

UsuarioRecordBase::~UsuarioRecordBase()
{}

//! Inicializa los registros foráneos.
void UsuarioRecordBase::init()
{
	REMPRESA_ = NULL;
RROL_ = NULL;
RUSUARIOCARGO_ = NULL;


	lstTables.prepend("Usuario");

	USUARIOATTRIBUTESLIST << "idUsuario"
<< "Empresa_idEmpresa"
<< "Rol_idRol"
<< "UsuarioCargo_idUsuarioCargo"
<< "Nombres"
<< "Apellidos"
<< "Usuario"
<< "FechaHora"
<< "Turno";
	USUARIOPKATTRIBUTESLIST << "idUsuario";
	USUARIODATETIMEATTRIBUTESLIST << "FechaHora";
	USUARIOPKAUTOINCREMENTATTRIBUTE = "idUsuario";
}

//! Inicializa los atributos con tipos primitivos
void UsuarioRecordBase::initValues()
{
	IDUSUARIO=0;
EMPRESA_IDEMPRESA=0;
ROL_IDROL=0;
USUARIOCARGO_IDUSUARIOCARGO=0;

}

void UsuarioRecordBase::setRecordEnabledBackup(bool enabled)
{
	enabledRecordBackup=enabled;
	
	if ( REMPRESA_ != NULL )
		REMPRESA_->setRecordEnabledBackup(enabled);
if ( RROL_ != NULL )
		RROL_->setRecordEnabledBackup(enabled);
if ( RUSUARIOCARGO_ != NULL )
		RUSUARIOCARGO_->setRecordEnabledBackup(enabled);

}

RecordBase *UsuarioRecordBase::getBackUpRecord() { return BACKUPRECORD; }

//set nuevo valor para un campo

void UsuarioRecordBase::setIdUsuario(int idUsuario)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		IDUSUARIO=idUsuario;
	else
	{
		addAttributeInsertUpdate("idUsuario");
		getBackUpRecord()->setProperty( "idUsuario",idUsuario );
	}
}

void UsuarioRecordBase::setEmpresa_idEmpresa(int Empresa_idEmpresa)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		EMPRESA_IDEMPRESA=Empresa_idEmpresa;
	else
	{
		addAttributeInsertUpdate("Empresa_idEmpresa");
		getBackUpRecord()->setProperty( "Empresa_idEmpresa",Empresa_idEmpresa );
	}
}

void UsuarioRecordBase::setRol_idRol(int Rol_idRol)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		ROL_IDROL=Rol_idRol;
	else
	{
		addAttributeInsertUpdate("Rol_idRol");
		getBackUpRecord()->setProperty( "Rol_idRol",Rol_idRol );
	}
}

void UsuarioRecordBase::setUsuarioCargo_idUsuarioCargo(int UsuarioCargo_idUsuarioCargo)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		USUARIOCARGO_IDUSUARIOCARGO=UsuarioCargo_idUsuarioCargo;
	else
	{
		addAttributeInsertUpdate("UsuarioCargo_idUsuarioCargo");
		getBackUpRecord()->setProperty( "UsuarioCargo_idUsuarioCargo",UsuarioCargo_idUsuarioCargo );
	}
}

void UsuarioRecordBase::setNombres(QString Nombres)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		NOMBRES=Nombres;
	else
	{
		addAttributeInsertUpdate("Nombres");
		getBackUpRecord()->setProperty( "Nombres",Nombres );
	}
}

void UsuarioRecordBase::setApellidos(QString Apellidos)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		APELLIDOS=Apellidos;
	else
	{
		addAttributeInsertUpdate("Apellidos");
		getBackUpRecord()->setProperty( "Apellidos",Apellidos );
	}
}

void UsuarioRecordBase::setUsuario(QString Usuario)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		USUARIO=Usuario;
	else
	{
		addAttributeInsertUpdate("Usuario");
		getBackUpRecord()->setProperty( "Usuario",Usuario );
	}
}

void UsuarioRecordBase::setFechaHora(QDateTime FechaHora)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		FECHAHORA=FechaHora;
	else
	{
		addAttributeInsertUpdate("FechaHora");
		getBackUpRecord()->setProperty( "FechaHora",FechaHora );
	}
}

void UsuarioRecordBase::setTurno(QString Turno)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		TURNO=Turno;
	else
	{
		addAttributeInsertUpdate("Turno");
		getBackUpRecord()->setProperty( "Turno",Turno );
	}
}



void UsuarioRecordBase::setREmpresa_(EmpresaRecordBase* r)
{
	if( REMPRESA_ != NULL )
		delete REMPRESA_;
	REMPRESA_=r;
	setEmpresa_idEmpresa( r->idEmpresa() );
}

void UsuarioRecordBase::setPREmpresa_(RecordBase *pr)
{
	setREmpresa_((EmpresaRecordBase*)pr);
}

void UsuarioRecordBase::setRRol_(RolRecordBase* r)
{
	if( RROL_ != NULL )
		delete RROL_;
	RROL_=r;
	setRol_idRol( r->idRol() );
}

void UsuarioRecordBase::setPRRol_(RecordBase *pr)
{
	setRRol_((RolRecordBase*)pr);
}

void UsuarioRecordBase::setRUsuarioCargo_(UsuarioCargoRecordBase* r)
{
	if( RUSUARIOCARGO_ != NULL )
		delete RUSUARIOCARGO_;
	RUSUARIOCARGO_=r;
	setUsuarioCargo_idUsuarioCargo( r->idUsuarioCargo() );
}

void UsuarioRecordBase::setPRUsuarioCargo_(RecordBase *pr)
{
	setRUsuarioCargo_((UsuarioCargoRecordBase*)pr);
}



//get de los campos, si hay valor nuevo ese regresa, si no el normal

int UsuarioRecordBase::idUsuario()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("idUsuario"))
		return IDUSUARIO;
	else
		return getBackUpRecord()->property( "idUsuario" ).toInt();
}

int UsuarioRecordBase::Empresa_idEmpresa()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("Empresa_idEmpresa"))
		return EMPRESA_IDEMPRESA;
	else
		return getBackUpRecord()->property( "Empresa_idEmpresa" ).toInt();
}

int UsuarioRecordBase::Rol_idRol()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("Rol_idRol"))
		return ROL_IDROL;
	else
		return getBackUpRecord()->property( "Rol_idRol" ).toInt();
}

int UsuarioRecordBase::UsuarioCargo_idUsuarioCargo()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("UsuarioCargo_idUsuarioCargo"))
		return USUARIOCARGO_IDUSUARIOCARGO;
	else
		return getBackUpRecord()->property( "UsuarioCargo_idUsuarioCargo" ).toInt();
}

QString UsuarioRecordBase::Nombres()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("Nombres"))
		return NOMBRES;
	else
		return getBackUpRecord()->property( "Nombres" ).toString();
}

QString UsuarioRecordBase::Apellidos()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("Apellidos"))
		return APELLIDOS;
	else
		return getBackUpRecord()->property( "Apellidos" ).toString();
}

QString UsuarioRecordBase::Usuario()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("Usuario"))
		return USUARIO;
	else
		return getBackUpRecord()->property( "Usuario" ).toString();
}

QDateTime UsuarioRecordBase::FechaHora()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("FechaHora"))
		return FECHAHORA;
	else
		return getBackUpRecord()->property( "FechaHora" ).toDateTime();
}

QString UsuarioRecordBase::Turno()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("Turno"))
		return TURNO;
	else
		return getBackUpRecord()->property( "Turno" ).toString();
}



EmpresaRecordBase *UsuarioRecordBase::REmpresa_()
{
	if ( REMPRESA_ == NULL )
	{
		REMPRESA_=new EmpresaRecordBase(this,this,DB);
		REMPRESA_->setRecordEnabledBackup(enabledRecordBackup);

		connect( REMPRESA_,SIGNAL(hasValuesWithOutSave(bool,RecordBase*)),
			this, SIGNAL(hasValuesWithOutSave(bool,RecordBase*)));
	}

	return REMPRESA_;
}

RolRecordBase *UsuarioRecordBase::RRol_()
{
	if ( RROL_ == NULL )
	{
		RROL_=new RolRecordBase(this,this,DB);
		RROL_->setRecordEnabledBackup(enabledRecordBackup);

		connect( RROL_,SIGNAL(hasValuesWithOutSave(bool,RecordBase*)),
			this, SIGNAL(hasValuesWithOutSave(bool,RecordBase*)));
	}

	return RROL_;
}

UsuarioCargoRecordBase *UsuarioRecordBase::RUsuarioCargo_()
{
	if ( RUSUARIOCARGO_ == NULL )
	{
		RUSUARIOCARGO_=new UsuarioCargoRecordBase(this,this,DB);
		RUSUARIOCARGO_->setRecordEnabledBackup(enabledRecordBackup);

		connect( RUSUARIOCARGO_,SIGNAL(hasValuesWithOutSave(bool,RecordBase*)),
			this, SIGNAL(hasValuesWithOutSave(bool,RecordBase*)));
	}

	return RUSUARIOCARGO_;
}



//!Limpia los atributos
void UsuarioRecordBase::clear()
{
	

	//limpiando no primitivos
	NOMBRES.clear();
APELLIDOS.clear();
USUARIO.clear();
FECHAHORA.setDate ( QDate(0,0,0) );
FECHAHORA.setTime ( QTime(0,0,0) );
TURNO.clear();


	//limpiando foraneas
	if ( REMPRESA_ != NULL )
	REMPRESA_->clear();
if ( RROL_ != NULL )
	RROL_->clear();
if ( RUSUARIOCARGO_ != NULL )
	RUSUARIOCARGO_->clear();

}

void UsuarioRecordBase::revert()
{
	RecordBase::revert();

	if ( REMPRESA_ != NULL )
	REMPRESA_->revert();
if ( RROL_ != NULL )
	RROL_->revert();
if ( RUSUARIOCARGO_ != NULL )
	RUSUARIOCARGO_->revert();

}

QStringList UsuarioRecordBase::UsuarioAttributesList() { return USUARIOATTRIBUTESLIST; }

QStringList UsuarioRecordBase::UsuarioPKAttributesList() { return USUARIOPKATTRIBUTESLIST; }

QString UsuarioRecordBase::UsuarioPKAutoIncrementAttribute() { return USUARIOPKAUTOINCREMENTATTRIBUTE; }

QStringList UsuarioRecordBase::UsuarioDateTimeAttributesList() { return USUARIODATETIMEATTRIBUTESLIST; }

QStringList UsuarioRecordBase::getAttributesList()
{
return USUARIOATTRIBUTESLIST;
}

QStringList UsuarioRecordBase::getPKAttributesList()
{
return USUARIOPKATTRIBUTESLIST;
}

QStringList UsuarioRecordBase::getPKAutoIncrementAttributesList()
{
return QStringList() << USUARIOPKAUTOINCREMENTATTRIBUTE;
}

QStringList UsuarioRecordBase::getDateTimeAttributesList()
{
return USUARIODATETIMEATTRIBUTESLIST;
}



QStringList UsuarioRecordBase::EmpresaFAttributes()
{
	return QStringList() << "Empresa_idEmpresa";
}

QStringList UsuarioRecordBase::RolFAttributes()
{
	return QStringList() << "Rol_idRol";
}

QStringList UsuarioRecordBase::UsuarioCargoFAttributes()
{
	return QStringList() << "UsuarioCargo_idUsuarioCargo";
}



RecordBase *UsuarioRecordBase::getLastChildDefaultRecord() { return this; }





QString UsuarioRecordBase::idUsuarioProperty() { return "idUsuario"; }

QString UsuarioRecordBase::Empresa_idEmpresaProperty() { return "Empresa_idEmpresa"; }

QString UsuarioRecordBase::Rol_idRolProperty() { return "Rol_idRol"; }

QString UsuarioRecordBase::UsuarioCargo_idUsuarioCargoProperty() { return "UsuarioCargo_idUsuarioCargo"; }

QString UsuarioRecordBase::NombresProperty() { return "Nombres"; }

QString UsuarioRecordBase::ApellidosProperty() { return "Apellidos"; }

QString UsuarioRecordBase::UsuarioProperty() { return "Usuario"; }

QString UsuarioRecordBase::FechaHoraProperty() { return "FechaHora"; }

QString UsuarioRecordBase::TurnoProperty() { return "Turno"; }



/*! Esta función reimplementa operator=().

  Asigna \a record a este UsuarioRecordBase.
*/
UsuarioRecordBase& UsuarioRecordBase::operator=(const UsuarioRecordBase& record)
{
	ISBACKUPRECORUSELOCALATT=true; //
	foreach( QString att, getAttributesList() )
		setProperty( att.toLocal8Bit(),
					record.property( att.toLocal8Bit() ));
	lstAttInsertUpdate.clear();
	emit hasValuesWithOutSave(false,this);
	ISBACKUPRECORUSELOCALATT=false;
	return *this;
}

