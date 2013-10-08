#include "grupopermisorecordbase.h"

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
GrupoPermisoRecordBase::GrupoPermisoRecordBase(QObject *qparent,
							 RecordBase *rparent,
							 QSqlDatabase db):
RecordSimpleBase(qparent,rparent,db)
{
	TABLENAME="GrupoPermiso";
	
	ISBACKUPRECORUSELOCALATT=false;
	BACKUPRECORD = new GrupoPermisoRecordBase(false,qparent,rparent,db);

	init();
	initValues();
}

//!Constructor copia.
GrupoPermisoRecordBase::GrupoPermisoRecordBase(const GrupoPermisoRecordBase &other):
RecordSimpleBase(other.QPARENT,other.PARENT,other.DB)
{
	init();

	foreach ( QString att, GRUPOPERMISOATTRIBUTESLIST )
		setProperty( att.toLocal8Bit(),
					other.property( att.toLocal8Bit() ));

	if ( other.TABLENAME == "GrupoPermiso" )
	{
		TABLENAME = other.TABLENAME;
		
		ISBACKUPRECORUSELOCALATT = false; //este es el papa mayor, aqui si va
		BACKUPRECORD = new GrupoPermisoRecordBase(false,other.QPARENT,other.PARENT,other.DB);
	}
}

GrupoPermisoRecordBase::GrupoPermisoRecordBase(bool conf,
							   QObject *qparent,
							   RecordBase *rparent,
							   QSqlDatabase db):
	RecordSimpleBase(qparent,rparent,db) //todos los hijos van asi
{
	if ( ! conf )
	{
		//es false, Entonces es la copia
		TABLENAME="GrupoPermiso";
		ISBACKUPRECORUSELOCALATT = true;
		BACKUPRECORD=NULL;
	}

	

	init();
	initValues();
}

GrupoPermisoRecordBase::~GrupoPermisoRecordBase()
{}

//! Inicializa los registros foráneos.
void GrupoPermisoRecordBase::init()
{
	

	lstTables.prepend("GrupoPermiso");

	GRUPOPERMISOATTRIBUTESLIST << "idGrupoPermiso"
<< "Nombre";
	GRUPOPERMISOPKATTRIBUTESLIST << "idGrupoPermiso";
	GRUPOPERMISODATETIMEATTRIBUTESLIST  = QStringList();;
	GRUPOPERMISOPKAUTOINCREMENTATTRIBUTE = "idGrupoPermiso";
}

//! Inicializa los atributos con tipos primitivos
void GrupoPermisoRecordBase::initValues()
{
	IDGRUPOPERMISO=0;

}

void GrupoPermisoRecordBase::setRecordEnabledBackup(bool enabled)
{
	enabledRecordBackup=enabled;
	
	
}

RecordBase *GrupoPermisoRecordBase::getBackUpRecord() { return BACKUPRECORD; }

//set nuevo valor para un campo

void GrupoPermisoRecordBase::setIdGrupoPermiso(int idGrupoPermiso)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		IDGRUPOPERMISO=idGrupoPermiso;
	else
	{
		addAttributeInsertUpdate("idGrupoPermiso");
		getBackUpRecord()->setProperty( "idGrupoPermiso",idGrupoPermiso );
	}
}

void GrupoPermisoRecordBase::setNombre(QString Nombre)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		NOMBRE=Nombre;
	else
	{
		addAttributeInsertUpdate("Nombre");
		getBackUpRecord()->setProperty( "Nombre",Nombre );
	}
}





//get de los campos, si hay valor nuevo ese regresa, si no el normal

int GrupoPermisoRecordBase::idGrupoPermiso()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("idGrupoPermiso"))
		return IDGRUPOPERMISO;
	else
		return getBackUpRecord()->property( "idGrupoPermiso" ).toInt();
}

QString GrupoPermisoRecordBase::Nombre()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("Nombre"))
		return NOMBRE;
	else
		return getBackUpRecord()->property( "Nombre" ).toString();
}





//!Limpia los atributos
void GrupoPermisoRecordBase::clear()
{
	

	//limpiando no primitivos
	NOMBRE.clear();


	//limpiando foraneas
	
}

void GrupoPermisoRecordBase::revert()
{
	RecordBase::revert();

	
}

QStringList GrupoPermisoRecordBase::GrupoPermisoAttributesList() { return GRUPOPERMISOATTRIBUTESLIST; }

QStringList GrupoPermisoRecordBase::GrupoPermisoPKAttributesList() { return GRUPOPERMISOPKATTRIBUTESLIST; }

QString GrupoPermisoRecordBase::GrupoPermisoPKAutoIncrementAttribute() { return GRUPOPERMISOPKAUTOINCREMENTATTRIBUTE; }

QStringList GrupoPermisoRecordBase::GrupoPermisoDateTimeAttributesList() { return GRUPOPERMISODATETIMEATTRIBUTESLIST; }

QStringList GrupoPermisoRecordBase::getAttributesList()
{
return GRUPOPERMISOATTRIBUTESLIST;
}

QStringList GrupoPermisoRecordBase::getPKAttributesList()
{
return GRUPOPERMISOPKATTRIBUTESLIST;
}

QStringList GrupoPermisoRecordBase::getPKAutoIncrementAttributesList()
{
return QStringList() << GRUPOPERMISOPKAUTOINCREMENTATTRIBUTE;
}

QStringList GrupoPermisoRecordBase::getDateTimeAttributesList()
{
return GRUPOPERMISODATETIMEATTRIBUTESLIST;
}





RecordBase *GrupoPermisoRecordBase::getLastChildDefaultRecord() { return this; }





QString GrupoPermisoRecordBase::idGrupoPermisoProperty() { return "idGrupoPermiso"; }

QString GrupoPermisoRecordBase::NombreProperty() { return "Nombre"; }



/*! Esta función reimplementa operator=().

  Asigna \a record a este GrupoPermisoRecordBase.
*/
GrupoPermisoRecordBase& GrupoPermisoRecordBase::operator=(const GrupoPermisoRecordBase& record)
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

