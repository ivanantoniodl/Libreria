#include "usuariocargorecordbase.h"

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
UsuarioCargoRecordBase::UsuarioCargoRecordBase(QObject *qparent,
							 RecordBase *rparent,
							 QSqlDatabase db):
RecordSimpleBase(qparent,rparent,db)
{
	TABLENAME="UsuarioCargo";
	
	ISBACKUPRECORUSELOCALATT=false;
	BACKUPRECORD = new UsuarioCargoRecordBase(false,qparent,rparent,db);

	init();
	initValues();
}

//!Constructor copia.
UsuarioCargoRecordBase::UsuarioCargoRecordBase(const UsuarioCargoRecordBase &other):
RecordSimpleBase(other.QPARENT,other.PARENT,other.DB)
{
	init();

	foreach ( QString att, USUARIOCARGOATTRIBUTESLIST )
		setProperty( att.toLocal8Bit(),
					other.property( att.toLocal8Bit() ));

	if ( other.TABLENAME == "UsuarioCargo" )
	{
		TABLENAME = other.TABLENAME;
		
		ISBACKUPRECORUSELOCALATT = false; //este es el papa mayor, aqui si va
		BACKUPRECORD = new UsuarioCargoRecordBase(false,other.QPARENT,other.PARENT,other.DB);
	}
}

UsuarioCargoRecordBase::UsuarioCargoRecordBase(bool conf,
							   QObject *qparent,
							   RecordBase *rparent,
							   QSqlDatabase db):
	RecordSimpleBase(qparent,rparent,db) //todos los hijos van asi
{
	if ( ! conf )
	{
		//es false, Entonces es la copia
		TABLENAME="UsuarioCargo";
		ISBACKUPRECORUSELOCALATT = true;
		BACKUPRECORD=NULL;
	}

	

	init();
	initValues();
}

UsuarioCargoRecordBase::~UsuarioCargoRecordBase()
{}

//! Inicializa los registros foráneos.
void UsuarioCargoRecordBase::init()
{
	

	lstTables.prepend("UsuarioCargo");

	USUARIOCARGOATTRIBUTESLIST << "idUsuarioCargo"
<< "Cargo";
	USUARIOCARGOPKATTRIBUTESLIST << "idUsuarioCargo";
	USUARIOCARGODATETIMEATTRIBUTESLIST  = QStringList();;
	USUARIOCARGOPKAUTOINCREMENTATTRIBUTE = "idUsuarioCargo";
}

//! Inicializa los atributos con tipos primitivos
void UsuarioCargoRecordBase::initValues()
{
	IDUSUARIOCARGO=0;

}

void UsuarioCargoRecordBase::setRecordEnabledBackup(bool enabled)
{
	enabledRecordBackup=enabled;
	
	
}

RecordBase *UsuarioCargoRecordBase::getBackUpRecord() { return BACKUPRECORD; }

//set nuevo valor para un campo

void UsuarioCargoRecordBase::setIdUsuarioCargo(int idUsuarioCargo)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		IDUSUARIOCARGO=idUsuarioCargo;
	else
	{
		addAttributeInsertUpdate("idUsuarioCargo");
		getBackUpRecord()->setProperty( "idUsuarioCargo",idUsuarioCargo );
	}
}

void UsuarioCargoRecordBase::setCargo(QString Cargo)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		CARGO=Cargo;
	else
	{
		addAttributeInsertUpdate("Cargo");
		getBackUpRecord()->setProperty( "Cargo",Cargo );
	}
}





//get de los campos, si hay valor nuevo ese regresa, si no el normal

int UsuarioCargoRecordBase::idUsuarioCargo()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("idUsuarioCargo"))
		return IDUSUARIOCARGO;
	else
		return getBackUpRecord()->property( "idUsuarioCargo" ).toInt();
}

QString UsuarioCargoRecordBase::Cargo()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("Cargo"))
		return CARGO;
	else
		return getBackUpRecord()->property( "Cargo" ).toString();
}





//!Limpia los atributos
void UsuarioCargoRecordBase::clear()
{
	

	//limpiando no primitivos
	CARGO.clear();


	//limpiando foraneas
	
}

void UsuarioCargoRecordBase::revert()
{
	RecordBase::revert();

	
}

QStringList UsuarioCargoRecordBase::UsuarioCargoAttributesList() { return USUARIOCARGOATTRIBUTESLIST; }

QStringList UsuarioCargoRecordBase::UsuarioCargoPKAttributesList() { return USUARIOCARGOPKATTRIBUTESLIST; }

QString UsuarioCargoRecordBase::UsuarioCargoPKAutoIncrementAttribute() { return USUARIOCARGOPKAUTOINCREMENTATTRIBUTE; }

QStringList UsuarioCargoRecordBase::UsuarioCargoDateTimeAttributesList() { return USUARIOCARGODATETIMEATTRIBUTESLIST; }

QStringList UsuarioCargoRecordBase::getAttributesList()
{
return USUARIOCARGOATTRIBUTESLIST;
}

QStringList UsuarioCargoRecordBase::getPKAttributesList()
{
return USUARIOCARGOPKATTRIBUTESLIST;
}

QStringList UsuarioCargoRecordBase::getPKAutoIncrementAttributesList()
{
return QStringList() << USUARIOCARGOPKAUTOINCREMENTATTRIBUTE;
}

QStringList UsuarioCargoRecordBase::getDateTimeAttributesList()
{
return USUARIOCARGODATETIMEATTRIBUTESLIST;
}





RecordBase *UsuarioCargoRecordBase::getLastChildDefaultRecord() { return this; }





QString UsuarioCargoRecordBase::idUsuarioCargoProperty() { return "idUsuarioCargo"; }

QString UsuarioCargoRecordBase::CargoProperty() { return "Cargo"; }



/*! Esta función reimplementa operator=().

  Asigna \a record a este UsuarioCargoRecordBase.
*/
UsuarioCargoRecordBase& UsuarioCargoRecordBase::operator=(const UsuarioCargoRecordBase& record)
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

