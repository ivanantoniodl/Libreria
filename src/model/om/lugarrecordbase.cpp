#include "lugarrecordbase.h"

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
LugarRecordBase::LugarRecordBase(QObject *qparent,
							 RecordBase *rparent,
							 QSqlDatabase db):
RecordSimpleBase(qparent,rparent,db)
{
	TABLENAME="Lugar";
	
	ISBACKUPRECORUSELOCALATT=false;
	BACKUPRECORD = new LugarRecordBase(false,qparent,rparent,db);

	init();
	initValues();
}

//!Constructor copia.
LugarRecordBase::LugarRecordBase(const LugarRecordBase &other):
RecordSimpleBase(other.QPARENT,other.PARENT,other.DB)
{
	init();

	foreach ( QString att, LUGARATTRIBUTESLIST )
		setProperty( att.toLocal8Bit(),
					other.property( att.toLocal8Bit() ));

	if ( other.TABLENAME == "Lugar" )
	{
		TABLENAME = other.TABLENAME;
		
		ISBACKUPRECORUSELOCALATT = false; //este es el papa mayor, aqui si va
		BACKUPRECORD = new LugarRecordBase(false,other.QPARENT,other.PARENT,other.DB);
	}
}

LugarRecordBase::LugarRecordBase(bool conf,
							   QObject *qparent,
							   RecordBase *rparent,
							   QSqlDatabase db):
	RecordSimpleBase(qparent,rparent,db) //todos los hijos van asi
{
	if ( ! conf )
	{
		//es false, Entonces es la copia
		TABLENAME="Lugar";
		ISBACKUPRECORUSELOCALATT = true;
		BACKUPRECORD=NULL;
	}

	

	init();
	initValues();
}

LugarRecordBase::~LugarRecordBase()
{}

//! Inicializa los registros foráneos.
void LugarRecordBase::init()
{
	REMPRESA_ = NULL;
RLUGARTIPO_ = NULL;


	lstTables.prepend("Lugar");

	LUGARATTRIBUTESLIST << "idLugar"
<< "Empresa_idEmpresa"
<< "LugarTipo_idLugarTipo"
<< "Nombre"
<< "Direccion"
<< "Telefono"
<< "NumPlaca";
	LUGARPKATTRIBUTESLIST << "idLugar";
	LUGARDATETIMEATTRIBUTESLIST  = QStringList();;
	LUGARPKAUTOINCREMENTATTRIBUTE = "idLugar";
}

//! Inicializa los atributos con tipos primitivos
void LugarRecordBase::initValues()
{
	IDLUGAR=0;
EMPRESA_IDEMPRESA=0;
LUGARTIPO_IDLUGARTIPO=0;

}

void LugarRecordBase::setRecordEnabledBackup(bool enabled)
{
	enabledRecordBackup=enabled;
	
	if ( REMPRESA_ != NULL )
		REMPRESA_->setRecordEnabledBackup(enabled);
if ( RLUGARTIPO_ != NULL )
		RLUGARTIPO_->setRecordEnabledBackup(enabled);

}

RecordBase *LugarRecordBase::getBackUpRecord() { return BACKUPRECORD; }

//set nuevo valor para un campo

void LugarRecordBase::setIdLugar(int idLugar)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		IDLUGAR=idLugar;
	else
	{
		addAttributeInsertUpdate("idLugar");
		getBackUpRecord()->setProperty( "idLugar",idLugar );
	}
}

void LugarRecordBase::setEmpresa_idEmpresa(int Empresa_idEmpresa)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		EMPRESA_IDEMPRESA=Empresa_idEmpresa;
	else
	{
		addAttributeInsertUpdate("Empresa_idEmpresa");
		getBackUpRecord()->setProperty( "Empresa_idEmpresa",Empresa_idEmpresa );
	}
}

void LugarRecordBase::setLugarTipo_idLugarTipo(int LugarTipo_idLugarTipo)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		LUGARTIPO_IDLUGARTIPO=LugarTipo_idLugarTipo;
	else
	{
		addAttributeInsertUpdate("LugarTipo_idLugarTipo");
		getBackUpRecord()->setProperty( "LugarTipo_idLugarTipo",LugarTipo_idLugarTipo );
	}
}

void LugarRecordBase::setNombre(QString Nombre)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		NOMBRE=Nombre;
	else
	{
		addAttributeInsertUpdate("Nombre");
		getBackUpRecord()->setProperty( "Nombre",Nombre );
	}
}

void LugarRecordBase::setDireccion(QString Direccion)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		DIRECCION=Direccion;
	else
	{
		addAttributeInsertUpdate("Direccion");
		getBackUpRecord()->setProperty( "Direccion",Direccion );
	}
}

void LugarRecordBase::setTelefono(QString Telefono)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		TELEFONO=Telefono;
	else
	{
		addAttributeInsertUpdate("Telefono");
		getBackUpRecord()->setProperty( "Telefono",Telefono );
	}
}

void LugarRecordBase::setNumPlaca(QString NumPlaca)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		NUMPLACA=NumPlaca;
	else
	{
		addAttributeInsertUpdate("NumPlaca");
		getBackUpRecord()->setProperty( "NumPlaca",NumPlaca );
	}
}



void LugarRecordBase::setREmpresa_(EmpresaRecordBase* r)
{
	if( REMPRESA_ != NULL )
		delete REMPRESA_;
	REMPRESA_=r;
	setEmpresa_idEmpresa( r->idEmpresa() );
}

void LugarRecordBase::setPREmpresa_(RecordBase *pr)
{
	setREmpresa_((EmpresaRecordBase*)pr);
}

void LugarRecordBase::setRLugarTipo_(LugarTipoRecordBase* r)
{
	if( RLUGARTIPO_ != NULL )
		delete RLUGARTIPO_;
	RLUGARTIPO_=r;
	setLugarTipo_idLugarTipo( r->idLugarTipo() );
}

void LugarRecordBase::setPRLugarTipo_(RecordBase *pr)
{
	setRLugarTipo_((LugarTipoRecordBase*)pr);
}



//get de los campos, si hay valor nuevo ese regresa, si no el normal

int LugarRecordBase::idLugar()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("idLugar"))
		return IDLUGAR;
	else
		return getBackUpRecord()->property( "idLugar" ).toInt();
}

int LugarRecordBase::Empresa_idEmpresa()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("Empresa_idEmpresa"))
		return EMPRESA_IDEMPRESA;
	else
		return getBackUpRecord()->property( "Empresa_idEmpresa" ).toInt();
}

int LugarRecordBase::LugarTipo_idLugarTipo()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("LugarTipo_idLugarTipo"))
		return LUGARTIPO_IDLUGARTIPO;
	else
		return getBackUpRecord()->property( "LugarTipo_idLugarTipo" ).toInt();
}

QString LugarRecordBase::Nombre()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("Nombre"))
		return NOMBRE;
	else
		return getBackUpRecord()->property( "Nombre" ).toString();
}

QString LugarRecordBase::Direccion()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("Direccion"))
		return DIRECCION;
	else
		return getBackUpRecord()->property( "Direccion" ).toString();
}

QString LugarRecordBase::Telefono()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("Telefono"))
		return TELEFONO;
	else
		return getBackUpRecord()->property( "Telefono" ).toString();
}

QString LugarRecordBase::NumPlaca()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("NumPlaca"))
		return NUMPLACA;
	else
		return getBackUpRecord()->property( "NumPlaca" ).toString();
}



EmpresaRecordBase *LugarRecordBase::REmpresa_()
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

LugarTipoRecordBase *LugarRecordBase::RLugarTipo_()
{
	if ( RLUGARTIPO_ == NULL )
	{
		RLUGARTIPO_=new LugarTipoRecordBase(this,this,DB);
		RLUGARTIPO_->setRecordEnabledBackup(enabledRecordBackup);

		connect( RLUGARTIPO_,SIGNAL(hasValuesWithOutSave(bool,RecordBase*)),
			this, SIGNAL(hasValuesWithOutSave(bool,RecordBase*)));
	}

	return RLUGARTIPO_;
}



//!Limpia los atributos
void LugarRecordBase::clear()
{
	

	//limpiando no primitivos
	NOMBRE.clear();
DIRECCION.clear();
TELEFONO.clear();
NUMPLACA.clear();


	//limpiando foraneas
	if ( REMPRESA_ != NULL )
	REMPRESA_->clear();
if ( RLUGARTIPO_ != NULL )
	RLUGARTIPO_->clear();

}

void LugarRecordBase::revert()
{
	RecordBase::revert();

	if ( REMPRESA_ != NULL )
	REMPRESA_->revert();
if ( RLUGARTIPO_ != NULL )
	RLUGARTIPO_->revert();

}

QStringList LugarRecordBase::LugarAttributesList() { return LUGARATTRIBUTESLIST; }

QStringList LugarRecordBase::LugarPKAttributesList() { return LUGARPKATTRIBUTESLIST; }

QString LugarRecordBase::LugarPKAutoIncrementAttribute() { return LUGARPKAUTOINCREMENTATTRIBUTE; }

QStringList LugarRecordBase::LugarDateTimeAttributesList() { return LUGARDATETIMEATTRIBUTESLIST; }

QStringList LugarRecordBase::getAttributesList()
{
return LUGARATTRIBUTESLIST;
}

QStringList LugarRecordBase::getPKAttributesList()
{
return LUGARPKATTRIBUTESLIST;
}

QStringList LugarRecordBase::getPKAutoIncrementAttributesList()
{
return QStringList() << LUGARPKAUTOINCREMENTATTRIBUTE;
}

QStringList LugarRecordBase::getDateTimeAttributesList()
{
return LUGARDATETIMEATTRIBUTESLIST;
}



QStringList LugarRecordBase::EmpresaFAttributes()
{
	return QStringList() << "Empresa_idEmpresa";
}

QStringList LugarRecordBase::LugarTipoFAttributes()
{
	return QStringList() << "LugarTipo_idLugarTipo";
}



RecordBase *LugarRecordBase::getLastChildDefaultRecord() { return this; }





QString LugarRecordBase::idLugarProperty() { return "idLugar"; }

QString LugarRecordBase::Empresa_idEmpresaProperty() { return "Empresa_idEmpresa"; }

QString LugarRecordBase::LugarTipo_idLugarTipoProperty() { return "LugarTipo_idLugarTipo"; }

QString LugarRecordBase::NombreProperty() { return "Nombre"; }

QString LugarRecordBase::DireccionProperty() { return "Direccion"; }

QString LugarRecordBase::TelefonoProperty() { return "Telefono"; }

QString LugarRecordBase::NumPlacaProperty() { return "NumPlaca"; }



/*! Esta función reimplementa operator=().

  Asigna \a record a este LugarRecordBase.
*/
LugarRecordBase& LugarRecordBase::operator=(const LugarRecordBase& record)
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

