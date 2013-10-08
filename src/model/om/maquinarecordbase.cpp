#include "maquinarecordbase.h"

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
MaquinaRecordBase::MaquinaRecordBase(QObject *qparent,
							 RecordBase *rparent,
							 QSqlDatabase db):
RecordSimpleBase(qparent,rparent,db)
{
	TABLENAME="Maquina";
	
	ISBACKUPRECORUSELOCALATT=false;
	BACKUPRECORD = new MaquinaRecordBase(false,qparent,rparent,db);

	init();
	initValues();
}

//!Constructor copia.
MaquinaRecordBase::MaquinaRecordBase(const MaquinaRecordBase &other):
RecordSimpleBase(other.QPARENT,other.PARENT,other.DB)
{
	init();

	foreach ( QString att, MAQUINAATTRIBUTESLIST )
		setProperty( att.toLocal8Bit(),
					other.property( att.toLocal8Bit() ));

	if ( other.TABLENAME == "Maquina" )
	{
		TABLENAME = other.TABLENAME;
		
		ISBACKUPRECORUSELOCALATT = false; //este es el papa mayor, aqui si va
		BACKUPRECORD = new MaquinaRecordBase(false,other.QPARENT,other.PARENT,other.DB);
	}
}

MaquinaRecordBase::MaquinaRecordBase(bool conf,
							   QObject *qparent,
							   RecordBase *rparent,
							   QSqlDatabase db):
	RecordSimpleBase(qparent,rparent,db) //todos los hijos van asi
{
	if ( ! conf )
	{
		//es false, Entonces es la copia
		TABLENAME="Maquina";
		ISBACKUPRECORUSELOCALATT = true;
		BACKUPRECORD=NULL;
	}

	

	init();
	initValues();
}

MaquinaRecordBase::~MaquinaRecordBase()
{}

//! Inicializa los registros foráneos.
void MaquinaRecordBase::init()
{
	RLUGAR_ = NULL;


	lstTables.prepend("Maquina");

	MAQUINAATTRIBUTESLIST << "idMaquina"
<< "Ip"
<< "Lugar_idLugar";
	MAQUINAPKATTRIBUTESLIST << "idMaquina";
	MAQUINADATETIMEATTRIBUTESLIST  = QStringList();;
	MAQUINAPKAUTOINCREMENTATTRIBUTE = "idMaquina";
}

//! Inicializa los atributos con tipos primitivos
void MaquinaRecordBase::initValues()
{
	IDMAQUINA=0;
LUGAR_IDLUGAR=0;

}

void MaquinaRecordBase::setRecordEnabledBackup(bool enabled)
{
	enabledRecordBackup=enabled;
	
	if ( RLUGAR_ != NULL )
		RLUGAR_->setRecordEnabledBackup(enabled);

}

RecordBase *MaquinaRecordBase::getBackUpRecord() { return BACKUPRECORD; }

//set nuevo valor para un campo

void MaquinaRecordBase::setIdMaquina(int idMaquina)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		IDMAQUINA=idMaquina;
	else
	{
		addAttributeInsertUpdate("idMaquina");
		getBackUpRecord()->setProperty( "idMaquina",idMaquina );
	}
}

void MaquinaRecordBase::setIp(QString Ip)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		IP=Ip;
	else
	{
		addAttributeInsertUpdate("Ip");
		getBackUpRecord()->setProperty( "Ip",Ip );
	}
}

void MaquinaRecordBase::setLugar_idLugar(int Lugar_idLugar)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		LUGAR_IDLUGAR=Lugar_idLugar;
	else
	{
		addAttributeInsertUpdate("Lugar_idLugar");
		getBackUpRecord()->setProperty( "Lugar_idLugar",Lugar_idLugar );
	}
}



void MaquinaRecordBase::setRLugar_(LugarRecordBase* r)
{
	if( RLUGAR_ != NULL )
		delete RLUGAR_;
	RLUGAR_=r;
	setLugar_idLugar( r->idLugar() );
}

void MaquinaRecordBase::setPRLugar_(RecordBase *pr)
{
	setRLugar_((LugarRecordBase*)pr);
}



//get de los campos, si hay valor nuevo ese regresa, si no el normal

int MaquinaRecordBase::idMaquina()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("idMaquina"))
		return IDMAQUINA;
	else
		return getBackUpRecord()->property( "idMaquina" ).toInt();
}

QString MaquinaRecordBase::Ip()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("Ip"))
		return IP;
	else
		return getBackUpRecord()->property( "Ip" ).toString();
}

int MaquinaRecordBase::Lugar_idLugar()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("Lugar_idLugar"))
		return LUGAR_IDLUGAR;
	else
		return getBackUpRecord()->property( "Lugar_idLugar" ).toInt();
}



LugarRecordBase *MaquinaRecordBase::RLugar_()
{
	if ( RLUGAR_ == NULL )
	{
		RLUGAR_=new LugarRecordBase(this,this,DB);
		RLUGAR_->setRecordEnabledBackup(enabledRecordBackup);

		connect( RLUGAR_,SIGNAL(hasValuesWithOutSave(bool,RecordBase*)),
			this, SIGNAL(hasValuesWithOutSave(bool,RecordBase*)));
	}

	return RLUGAR_;
}



//!Limpia los atributos
void MaquinaRecordBase::clear()
{
	

	//limpiando no primitivos
	IP.clear();


	//limpiando foraneas
	if ( RLUGAR_ != NULL )
	RLUGAR_->clear();

}

void MaquinaRecordBase::revert()
{
	RecordBase::revert();

	if ( RLUGAR_ != NULL )
	RLUGAR_->revert();

}

QStringList MaquinaRecordBase::MaquinaAttributesList() { return MAQUINAATTRIBUTESLIST; }

QStringList MaquinaRecordBase::MaquinaPKAttributesList() { return MAQUINAPKATTRIBUTESLIST; }

QString MaquinaRecordBase::MaquinaPKAutoIncrementAttribute() { return MAQUINAPKAUTOINCREMENTATTRIBUTE; }

QStringList MaquinaRecordBase::MaquinaDateTimeAttributesList() { return MAQUINADATETIMEATTRIBUTESLIST; }

QStringList MaquinaRecordBase::getAttributesList()
{
return MAQUINAATTRIBUTESLIST;
}

QStringList MaquinaRecordBase::getPKAttributesList()
{
return MAQUINAPKATTRIBUTESLIST;
}

QStringList MaquinaRecordBase::getPKAutoIncrementAttributesList()
{
return QStringList() << MAQUINAPKAUTOINCREMENTATTRIBUTE;
}

QStringList MaquinaRecordBase::getDateTimeAttributesList()
{
return MAQUINADATETIMEATTRIBUTESLIST;
}



QStringList MaquinaRecordBase::LugarFAttributes()
{
	return QStringList() << "Lugar_idLugar";
}



RecordBase *MaquinaRecordBase::getLastChildDefaultRecord() { return this; }





QString MaquinaRecordBase::idMaquinaProperty() { return "idMaquina"; }

QString MaquinaRecordBase::IpProperty() { return "Ip"; }

QString MaquinaRecordBase::Lugar_idLugarProperty() { return "Lugar_idLugar"; }



/*! Esta función reimplementa operator=().

  Asigna \a record a este MaquinaRecordBase.
*/
MaquinaRecordBase& MaquinaRecordBase::operator=(const MaquinaRecordBase& record)
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

