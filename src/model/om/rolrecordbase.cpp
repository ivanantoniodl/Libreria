#include "rolrecordbase.h"

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
RolRecordBase::RolRecordBase(QObject *qparent,
							 RecordBase *rparent,
							 QSqlDatabase db):
RecordSimpleBase(qparent,rparent,db)
{
	TABLENAME="Rol";
	
	ISBACKUPRECORUSELOCALATT=false;
	BACKUPRECORD = new RolRecordBase(false,qparent,rparent,db);

	init();
	initValues();
}

//!Constructor copia.
RolRecordBase::RolRecordBase(const RolRecordBase &other):
RecordSimpleBase(other.QPARENT,other.PARENT,other.DB)
{
	init();

	foreach ( QString att, ROLATTRIBUTESLIST )
		setProperty( att.toLocal8Bit(),
					other.property( att.toLocal8Bit() ));

	if ( other.TABLENAME == "Rol" )
	{
		TABLENAME = other.TABLENAME;
		
		ISBACKUPRECORUSELOCALATT = false; //este es el papa mayor, aqui si va
		BACKUPRECORD = new RolRecordBase(false,other.QPARENT,other.PARENT,other.DB);
	}
}

RolRecordBase::RolRecordBase(bool conf,
							   QObject *qparent,
							   RecordBase *rparent,
							   QSqlDatabase db):
	RecordSimpleBase(qparent,rparent,db) //todos los hijos van asi
{
	if ( ! conf )
	{
		//es false, Entonces es la copia
		TABLENAME="Rol";
		ISBACKUPRECORUSELOCALATT = true;
		BACKUPRECORD=NULL;
	}

	

	init();
	initValues();
}

RolRecordBase::~RolRecordBase()
{}

//! Inicializa los registros foráneos.
void RolRecordBase::init()
{
	

	lstTables.prepend("Rol");

	ROLATTRIBUTESLIST << "idRol"
<< "Rol";
	ROLPKATTRIBUTESLIST << "idRol";
	ROLDATETIMEATTRIBUTESLIST  = QStringList();;
	ROLPKAUTOINCREMENTATTRIBUTE = "idRol";
}

//! Inicializa los atributos con tipos primitivos
void RolRecordBase::initValues()
{
	IDROL=0;

}

void RolRecordBase::setRecordEnabledBackup(bool enabled)
{
	enabledRecordBackup=enabled;
	
	
}

RecordBase *RolRecordBase::getBackUpRecord() { return BACKUPRECORD; }

//set nuevo valor para un campo

void RolRecordBase::setIdRol(int idRol)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		IDROL=idRol;
	else
	{
		addAttributeInsertUpdate("idRol");
		getBackUpRecord()->setProperty( "idRol",idRol );
	}
}

void RolRecordBase::setRol(QString Rol)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		ROL=Rol;
	else
	{
		addAttributeInsertUpdate("Rol");
		getBackUpRecord()->setProperty( "Rol",Rol );
	}
}





//get de los campos, si hay valor nuevo ese regresa, si no el normal

int RolRecordBase::idRol()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("idRol"))
		return IDROL;
	else
		return getBackUpRecord()->property( "idRol" ).toInt();
}

QString RolRecordBase::Rol()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("Rol"))
		return ROL;
	else
		return getBackUpRecord()->property( "Rol" ).toString();
}





//!Limpia los atributos
void RolRecordBase::clear()
{
	

	//limpiando no primitivos
	ROL.clear();


	//limpiando foraneas
	
}

void RolRecordBase::revert()
{
	RecordBase::revert();

	
}

QStringList RolRecordBase::RolAttributesList() { return ROLATTRIBUTESLIST; }

QStringList RolRecordBase::RolPKAttributesList() { return ROLPKATTRIBUTESLIST; }

QString RolRecordBase::RolPKAutoIncrementAttribute() { return ROLPKAUTOINCREMENTATTRIBUTE; }

QStringList RolRecordBase::RolDateTimeAttributesList() { return ROLDATETIMEATTRIBUTESLIST; }

QStringList RolRecordBase::getAttributesList()
{
return ROLATTRIBUTESLIST;
}

QStringList RolRecordBase::getPKAttributesList()
{
return ROLPKATTRIBUTESLIST;
}

QStringList RolRecordBase::getPKAutoIncrementAttributesList()
{
return QStringList() << ROLPKAUTOINCREMENTATTRIBUTE;
}

QStringList RolRecordBase::getDateTimeAttributesList()
{
return ROLDATETIMEATTRIBUTESLIST;
}





RecordBase *RolRecordBase::getLastChildDefaultRecord() { return this; }





QString RolRecordBase::idRolProperty() { return "idRol"; }

QString RolRecordBase::RolProperty() { return "Rol"; }



/*! Esta función reimplementa operator=().

  Asigna \a record a este RolRecordBase.
*/
RolRecordBase& RolRecordBase::operator=(const RolRecordBase& record)
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

