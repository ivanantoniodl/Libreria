#include "permisorecordbase.h"

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
PermisoRecordBase::PermisoRecordBase(QObject *qparent,
							 RecordBase *rparent,
							 QSqlDatabase db):
RecordSimpleBase(qparent,rparent,db)
{
	TABLENAME="Permiso";
	
	ISBACKUPRECORUSELOCALATT=false;
	BACKUPRECORD = new PermisoRecordBase(false,qparent,rparent,db);

	init();
	initValues();
}

//!Constructor copia.
PermisoRecordBase::PermisoRecordBase(const PermisoRecordBase &other):
RecordSimpleBase(other.QPARENT,other.PARENT,other.DB)
{
	init();

	foreach ( QString att, PERMISOATTRIBUTESLIST )
		setProperty( att.toLocal8Bit(),
					other.property( att.toLocal8Bit() ));

	if ( other.TABLENAME == "Permiso" )
	{
		TABLENAME = other.TABLENAME;
		
		ISBACKUPRECORUSELOCALATT = false; //este es el papa mayor, aqui si va
		BACKUPRECORD = new PermisoRecordBase(false,other.QPARENT,other.PARENT,other.DB);
	}
}

PermisoRecordBase::PermisoRecordBase(bool conf,
							   QObject *qparent,
							   RecordBase *rparent,
							   QSqlDatabase db):
	RecordSimpleBase(qparent,rparent,db) //todos los hijos van asi
{
	if ( ! conf )
	{
		//es false, Entonces es la copia
		TABLENAME="Permiso";
		ISBACKUPRECORUSELOCALATT = true;
		BACKUPRECORD=NULL;
	}

	

	init();
	initValues();
}

PermisoRecordBase::~PermisoRecordBase()
{}

//! Inicializa los registros foráneos.
void PermisoRecordBase::init()
{
	RGRUPOPERMISO_ = NULL;


	lstTables.prepend("Permiso");

	PERMISOATTRIBUTESLIST << "idPermiso"
<< "GrupoPermiso_idGrupoPermiso"
<< "Formulario"
<< "Etiqueta";
	PERMISOPKATTRIBUTESLIST << "idPermiso";
	PERMISODATETIMEATTRIBUTESLIST  = QStringList();;
	PERMISOPKAUTOINCREMENTATTRIBUTE = "idPermiso";
}

//! Inicializa los atributos con tipos primitivos
void PermisoRecordBase::initValues()
{
	IDPERMISO=0;
GRUPOPERMISO_IDGRUPOPERMISO=0;

}

void PermisoRecordBase::setRecordEnabledBackup(bool enabled)
{
	enabledRecordBackup=enabled;
	
	if ( RGRUPOPERMISO_ != NULL )
		RGRUPOPERMISO_->setRecordEnabledBackup(enabled);

}

RecordBase *PermisoRecordBase::getBackUpRecord() { return BACKUPRECORD; }

//set nuevo valor para un campo

void PermisoRecordBase::setIdPermiso(int idPermiso)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		IDPERMISO=idPermiso;
	else
	{
		addAttributeInsertUpdate("idPermiso");
		getBackUpRecord()->setProperty( "idPermiso",idPermiso );
	}
}

void PermisoRecordBase::setGrupoPermiso_idGrupoPermiso(int GrupoPermiso_idGrupoPermiso)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		GRUPOPERMISO_IDGRUPOPERMISO=GrupoPermiso_idGrupoPermiso;
	else
	{
		addAttributeInsertUpdate("GrupoPermiso_idGrupoPermiso");
		getBackUpRecord()->setProperty( "GrupoPermiso_idGrupoPermiso",GrupoPermiso_idGrupoPermiso );
	}
}

void PermisoRecordBase::setFormulario(QString Formulario)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		FORMULARIO=Formulario;
	else
	{
		addAttributeInsertUpdate("Formulario");
		getBackUpRecord()->setProperty( "Formulario",Formulario );
	}
}

void PermisoRecordBase::setEtiqueta(QString Etiqueta)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		ETIQUETA=Etiqueta;
	else
	{
		addAttributeInsertUpdate("Etiqueta");
		getBackUpRecord()->setProperty( "Etiqueta",Etiqueta );
	}
}



void PermisoRecordBase::setRGrupoPermiso_(GrupoPermisoRecordBase* r)
{
	if( RGRUPOPERMISO_ != NULL )
		delete RGRUPOPERMISO_;
	RGRUPOPERMISO_=r;
	setGrupoPermiso_idGrupoPermiso( r->idGrupoPermiso() );
}

void PermisoRecordBase::setPRGrupoPermiso_(RecordBase *pr)
{
	setRGrupoPermiso_((GrupoPermisoRecordBase*)pr);
}



//get de los campos, si hay valor nuevo ese regresa, si no el normal

int PermisoRecordBase::idPermiso()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("idPermiso"))
		return IDPERMISO;
	else
		return getBackUpRecord()->property( "idPermiso" ).toInt();
}

int PermisoRecordBase::GrupoPermiso_idGrupoPermiso()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("GrupoPermiso_idGrupoPermiso"))
		return GRUPOPERMISO_IDGRUPOPERMISO;
	else
		return getBackUpRecord()->property( "GrupoPermiso_idGrupoPermiso" ).toInt();
}

QString PermisoRecordBase::Formulario()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("Formulario"))
		return FORMULARIO;
	else
		return getBackUpRecord()->property( "Formulario" ).toString();
}

QString PermisoRecordBase::Etiqueta()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("Etiqueta"))
		return ETIQUETA;
	else
		return getBackUpRecord()->property( "Etiqueta" ).toString();
}



GrupoPermisoRecordBase *PermisoRecordBase::RGrupoPermiso_()
{
	if ( RGRUPOPERMISO_ == NULL )
	{
		RGRUPOPERMISO_=new GrupoPermisoRecordBase(this,this,DB);
		RGRUPOPERMISO_->setRecordEnabledBackup(enabledRecordBackup);

		connect( RGRUPOPERMISO_,SIGNAL(hasValuesWithOutSave(bool,RecordBase*)),
			this, SIGNAL(hasValuesWithOutSave(bool,RecordBase*)));
	}

	return RGRUPOPERMISO_;
}



//!Limpia los atributos
void PermisoRecordBase::clear()
{
	

	//limpiando no primitivos
	FORMULARIO.clear();
ETIQUETA.clear();


	//limpiando foraneas
	if ( RGRUPOPERMISO_ != NULL )
	RGRUPOPERMISO_->clear();

}

void PermisoRecordBase::revert()
{
	RecordBase::revert();

	if ( RGRUPOPERMISO_ != NULL )
	RGRUPOPERMISO_->revert();

}

QStringList PermisoRecordBase::PermisoAttributesList() { return PERMISOATTRIBUTESLIST; }

QStringList PermisoRecordBase::PermisoPKAttributesList() { return PERMISOPKATTRIBUTESLIST; }

QString PermisoRecordBase::PermisoPKAutoIncrementAttribute() { return PERMISOPKAUTOINCREMENTATTRIBUTE; }

QStringList PermisoRecordBase::PermisoDateTimeAttributesList() { return PERMISODATETIMEATTRIBUTESLIST; }

QStringList PermisoRecordBase::getAttributesList()
{
return PERMISOATTRIBUTESLIST;
}

QStringList PermisoRecordBase::getPKAttributesList()
{
return PERMISOPKATTRIBUTESLIST;
}

QStringList PermisoRecordBase::getPKAutoIncrementAttributesList()
{
return QStringList() << PERMISOPKAUTOINCREMENTATTRIBUTE;
}

QStringList PermisoRecordBase::getDateTimeAttributesList()
{
return PERMISODATETIMEATTRIBUTESLIST;
}



QStringList PermisoRecordBase::GrupoPermisoFAttributes()
{
	return QStringList() << "GrupoPermiso_idGrupoPermiso";
}



RecordBase *PermisoRecordBase::getLastChildDefaultRecord() { return this; }





QString PermisoRecordBase::idPermisoProperty() { return "idPermiso"; }

QString PermisoRecordBase::GrupoPermiso_idGrupoPermisoProperty() { return "GrupoPermiso_idGrupoPermiso"; }

QString PermisoRecordBase::FormularioProperty() { return "Formulario"; }

QString PermisoRecordBase::EtiquetaProperty() { return "Etiqueta"; }



/*! Esta función reimplementa operator=().

  Asigna \a record a este PermisoRecordBase.
*/
PermisoRecordBase& PermisoRecordBase::operator=(const PermisoRecordBase& record)
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

