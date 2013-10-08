#include "editoriallibrorecordbase.h"

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
EditorialLibroRecordBase::EditorialLibroRecordBase(QObject *qparent,
							 RecordBase *rparent,
							 QSqlDatabase db):
RecordSimpleBase(qparent,rparent,db)
{
	TABLENAME="EditorialLibro";
	
	ISBACKUPRECORUSELOCALATT=false;
	BACKUPRECORD = new EditorialLibroRecordBase(false,qparent,rparent,db);

	init();
	initValues();
}

//!Constructor copia.
EditorialLibroRecordBase::EditorialLibroRecordBase(const EditorialLibroRecordBase &other):
RecordSimpleBase(other.QPARENT,other.PARENT,other.DB)
{
	init();

	foreach ( QString att, EDITORIALLIBROATTRIBUTESLIST )
		setProperty( att.toLocal8Bit(),
					other.property( att.toLocal8Bit() ));

	if ( other.TABLENAME == "EditorialLibro" )
	{
		TABLENAME = other.TABLENAME;
		
		ISBACKUPRECORUSELOCALATT = false; //este es el papa mayor, aqui si va
		BACKUPRECORD = new EditorialLibroRecordBase(false,other.QPARENT,other.PARENT,other.DB);
	}
}

EditorialLibroRecordBase::EditorialLibroRecordBase(bool conf,
							   QObject *qparent,
							   RecordBase *rparent,
							   QSqlDatabase db):
	RecordSimpleBase(qparent,rparent,db) //todos los hijos van asi
{
	if ( ! conf )
	{
		//es false, Entonces es la copia
		TABLENAME="EditorialLibro";
		ISBACKUPRECORUSELOCALATT = true;
		BACKUPRECORD=NULL;
	}

	

	init();
	initValues();
}

EditorialLibroRecordBase::~EditorialLibroRecordBase()
{}

//! Inicializa los registros foráneos.
void EditorialLibroRecordBase::init()
{
	REDITORIAL_ = NULL;
RLIBRO_ = NULL;


	lstTables.prepend("EditorialLibro");

	EDITORIALLIBROATTRIBUTESLIST << "id"
<< "Editorial_id"
<< "Libro_id";
	EDITORIALLIBROPKATTRIBUTESLIST << "id";
	EDITORIALLIBRODATETIMEATTRIBUTESLIST  = QStringList();;
	EDITORIALLIBROPKAUTOINCREMENTATTRIBUTE = "id";
}

//! Inicializa los atributos con tipos primitivos
void EditorialLibroRecordBase::initValues()
{
	ID=0;
EDITORIAL_ID=0;
LIBRO_ID=0;

}

void EditorialLibroRecordBase::setRecordEnabledBackup(bool enabled)
{
	enabledRecordBackup=enabled;
	
	if ( REDITORIAL_ != NULL )
		REDITORIAL_->setRecordEnabledBackup(enabled);
if ( RLIBRO_ != NULL )
		RLIBRO_->setRecordEnabledBackup(enabled);

}

RecordBase *EditorialLibroRecordBase::getBackUpRecord() { return BACKUPRECORD; }

//set nuevo valor para un campo

void EditorialLibroRecordBase::setId(int id)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		ID=id;
	else
	{
		addAttributeInsertUpdate("id");
		getBackUpRecord()->setProperty( "id",id );
	}
}

void EditorialLibroRecordBase::setEditorial_id(int Editorial_id)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		EDITORIAL_ID=Editorial_id;
	else
	{
		addAttributeInsertUpdate("Editorial_id");
		getBackUpRecord()->setProperty( "Editorial_id",Editorial_id );
	}
}

void EditorialLibroRecordBase::setLibro_id(int Libro_id)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		LIBRO_ID=Libro_id;
	else
	{
		addAttributeInsertUpdate("Libro_id");
		getBackUpRecord()->setProperty( "Libro_id",Libro_id );
	}
}



void EditorialLibroRecordBase::setREditorial_(EditorialRecordBase* r)
{
	if( REDITORIAL_ != NULL )
		delete REDITORIAL_;
	REDITORIAL_=r;
	setEditorial_id( r->id() );
}

void EditorialLibroRecordBase::setPREditorial_(RecordBase *pr)
{
	setREditorial_((EditorialRecordBase*)pr);
}

void EditorialLibroRecordBase::setRLibro_(LibroRecordBase* r)
{
	if( RLIBRO_ != NULL )
		delete RLIBRO_;
	RLIBRO_=r;
	setLibro_id( r->id() );
}

void EditorialLibroRecordBase::setPRLibro_(RecordBase *pr)
{
	setRLibro_((LibroRecordBase*)pr);
}



//get de los campos, si hay valor nuevo ese regresa, si no el normal

int EditorialLibroRecordBase::id()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("id"))
		return ID;
	else
		return getBackUpRecord()->property( "id" ).toInt();
}

int EditorialLibroRecordBase::Editorial_id()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("Editorial_id"))
		return EDITORIAL_ID;
	else
		return getBackUpRecord()->property( "Editorial_id" ).toInt();
}

int EditorialLibroRecordBase::Libro_id()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("Libro_id"))
		return LIBRO_ID;
	else
		return getBackUpRecord()->property( "Libro_id" ).toInt();
}



EditorialRecordBase *EditorialLibroRecordBase::REditorial_()
{
	if ( REDITORIAL_ == NULL )
	{
		REDITORIAL_=new EditorialRecordBase(this,this,DB);
		REDITORIAL_->setRecordEnabledBackup(enabledRecordBackup);

		connect( REDITORIAL_,SIGNAL(hasValuesWithOutSave(bool,RecordBase*)),
			this, SIGNAL(hasValuesWithOutSave(bool,RecordBase*)));
	}

	return REDITORIAL_;
}

LibroRecordBase *EditorialLibroRecordBase::RLibro_()
{
	if ( RLIBRO_ == NULL )
	{
		RLIBRO_=new LibroRecordBase(this,this,DB);
		RLIBRO_->setRecordEnabledBackup(enabledRecordBackup);

		connect( RLIBRO_,SIGNAL(hasValuesWithOutSave(bool,RecordBase*)),
			this, SIGNAL(hasValuesWithOutSave(bool,RecordBase*)));
	}

	return RLIBRO_;
}



//!Limpia los atributos
void EditorialLibroRecordBase::clear()
{
	

	//limpiando no primitivos
	

	//limpiando foraneas
	if ( REDITORIAL_ != NULL )
	REDITORIAL_->clear();
if ( RLIBRO_ != NULL )
	RLIBRO_->clear();

}

void EditorialLibroRecordBase::revert()
{
	RecordBase::revert();

	if ( REDITORIAL_ != NULL )
	REDITORIAL_->revert();
if ( RLIBRO_ != NULL )
	RLIBRO_->revert();

}

QStringList EditorialLibroRecordBase::EditorialLibroAttributesList() { return EDITORIALLIBROATTRIBUTESLIST; }

QStringList EditorialLibroRecordBase::EditorialLibroPKAttributesList() { return EDITORIALLIBROPKATTRIBUTESLIST; }

QString EditorialLibroRecordBase::EditorialLibroPKAutoIncrementAttribute() { return EDITORIALLIBROPKAUTOINCREMENTATTRIBUTE; }

QStringList EditorialLibroRecordBase::EditorialLibroDateTimeAttributesList() { return EDITORIALLIBRODATETIMEATTRIBUTESLIST; }

QStringList EditorialLibroRecordBase::getAttributesList()
{
return EDITORIALLIBROATTRIBUTESLIST;
}

QStringList EditorialLibroRecordBase::getPKAttributesList()
{
return EDITORIALLIBROPKATTRIBUTESLIST;
}

QStringList EditorialLibroRecordBase::getPKAutoIncrementAttributesList()
{
return QStringList() << EDITORIALLIBROPKAUTOINCREMENTATTRIBUTE;
}

QStringList EditorialLibroRecordBase::getDateTimeAttributesList()
{
return EDITORIALLIBRODATETIMEATTRIBUTESLIST;
}



QStringList EditorialLibroRecordBase::EditorialFAttributes()
{
	return QStringList() << "Editorial_id";
}

QStringList EditorialLibroRecordBase::LibroFAttributes()
{
	return QStringList() << "Libro_id";
}



RecordBase *EditorialLibroRecordBase::getLastChildDefaultRecord() { return this; }





QString EditorialLibroRecordBase::idProperty() { return "id"; }

QString EditorialLibroRecordBase::Editorial_idProperty() { return "Editorial_id"; }

QString EditorialLibroRecordBase::Libro_idProperty() { return "Libro_id"; }



/*! Esta función reimplementa operator=().

  Asigna \a record a este EditorialLibroRecordBase.
*/
EditorialLibroRecordBase& EditorialLibroRecordBase::operator=(const EditorialLibroRecordBase& record)
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

