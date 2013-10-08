#include "editorialrecordbase.h"

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
EditorialRecordBase::EditorialRecordBase(QObject *qparent,
							 RecordBase *rparent,
							 QSqlDatabase db):
RecordSimpleBase(qparent,rparent,db)
{
	TABLENAME="Editorial";
	
	ISBACKUPRECORUSELOCALATT=false;
	BACKUPRECORD = new EditorialRecordBase(false,qparent,rparent,db);

	init();
	initValues();
}

//!Constructor copia.
EditorialRecordBase::EditorialRecordBase(const EditorialRecordBase &other):
RecordSimpleBase(other.QPARENT,other.PARENT,other.DB)
{
	init();

	foreach ( QString att, EDITORIALATTRIBUTESLIST )
		setProperty( att.toLocal8Bit(),
					other.property( att.toLocal8Bit() ));

	if ( other.TABLENAME == "Editorial" )
	{
		TABLENAME = other.TABLENAME;
		
		ISBACKUPRECORUSELOCALATT = false; //este es el papa mayor, aqui si va
		BACKUPRECORD = new EditorialRecordBase(false,other.QPARENT,other.PARENT,other.DB);
	}
}

EditorialRecordBase::EditorialRecordBase(bool conf,
							   QObject *qparent,
							   RecordBase *rparent,
							   QSqlDatabase db):
	RecordSimpleBase(qparent,rparent,db) //todos los hijos van asi
{
	if ( ! conf )
	{
		//es false, Entonces es la copia
		TABLENAME="Editorial";
		ISBACKUPRECORUSELOCALATT = true;
		BACKUPRECORD=NULL;
	}

	

	init();
	initValues();
}

EditorialRecordBase::~EditorialRecordBase()
{}

//! Inicializa los registros foráneos.
void EditorialRecordBase::init()
{
	

	lstTables.prepend("Editorial");

	EDITORIALATTRIBUTESLIST << "id"
<< "Nombre"
<< "Direccion";
	EDITORIALPKATTRIBUTESLIST << "id";
	EDITORIALDATETIMEATTRIBUTESLIST  = QStringList();;
	EDITORIALPKAUTOINCREMENTATTRIBUTE = "id";
}

//! Inicializa los atributos con tipos primitivos
void EditorialRecordBase::initValues()
{
	ID=0;

}

void EditorialRecordBase::setRecordEnabledBackup(bool enabled)
{
	enabledRecordBackup=enabled;
	
	
}

RecordBase *EditorialRecordBase::getBackUpRecord() { return BACKUPRECORD; }

//set nuevo valor para un campo

void EditorialRecordBase::setId(int id)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		ID=id;
	else
	{
		addAttributeInsertUpdate("id");
		getBackUpRecord()->setProperty( "id",id );
	}
}

void EditorialRecordBase::setNombre(QString Nombre)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		NOMBRE=Nombre;
	else
	{
		addAttributeInsertUpdate("Nombre");
		getBackUpRecord()->setProperty( "Nombre",Nombre );
	}
}

void EditorialRecordBase::setDireccion(QString Direccion)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		DIRECCION=Direccion;
	else
	{
		addAttributeInsertUpdate("Direccion");
		getBackUpRecord()->setProperty( "Direccion",Direccion );
	}
}





//get de los campos, si hay valor nuevo ese regresa, si no el normal

int EditorialRecordBase::id()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("id"))
		return ID;
	else
		return getBackUpRecord()->property( "id" ).toInt();
}

QString EditorialRecordBase::Nombre()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("Nombre"))
		return NOMBRE;
	else
		return getBackUpRecord()->property( "Nombre" ).toString();
}

QString EditorialRecordBase::Direccion()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("Direccion"))
		return DIRECCION;
	else
		return getBackUpRecord()->property( "Direccion" ).toString();
}





//!Limpia los atributos
void EditorialRecordBase::clear()
{
	

	//limpiando no primitivos
	NOMBRE.clear();
DIRECCION.clear();


	//limpiando foraneas
	
}

void EditorialRecordBase::revert()
{
	RecordBase::revert();

	
}

QStringList EditorialRecordBase::EditorialAttributesList() { return EDITORIALATTRIBUTESLIST; }

QStringList EditorialRecordBase::EditorialPKAttributesList() { return EDITORIALPKATTRIBUTESLIST; }

QString EditorialRecordBase::EditorialPKAutoIncrementAttribute() { return EDITORIALPKAUTOINCREMENTATTRIBUTE; }

QStringList EditorialRecordBase::EditorialDateTimeAttributesList() { return EDITORIALDATETIMEATTRIBUTESLIST; }

QStringList EditorialRecordBase::getAttributesList()
{
return EDITORIALATTRIBUTESLIST;
}

QStringList EditorialRecordBase::getPKAttributesList()
{
return EDITORIALPKATTRIBUTESLIST;
}

QStringList EditorialRecordBase::getPKAutoIncrementAttributesList()
{
return QStringList() << EDITORIALPKAUTOINCREMENTATTRIBUTE;
}

QStringList EditorialRecordBase::getDateTimeAttributesList()
{
return EDITORIALDATETIMEATTRIBUTESLIST;
}





RecordBase *EditorialRecordBase::getLastChildDefaultRecord() { return this; }





QString EditorialRecordBase::idProperty() { return "id"; }

QString EditorialRecordBase::NombreProperty() { return "Nombre"; }

QString EditorialRecordBase::DireccionProperty() { return "Direccion"; }



/*! Esta función reimplementa operator=().

  Asigna \a record a este EditorialRecordBase.
*/
EditorialRecordBase& EditorialRecordBase::operator=(const EditorialRecordBase& record)
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

