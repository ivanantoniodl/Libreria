#include "empresarecordbase.h"

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
EmpresaRecordBase::EmpresaRecordBase(QObject *qparent,
							 RecordBase *rparent,
							 QSqlDatabase db):
RecordSimpleBase(qparent,rparent,db)
{
	TABLENAME="Empresa";
	
	ISBACKUPRECORUSELOCALATT=false;
	BACKUPRECORD = new EmpresaRecordBase(false,qparent,rparent,db);

	init();
	initValues();
}

//!Constructor copia.
EmpresaRecordBase::EmpresaRecordBase(const EmpresaRecordBase &other):
RecordSimpleBase(other.QPARENT,other.PARENT,other.DB)
{
	init();

	foreach ( QString att, EMPRESAATTRIBUTESLIST )
		setProperty( att.toLocal8Bit(),
					other.property( att.toLocal8Bit() ));

	if ( other.TABLENAME == "Empresa" )
	{
		TABLENAME = other.TABLENAME;
		
		ISBACKUPRECORUSELOCALATT = false; //este es el papa mayor, aqui si va
		BACKUPRECORD = new EmpresaRecordBase(false,other.QPARENT,other.PARENT,other.DB);
	}
}

EmpresaRecordBase::EmpresaRecordBase(bool conf,
							   QObject *qparent,
							   RecordBase *rparent,
							   QSqlDatabase db):
	RecordSimpleBase(qparent,rparent,db) //todos los hijos van asi
{
	if ( ! conf )
	{
		//es false, Entonces es la copia
		TABLENAME="Empresa";
		ISBACKUPRECORUSELOCALATT = true;
		BACKUPRECORD=NULL;
	}

	

	init();
	initValues();
}

EmpresaRecordBase::~EmpresaRecordBase()
{}

//! Inicializa los registros foráneos.
void EmpresaRecordBase::init()
{
	

	lstTables.prepend("Empresa");

	EMPRESAATTRIBUTESLIST << "idEmpresa"
<< "Nombre";
	EMPRESAPKATTRIBUTESLIST << "idEmpresa";
	EMPRESADATETIMEATTRIBUTESLIST  = QStringList();;
	EMPRESAPKAUTOINCREMENTATTRIBUTE = "idEmpresa";
}

//! Inicializa los atributos con tipos primitivos
void EmpresaRecordBase::initValues()
{
	IDEMPRESA=0;

}

void EmpresaRecordBase::setRecordEnabledBackup(bool enabled)
{
	enabledRecordBackup=enabled;
	
	
}

RecordBase *EmpresaRecordBase::getBackUpRecord() { return BACKUPRECORD; }

//set nuevo valor para un campo

void EmpresaRecordBase::setIdEmpresa(int idEmpresa)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		IDEMPRESA=idEmpresa;
	else
	{
		addAttributeInsertUpdate("idEmpresa");
		getBackUpRecord()->setProperty( "idEmpresa",idEmpresa );
	}
}

void EmpresaRecordBase::setNombre(QString Nombre)
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

int EmpresaRecordBase::idEmpresa()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("idEmpresa"))
		return IDEMPRESA;
	else
		return getBackUpRecord()->property( "idEmpresa" ).toInt();
}

QString EmpresaRecordBase::Nombre()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("Nombre"))
		return NOMBRE;
	else
		return getBackUpRecord()->property( "Nombre" ).toString();
}





//!Limpia los atributos
void EmpresaRecordBase::clear()
{
	

	//limpiando no primitivos
	NOMBRE.clear();


	//limpiando foraneas
	
}

void EmpresaRecordBase::revert()
{
	RecordBase::revert();

	
}

QStringList EmpresaRecordBase::EmpresaAttributesList() { return EMPRESAATTRIBUTESLIST; }

QStringList EmpresaRecordBase::EmpresaPKAttributesList() { return EMPRESAPKATTRIBUTESLIST; }

QString EmpresaRecordBase::EmpresaPKAutoIncrementAttribute() { return EMPRESAPKAUTOINCREMENTATTRIBUTE; }

QStringList EmpresaRecordBase::EmpresaDateTimeAttributesList() { return EMPRESADATETIMEATTRIBUTESLIST; }

QStringList EmpresaRecordBase::getAttributesList()
{
return EMPRESAATTRIBUTESLIST;
}

QStringList EmpresaRecordBase::getPKAttributesList()
{
return EMPRESAPKATTRIBUTESLIST;
}

QStringList EmpresaRecordBase::getPKAutoIncrementAttributesList()
{
return QStringList() << EMPRESAPKAUTOINCREMENTATTRIBUTE;
}

QStringList EmpresaRecordBase::getDateTimeAttributesList()
{
return EMPRESADATETIMEATTRIBUTESLIST;
}





RecordBase *EmpresaRecordBase::getLastChildDefaultRecord() { return this; }





QString EmpresaRecordBase::idEmpresaProperty() { return "idEmpresa"; }

QString EmpresaRecordBase::NombreProperty() { return "Nombre"; }



/*! Esta función reimplementa operator=().

  Asigna \a record a este EmpresaRecordBase.
*/
EmpresaRecordBase& EmpresaRecordBase::operator=(const EmpresaRecordBase& record)
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

