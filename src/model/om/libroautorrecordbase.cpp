#include "libroautorrecordbase.h"

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
LibroAutorRecordBase::LibroAutorRecordBase(QObject *qparent,
							 RecordBase *rparent,
							 QSqlDatabase db):
RecordSimpleBase(qparent,rparent,db)
{
	TABLENAME="LibroAutor";
	
	ISBACKUPRECORUSELOCALATT=false;
	BACKUPRECORD = new LibroAutorRecordBase(false,qparent,rparent,db);

	init();
	initValues();
}

//!Constructor copia.
LibroAutorRecordBase::LibroAutorRecordBase(const LibroAutorRecordBase &other):
RecordSimpleBase(other.QPARENT,other.PARENT,other.DB)
{
	init();

	foreach ( QString att, LIBROAUTORATTRIBUTESLIST )
		setProperty( att.toLocal8Bit(),
					other.property( att.toLocal8Bit() ));

	if ( other.TABLENAME == "LibroAutor" )
	{
		TABLENAME = other.TABLENAME;
		
		ISBACKUPRECORUSELOCALATT = false; //este es el papa mayor, aqui si va
		BACKUPRECORD = new LibroAutorRecordBase(false,other.QPARENT,other.PARENT,other.DB);
	}
}

LibroAutorRecordBase::LibroAutorRecordBase(bool conf,
							   QObject *qparent,
							   RecordBase *rparent,
							   QSqlDatabase db):
	RecordSimpleBase(qparent,rparent,db) //todos los hijos van asi
{
	if ( ! conf )
	{
		//es false, Entonces es la copia
		TABLENAME="LibroAutor";
		ISBACKUPRECORUSELOCALATT = true;
		BACKUPRECORD=NULL;
	}

	

	init();
	initValues();
}

LibroAutorRecordBase::~LibroAutorRecordBase()
{}

//! Inicializa los registros foráneos.
void LibroAutorRecordBase::init()
{
	RLIBRO_ = NULL;
RAUTOR_ = NULL;


	lstTables.prepend("LibroAutor");

	LIBROAUTORATTRIBUTESLIST << "id"
<< "Libro_id"
<< "Autor_id";
	LIBROAUTORPKATTRIBUTESLIST << "id";
	LIBROAUTORDATETIMEATTRIBUTESLIST  = QStringList();;
	LIBROAUTORPKAUTOINCREMENTATTRIBUTE = "id";
}

//! Inicializa los atributos con tipos primitivos
void LibroAutorRecordBase::initValues()
{
	ID=0;
LIBRO_ID=0;
AUTOR_ID=0;

}

void LibroAutorRecordBase::setRecordEnabledBackup(bool enabled)
{
	enabledRecordBackup=enabled;
	
	if ( RLIBRO_ != NULL )
		RLIBRO_->setRecordEnabledBackup(enabled);
if ( RAUTOR_ != NULL )
		RAUTOR_->setRecordEnabledBackup(enabled);

}

RecordBase *LibroAutorRecordBase::getBackUpRecord() { return BACKUPRECORD; }

//set nuevo valor para un campo

void LibroAutorRecordBase::setId(int id)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		ID=id;
	else
	{
		addAttributeInsertUpdate("id");
		getBackUpRecord()->setProperty( "id",id );
	}
}

void LibroAutorRecordBase::setLibro_id(int Libro_id)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		LIBRO_ID=Libro_id;
	else
	{
		addAttributeInsertUpdate("Libro_id");
		getBackUpRecord()->setProperty( "Libro_id",Libro_id );
	}
}

void LibroAutorRecordBase::setAutor_id(int Autor_id)
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup )
		AUTOR_ID=Autor_id;
	else
	{
		addAttributeInsertUpdate("Autor_id");
		getBackUpRecord()->setProperty( "Autor_id",Autor_id );
	}
}



void LibroAutorRecordBase::setRLibro_(LibroRecordBase* r)
{
	if( RLIBRO_ != NULL )
		delete RLIBRO_;
	RLIBRO_=r;
	setLibro_id( r->id() );
}

void LibroAutorRecordBase::setPRLibro_(RecordBase *pr)
{
	setRLibro_((LibroRecordBase*)pr);
}

void LibroAutorRecordBase::setRAutor_(AutorRecordBase* r)
{
	if( RAUTOR_ != NULL )
		delete RAUTOR_;
	RAUTOR_=r;
	setAutor_id( r->id() );
}

void LibroAutorRecordBase::setPRAutor_(RecordBase *pr)
{
	setRAutor_((AutorRecordBase*)pr);
}



//get de los campos, si hay valor nuevo ese regresa, si no el normal

int LibroAutorRecordBase::id()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("id"))
		return ID;
	else
		return getBackUpRecord()->property( "id" ).toInt();
}

int LibroAutorRecordBase::Libro_id()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("Libro_id"))
		return LIBRO_ID;
	else
		return getBackUpRecord()->property( "Libro_id" ).toInt();
}

int LibroAutorRecordBase::Autor_id()
{
	if ( ISBACKUPRECORUSELOCALATT || ! enabledRecordBackup || ! lstAttInsertUpdate.contains("Autor_id"))
		return AUTOR_ID;
	else
		return getBackUpRecord()->property( "Autor_id" ).toInt();
}



LibroRecordBase *LibroAutorRecordBase::RLibro_()
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

AutorRecordBase *LibroAutorRecordBase::RAutor_()
{
	if ( RAUTOR_ == NULL )
	{
		RAUTOR_=new AutorRecordBase(this,this,DB);
		RAUTOR_->setRecordEnabledBackup(enabledRecordBackup);

		connect( RAUTOR_,SIGNAL(hasValuesWithOutSave(bool,RecordBase*)),
			this, SIGNAL(hasValuesWithOutSave(bool,RecordBase*)));
	}

	return RAUTOR_;
}



//!Limpia los atributos
void LibroAutorRecordBase::clear()
{
	

	//limpiando no primitivos
	

	//limpiando foraneas
	if ( RLIBRO_ != NULL )
	RLIBRO_->clear();
if ( RAUTOR_ != NULL )
	RAUTOR_->clear();

}

void LibroAutorRecordBase::revert()
{
	RecordBase::revert();

	if ( RLIBRO_ != NULL )
	RLIBRO_->revert();
if ( RAUTOR_ != NULL )
	RAUTOR_->revert();

}

QStringList LibroAutorRecordBase::LibroAutorAttributesList() { return LIBROAUTORATTRIBUTESLIST; }

QStringList LibroAutorRecordBase::LibroAutorPKAttributesList() { return LIBROAUTORPKATTRIBUTESLIST; }

QString LibroAutorRecordBase::LibroAutorPKAutoIncrementAttribute() { return LIBROAUTORPKAUTOINCREMENTATTRIBUTE; }

QStringList LibroAutorRecordBase::LibroAutorDateTimeAttributesList() { return LIBROAUTORDATETIMEATTRIBUTESLIST; }

QStringList LibroAutorRecordBase::getAttributesList()
{
return LIBROAUTORATTRIBUTESLIST;
}

QStringList LibroAutorRecordBase::getPKAttributesList()
{
return LIBROAUTORPKATTRIBUTESLIST;
}

QStringList LibroAutorRecordBase::getPKAutoIncrementAttributesList()
{
return QStringList() << LIBROAUTORPKAUTOINCREMENTATTRIBUTE;
}

QStringList LibroAutorRecordBase::getDateTimeAttributesList()
{
return LIBROAUTORDATETIMEATTRIBUTESLIST;
}



QStringList LibroAutorRecordBase::LibroFAttributes()
{
	return QStringList() << "Libro_id";
}

QStringList LibroAutorRecordBase::AutorFAttributes()
{
	return QStringList() << "Autor_id";
}



RecordBase *LibroAutorRecordBase::getLastChildDefaultRecord() { return this; }





QString LibroAutorRecordBase::idProperty() { return "id"; }

QString LibroAutorRecordBase::Libro_idProperty() { return "Libro_id"; }

QString LibroAutorRecordBase::Autor_idProperty() { return "Autor_id"; }



/*! Esta función reimplementa operator=().

  Asigna \a record a este LibroAutorRecordBase.
*/
LibroAutorRecordBase& LibroAutorRecordBase::operator=(const LibroAutorRecordBase& record)
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

