#include "rolpermisorecordbase.h"

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
RolPermisoRecordBase::RolPermisoRecordBase(QObject *qparent,
							 RecordBase *rparent,
							 QSqlDatabase db):
RecordSimpleBase(qparent,rparent,db)
{
	TABLENAME="RolPermiso";
	
	ISBACKUPRECORUSELOCALATT=false;
	BACKUPRECORD = new RolPermisoRecordBase(false,qparent,rparent,db);

	init();
	initValues();
}

//!Constructor copia.
RolPermisoRecordBase::RolPermisoRecordBase(const RolPermisoRecordBase &other):
RecordSimpleBase(other.QPARENT,other.PARENT,other.DB)
{
	init();

	foreach ( QString att, ROLPERMISOATTRIBUTESLIST )
		setProperty( att.toLocal8Bit(),
					other.property( att.toLocal8Bit() ));

	if ( other.TABLENAME == "RolPermiso" )
	{
		TABLENAME = other.TABLENAME;
		
		ISBACKUPRECORUSELOCALATT = false; //este es el papa mayor, aqui si va
		BACKUPRECORD = new RolPermisoRecordBase(false,other.QPARENT,other.PARENT,other.DB);
	}
}

RolPermisoRecordBase::RolPermisoRecordBase(bool conf,
							   QObject *qparent,
							   RecordBase *rparent,
							   QSqlDatabase db):
	RecordSimpleBase(qparent,rparent,db) //todos los hijos van asi
{
	if ( ! conf )
	{
		//es false, Entonces es la copia
		TABLENAME="RolPermiso";
		ISBACKUPRECORUSELOCALATT = true;
		BACKUPRECORD=NULL;
	}

	

	init();
	initValues();
}

RolPermisoRecordBase::~RolPermisoRecordBase()
{}

//! Inicializa los registros foráneos.
void RolPermisoRecordBase::init()
{
	RPERMISO_ = NULL;
RROL_ = NULL;


	lstTables.prepend("RolPermiso");

	ROLPERMISOATTRIBUTESLIST << "idRolPermiso"
<< "Permiso_idPermiso"
<< "Rol_idRol"
<< "Permiso";
	ROLPERMISOPKATTRIBUTESLIST << "idRolPermiso";
	ROLPERMISODATETIMEATTRIBUTESLIST  = QStringList();;
	ROLPERMISOPKAUTOINCREMENTATTRIBUTE = "idRolPermiso";
}

//! Inicializa los atributos con tipos primitivos
void RolPermisoRecordBase::initValues()
{
	IDROLPERMISO=0;
PERMISO_IDPERMISO=0;
ROL_IDROL=0;
PERMISO=0;

}

void RolPermisoRecordBase::setRecordEnabledBackup(bool enabled)
{
	enabledRecordBackup=enabled;
	
	if ( RPERMISO_ != NULL )
		RPERMISO_->setRecordEnabledBackup(enabled);
if ( RROL_ != NULL )
		RROL_->setRecordEnabledBackup(enabled);

}

RecordBase *RolPermisoRecordBase::getBackUpRecord() { return BACKUPRECORD; }

//set nuevo valor para un campo

void RolPermisoRecordBase::setIdRolPermiso(int idRolPermiso)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		IDROLPERMISO=idRolPermiso;
	else
	{
		addAttributeInsertUpdate("idRolPermiso");
		getBackUpRecord()->setProperty( "idRolPermiso",idRolPermiso );
	}
}

void RolPermisoRecordBase::setPermiso_idPermiso(int Permiso_idPermiso)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		PERMISO_IDPERMISO=Permiso_idPermiso;
	else
	{
		addAttributeInsertUpdate("Permiso_idPermiso");
		getBackUpRecord()->setProperty( "Permiso_idPermiso",Permiso_idPermiso );
	}
}

void RolPermisoRecordBase::setRol_idRol(int Rol_idRol)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		ROL_IDROL=Rol_idRol;
	else
	{
		addAttributeInsertUpdate("Rol_idRol");
		getBackUpRecord()->setProperty( "Rol_idRol",Rol_idRol );
	}
}

void RolPermisoRecordBase::setPermiso(int Permiso)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		PERMISO=Permiso;
	else
	{
		addAttributeInsertUpdate("Permiso");
		getBackUpRecord()->setProperty( "Permiso",Permiso );
	}
}



void RolPermisoRecordBase::setRPermiso_(PermisoRecordBase* r)
{
	if( RPERMISO_ != NULL )
		delete RPERMISO_;
	RPERMISO_=r;
	setPermiso_idPermiso( r->idPermiso() );
}

void RolPermisoRecordBase::setPRPermiso_(RecordBase *pr)
{
	setRPermiso_((PermisoRecordBase*)pr);
}

void RolPermisoRecordBase::setRRol_(RolRecordBase* r)
{
	if( RROL_ != NULL )
		delete RROL_;
	RROL_=r;
	setRol_idRol( r->idRol() );
}

void RolPermisoRecordBase::setPRRol_(RecordBase *pr)
{
	setRRol_((RolRecordBase*)pr);
}



//get de los campos, si hay valor nuevo ese regresa, si no el normal

int RolPermisoRecordBase::idRolPermiso()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("idRolPermiso"))
		return IDROLPERMISO;
	else
		return getBackUpRecord()->property( "idRolPermiso" ).toInt();
}

int RolPermisoRecordBase::Permiso_idPermiso()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("Permiso_idPermiso"))
		return PERMISO_IDPERMISO;
	else
		return getBackUpRecord()->property( "Permiso_idPermiso" ).toInt();
}

int RolPermisoRecordBase::Rol_idRol()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("Rol_idRol"))
		return ROL_IDROL;
	else
		return getBackUpRecord()->property( "Rol_idRol" ).toInt();
}

int RolPermisoRecordBase::Permiso()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("Permiso"))
		return PERMISO;
	else
		return getBackUpRecord()->property( "Permiso" ).toInt();
}



PermisoRecordBase *RolPermisoRecordBase::RPermiso_()
{
	if ( RPERMISO_ == NULL )
	{
		RPERMISO_=new PermisoRecordBase(this,this,DB);
		RPERMISO_->setRecordEnabledBackup(enabledRecordBackup);

		connect( RPERMISO_,SIGNAL(hasValuesWithOutSave(bool,RecordBase*)),
			this, SIGNAL(hasValuesWithOutSave(bool,RecordBase*)));
	}

	return RPERMISO_;
}

RolRecordBase *RolPermisoRecordBase::RRol_()
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



//!Limpia los atributos
void RolPermisoRecordBase::clear()
{
	

	//limpiando no primitivos
	

	//limpiando foraneas
	if ( RPERMISO_ != NULL )
	RPERMISO_->clear();
if ( RROL_ != NULL )
	RROL_->clear();

}

void RolPermisoRecordBase::revert()
{
	RecordBase::revert();

	if ( RPERMISO_ != NULL )
	RPERMISO_->revert();
if ( RROL_ != NULL )
	RROL_->revert();

}

QStringList RolPermisoRecordBase::RolPermisoAttributesList() { return ROLPERMISOATTRIBUTESLIST; }

QStringList RolPermisoRecordBase::RolPermisoPKAttributesList() { return ROLPERMISOPKATTRIBUTESLIST; }

QString RolPermisoRecordBase::RolPermisoPKAutoIncrementAttribute() { return ROLPERMISOPKAUTOINCREMENTATTRIBUTE; }

QStringList RolPermisoRecordBase::RolPermisoDateTimeAttributesList() { return ROLPERMISODATETIMEATTRIBUTESLIST; }

QStringList RolPermisoRecordBase::getAttributesList()
{
return ROLPERMISOATTRIBUTESLIST;
}

QStringList RolPermisoRecordBase::getPKAttributesList()
{
return ROLPERMISOPKATTRIBUTESLIST;
}

QStringList RolPermisoRecordBase::getPKAutoIncrementAttributesList()
{
return QStringList() << ROLPERMISOPKAUTOINCREMENTATTRIBUTE;
}

QStringList RolPermisoRecordBase::getDateTimeAttributesList()
{
return ROLPERMISODATETIMEATTRIBUTESLIST;
}



QStringList RolPermisoRecordBase::PermisoFAttributes()
{
	return QStringList() << "Permiso_idPermiso";
}

QStringList RolPermisoRecordBase::RolFAttributes()
{
	return QStringList() << "Rol_idRol";
}



RecordBase *RolPermisoRecordBase::getLastChildDefaultRecord() { return this; }





QString RolPermisoRecordBase::idRolPermisoProperty() { return "idRolPermiso"; }

QString RolPermisoRecordBase::Permiso_idPermisoProperty() { return "Permiso_idPermiso"; }

QString RolPermisoRecordBase::Rol_idRolProperty() { return "Rol_idRol"; }

QString RolPermisoRecordBase::PermisoProperty() { return "Permiso"; }



/*! Esta función reimplementa operator=().

  Asigna \a record a este RolPermisoRecordBase.
*/
RolPermisoRecordBase& RolPermisoRecordBase::operator=(const RolPermisoRecordBase& record)
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

