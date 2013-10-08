#include "lugartiporecordbase.h"

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
LugarTipoRecordBase::LugarTipoRecordBase(QObject *qparent,
							 RecordBase *rparent,
							 QSqlDatabase db):
RecordSimpleBase(qparent,rparent,db)
{
	TABLENAME="LugarTipo";
	
	ISBACKUPRECORUSELOCALATT=false;
	BACKUPRECORD = new LugarTipoRecordBase(false,qparent,rparent,db);

	init();
	initValues();
}

//!Constructor copia.
LugarTipoRecordBase::LugarTipoRecordBase(const LugarTipoRecordBase &other):
RecordSimpleBase(other.QPARENT,other.PARENT,other.DB)
{
	init();

	foreach ( QString att, LUGARTIPOATTRIBUTESLIST )
		setProperty( att.toLocal8Bit(),
					other.property( att.toLocal8Bit() ));

	if ( other.TABLENAME == "LugarTipo" )
	{
		TABLENAME = other.TABLENAME;
		
		ISBACKUPRECORUSELOCALATT = false; //este es el papa mayor, aqui si va
		BACKUPRECORD = new LugarTipoRecordBase(false,other.QPARENT,other.PARENT,other.DB);
	}
}

LugarTipoRecordBase::LugarTipoRecordBase(bool conf,
							   QObject *qparent,
							   RecordBase *rparent,
							   QSqlDatabase db):
	RecordSimpleBase(qparent,rparent,db) //todos los hijos van asi
{
	if ( ! conf )
	{
		//es false, Entonces es la copia
		TABLENAME="LugarTipo";
		ISBACKUPRECORUSELOCALATT = true;
		BACKUPRECORD=NULL;
	}

	

	init();
	initValues();
}

LugarTipoRecordBase::~LugarTipoRecordBase()
{}

//! Inicializa los registros foráneos.
void LugarTipoRecordBase::init()
{
	

	lstTables.prepend("LugarTipo");

	LUGARTIPOATTRIBUTESLIST << "idLugarTipo"
<< "Tipo";
	LUGARTIPOPKATTRIBUTESLIST << "idLugarTipo";
	LUGARTIPODATETIMEATTRIBUTESLIST  = QStringList();;
	LUGARTIPOPKAUTOINCREMENTATTRIBUTE = "idLugarTipo";
}

//! Inicializa los atributos con tipos primitivos
void LugarTipoRecordBase::initValues()
{
	IDLUGARTIPO=0;

}

void LugarTipoRecordBase::setRecordEnabledBackup(bool enabled)
{
	enabledRecordBackup=enabled;
	
	
}

RecordBase *LugarTipoRecordBase::getBackUpRecord() { return BACKUPRECORD; }

//set nuevo valor para un campo

void LugarTipoRecordBase::setIdLugarTipo(int idLugarTipo)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		IDLUGARTIPO=idLugarTipo;
	else
	{
		addAttributeInsertUpdate("idLugarTipo");
		getBackUpRecord()->setProperty( "idLugarTipo",idLugarTipo );
	}
}

void LugarTipoRecordBase::setTipo(QString Tipo)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		TIPO=Tipo;
	else
	{
		addAttributeInsertUpdate("Tipo");
		getBackUpRecord()->setProperty( "Tipo",Tipo );
	}
}





//get de los campos, si hay valor nuevo ese regresa, si no el normal

int LugarTipoRecordBase::idLugarTipo()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("idLugarTipo"))
		return IDLUGARTIPO;
	else
		return getBackUpRecord()->property( "idLugarTipo" ).toInt();
}

QString LugarTipoRecordBase::Tipo()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("Tipo"))
		return TIPO;
	else
		return getBackUpRecord()->property( "Tipo" ).toString();
}





//!Limpia los atributos
void LugarTipoRecordBase::clear()
{
	

	//limpiando no primitivos
	TIPO.clear();


	//limpiando foraneas
	
}

void LugarTipoRecordBase::revert()
{
	RecordBase::revert();

	
}

QStringList LugarTipoRecordBase::LugarTipoAttributesList() { return LUGARTIPOATTRIBUTESLIST; }

QStringList LugarTipoRecordBase::LugarTipoPKAttributesList() { return LUGARTIPOPKATTRIBUTESLIST; }

QString LugarTipoRecordBase::LugarTipoPKAutoIncrementAttribute() { return LUGARTIPOPKAUTOINCREMENTATTRIBUTE; }

QStringList LugarTipoRecordBase::LugarTipoDateTimeAttributesList() { return LUGARTIPODATETIMEATTRIBUTESLIST; }

QStringList LugarTipoRecordBase::getAttributesList()
{
return LUGARTIPOATTRIBUTESLIST;
}

QStringList LugarTipoRecordBase::getPKAttributesList()
{
return LUGARTIPOPKATTRIBUTESLIST;
}

QStringList LugarTipoRecordBase::getPKAutoIncrementAttributesList()
{
return QStringList() << LUGARTIPOPKAUTOINCREMENTATTRIBUTE;
}

QStringList LugarTipoRecordBase::getDateTimeAttributesList()
{
return LUGARTIPODATETIMEATTRIBUTESLIST;
}





RecordBase *LugarTipoRecordBase::getLastChildDefaultRecord() { return this; }





QString LugarTipoRecordBase::idLugarTipoProperty() { return "idLugarTipo"; }

QString LugarTipoRecordBase::TipoProperty() { return "Tipo"; }



/*! Esta función reimplementa operator=().

  Asigna \a record a este LugarTipoRecordBase.
*/
LugarTipoRecordBase& LugarTipoRecordBase::operator=(const LugarTipoRecordBase& record)
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

