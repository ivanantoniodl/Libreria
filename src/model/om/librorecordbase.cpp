#include "librorecordbase.h"

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
LibroRecordBase::LibroRecordBase(QObject *qparent,
							 RecordBase *rparent,
							 QSqlDatabase db):
RecordSimpleBase(qparent,rparent,db)
{
	TABLENAME="Libro";
	
	ISBACKUPRECORUSELOCALATT=false;
	BACKUPRECORD = new LibroRecordBase(false,qparent,rparent,db);

	init();
	initValues();
}

//!Constructor copia.
LibroRecordBase::LibroRecordBase(const LibroRecordBase &other):
RecordSimpleBase(other.QPARENT,other.PARENT,other.DB)
{
	init();

	foreach ( QString att, LIBROATTRIBUTESLIST )
		setProperty( att.toLocal8Bit(),
					other.property( att.toLocal8Bit() ));

	if ( other.TABLENAME == "Libro" )
	{
		TABLENAME = other.TABLENAME;
		
		ISBACKUPRECORUSELOCALATT = false; //este es el papa mayor, aqui si va
		BACKUPRECORD = new LibroRecordBase(false,other.QPARENT,other.PARENT,other.DB);
	}
}

LibroRecordBase::LibroRecordBase(bool conf,
							   QObject *qparent,
							   RecordBase *rparent,
							   QSqlDatabase db):
	RecordSimpleBase(qparent,rparent,db) //todos los hijos van asi
{
	if ( ! conf )
	{
		//es false, Entonces es la copia
		TABLENAME="Libro";
		ISBACKUPRECORUSELOCALATT = true;
		BACKUPRECORD=NULL;
	}

	

	init();
	initValues();
}

LibroRecordBase::~LibroRecordBase()
{}

//! Inicializa los registros foráneos.
void LibroRecordBase::init()
{
	

	lstTables.prepend("Libro");

	LIBROATTRIBUTESLIST << "id"
<< "Nombre"
<< "AnioImp";
	LIBROPKATTRIBUTESLIST << "id";
	LIBRODATETIMEATTRIBUTESLIST  = QStringList();;
	LIBROPKAUTOINCREMENTATTRIBUTE = "id";
}

//! Inicializa los atributos con tipos primitivos
void LibroRecordBase::initValues()
{
	ID=0;

}

void LibroRecordBase::setRecordEnabledBackup(bool enabled)
{
	enabledRecordBackup=enabled;
	
	
}

RecordBase *LibroRecordBase::getBackUpRecord() { return BACKUPRECORD; }

//set nuevo valor para un campo

void LibroRecordBase::setId(int id)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		ID=id;
	else
	{
		addAttributeInsertUpdate("id");
		getBackUpRecord()->setProperty( "id",id );
	}
}

void LibroRecordBase::setNombre(QString Nombre)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		NOMBRE=Nombre;
	else
	{
		addAttributeInsertUpdate("Nombre");
		getBackUpRecord()->setProperty( "Nombre",Nombre );
	}
}

void LibroRecordBase::setAnioImp(QString AnioImp)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		ANIOIMP=AnioImp;
	else
	{
		addAttributeInsertUpdate("AnioImp");
		getBackUpRecord()->setProperty( "AnioImp",AnioImp );
	}
}





//get de los campos, si hay valor nuevo ese regresa, si no el normal

int LibroRecordBase::id()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("id"))
		return ID;
	else
		return getBackUpRecord()->property( "id" ).toInt();
}

QString LibroRecordBase::Nombre()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("Nombre"))
		return NOMBRE;
	else
		return getBackUpRecord()->property( "Nombre" ).toString();
}

QString LibroRecordBase::AnioImp()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("AnioImp"))
		return ANIOIMP;
	else
		return getBackUpRecord()->property( "AnioImp" ).toString();
}





//!Limpia los atributos
void LibroRecordBase::clear()
{
	

	//limpiando no primitivos
	NOMBRE.clear();
ANIOIMP.clear();


	//limpiando foraneas
	
}

void LibroRecordBase::revert()
{
	RecordBase::revert();

	
}

QStringList LibroRecordBase::LibroAttributesList() { return LIBROATTRIBUTESLIST; }

QStringList LibroRecordBase::LibroPKAttributesList() { return LIBROPKATTRIBUTESLIST; }

QString LibroRecordBase::LibroPKAutoIncrementAttribute() { return LIBROPKAUTOINCREMENTATTRIBUTE; }

QStringList LibroRecordBase::LibroDateTimeAttributesList() { return LIBRODATETIMEATTRIBUTESLIST; }

QStringList LibroRecordBase::getAttributesList()
{
return LIBROATTRIBUTESLIST;
}

QStringList LibroRecordBase::getPKAttributesList()
{
return LIBROPKATTRIBUTESLIST;
}

QStringList LibroRecordBase::getPKAutoIncrementAttributesList()
{
return QStringList() << LIBROPKAUTOINCREMENTATTRIBUTE;
}

QStringList LibroRecordBase::getDateTimeAttributesList()
{
return LIBRODATETIMEATTRIBUTESLIST;
}





RecordBase *LibroRecordBase::getLastChildDefaultRecord() { return this; }





QString LibroRecordBase::idProperty() { return "id"; }

QString LibroRecordBase::NombreProperty() { return "Nombre"; }

QString LibroRecordBase::AnioImpProperty() { return "AnioImp"; }



/*! Esta función reimplementa operator=().

  Asigna \a record a este LibroRecordBase.
*/
LibroRecordBase& LibroRecordBase::operator=(const LibroRecordBase& record)
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

