#include "autorrecordbase.h"

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
AutorRecordBase::AutorRecordBase(QObject *qparent,
							 RecordBase *rparent,
							 QSqlDatabase db):
RecordSimpleBase(qparent,rparent,db)
{
	TABLENAME="Autor";
	
	ISBACKUPRECORUSELOCALATT=false;
	BACKUPRECORD = new AutorRecordBase(false,qparent,rparent,db);

	init();
	initValues();
}

//!Constructor copia.
AutorRecordBase::AutorRecordBase(const AutorRecordBase &other):
RecordSimpleBase(other.QPARENT,other.PARENT,other.DB)
{
	init();

	foreach ( QString att, AUTORATTRIBUTESLIST )
		setProperty( att.toLocal8Bit(),
					other.property( att.toLocal8Bit() ));

	if ( other.TABLENAME == "Autor" )
	{
		TABLENAME = other.TABLENAME;
		
		ISBACKUPRECORUSELOCALATT = false; //este es el papa mayor, aqui si va
		BACKUPRECORD = new AutorRecordBase(false,other.QPARENT,other.PARENT,other.DB);
	}
}

AutorRecordBase::AutorRecordBase(bool conf,
							   QObject *qparent,
							   RecordBase *rparent,
							   QSqlDatabase db):
	RecordSimpleBase(qparent,rparent,db) //todos los hijos van asi
{
	if ( ! conf )
	{
		//es false, Entonces es la copia
		TABLENAME="Autor";
		ISBACKUPRECORUSELOCALATT = true;
		BACKUPRECORD=NULL;
	}

	

	init();
	initValues();
}

AutorRecordBase::~AutorRecordBase()
{}

//! Inicializa los registros foráneos.
void AutorRecordBase::init()
{
	

	lstTables.prepend("Autor");

	AUTORATTRIBUTESLIST << "id"
<< "Nombre"
<< "Direccion";
	AUTORPKATTRIBUTESLIST << "id";
	AUTORDATETIMEATTRIBUTESLIST  = QStringList();;
	AUTORPKAUTOINCREMENTATTRIBUTE = "id";
}

//! Inicializa los atributos con tipos primitivos
void AutorRecordBase::initValues()
{
	ID=0;

}

void AutorRecordBase::setRecordEnabledBackup(bool enabled)
{
	enabledRecordBackup=enabled;
	
	
}

RecordBase *AutorRecordBase::getBackUpRecord() { return BACKUPRECORD; }

//set nuevo valor para un campo

void AutorRecordBase::setId(int id)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		ID=id;
	else
	{
		addAttributeInsertUpdate("id");
		getBackUpRecord()->setProperty( "id",id );
	}
}

void AutorRecordBase::setNombre(QString Nombre)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		NOMBRE=Nombre;
	else
	{
		addAttributeInsertUpdate("Nombre");
		getBackUpRecord()->setProperty( "Nombre",Nombre );
	}
}

void AutorRecordBase::setDireccion(QString Direccion)
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

int AutorRecordBase::id()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("id"))
		return ID;
	else
		return getBackUpRecord()->property( "id" ).toInt();
}

QString AutorRecordBase::Nombre()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("Nombre"))
		return NOMBRE;
	else
		return getBackUpRecord()->property( "Nombre" ).toString();
}

QString AutorRecordBase::Direccion()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("Direccion"))
		return DIRECCION;
	else
		return getBackUpRecord()->property( "Direccion" ).toString();
}





//!Limpia los atributos
void AutorRecordBase::clear()
{
	

	//limpiando no primitivos
	NOMBRE.clear();
DIRECCION.clear();


	//limpiando foraneas
	
}

void AutorRecordBase::revert()
{
	RecordBase::revert();

	
}

QStringList AutorRecordBase::AutorAttributesList() { return AUTORATTRIBUTESLIST; }

QStringList AutorRecordBase::AutorPKAttributesList() { return AUTORPKATTRIBUTESLIST; }

QString AutorRecordBase::AutorPKAutoIncrementAttribute() { return AUTORPKAUTOINCREMENTATTRIBUTE; }

QStringList AutorRecordBase::AutorDateTimeAttributesList() { return AUTORDATETIMEATTRIBUTESLIST; }

QStringList AutorRecordBase::getAttributesList()
{
return AUTORATTRIBUTESLIST;
}

QStringList AutorRecordBase::getPKAttributesList()
{
return AUTORPKATTRIBUTESLIST;
}

QStringList AutorRecordBase::getPKAutoIncrementAttributesList()
{
return QStringList() << AUTORPKAUTOINCREMENTATTRIBUTE;
}

QStringList AutorRecordBase::getDateTimeAttributesList()
{
return AUTORDATETIMEATTRIBUTESLIST;
}





RecordBase *AutorRecordBase::getLastChildDefaultRecord() { return this; }





QString AutorRecordBase::idProperty() { return "id"; }

QString AutorRecordBase::NombreProperty() { return "Nombre"; }

QString AutorRecordBase::DireccionProperty() { return "Direccion"; }



/*! Esta función reimplementa operator=().

  Asigna \a record a este AutorRecordBase.
*/
AutorRecordBase& AutorRecordBase::operator=(const AutorRecordBase& record)
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

