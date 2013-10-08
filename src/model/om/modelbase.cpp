#include "modelbase.h"
#include "tsqlgenerator.h"

ModelBase::ModelBase(QObject *parent,
                     QSqlDatabase db) :
    QAbstractTableModel(parent), Parent(parent), DB(db)
{
    customColumns=0;
    limit=50;
    offset=0;
    consConf=-1;
    firstQuery=true;
    fastConfiguration=false;
    testingCustomColumns=false;
    navigationEnabled=true;
    query=new QSqlQuery(db);
}

ModelBase::~ModelBase()
{
    delete query;
    clearData();
    qDeleteAll(lstHorizontalHeaderData);
    lstHorizontalHeaderData.clear();
}

//protected

/*!Devulve el tamaño de la consulta.
\param query Consulta
\return Tamaño de filas de la consulta

\warning se tiene que usar al ejecutar, sin configurar posicion
*/
int ModelBase::querySize(QSqlQuery query)
{
    if ( DB.driver()->hasFeature( QSqlDriver::QuerySize ) )
        return query.size();
    else
    {
        int size=0;
        while ( query.next() )
            size++;
        return size;
    }
}

/*! Devuleve el atributo de un registro.

\param r Registro a consultar.
\param colum Número de columna, el orden de las columnas es el orden como fue configurada la consulta.
Ejemplo
Columna 0: idPersona
Columna 1: Nombre
Columna 2: Lugar.Nombre (Table Lugar atributo Nombre)
\return Valor del atributo.
*/
QVariant ModelBase::getRecordValue(RecordBase *r,int column) const
{
    if ( testingCustomColumns )
    {
        QString str("usingGetRecordValueBase=true!@#$");
        QVariant v;
        v.setValue(str);
        return v;
    }

    if ( column >= lstCIV.size() || column < 0 )
        return QVariant();

    confInsertValue *civ=lstCIV.at(column);

    r=r->getRecordFromPath( civ->lstRecord );
    return r->property(civ->att.toLocal8Bit());
}

void ModelBase::clearData()
{
    qDeleteAll(lstRecord);
    lstRecord.clear();
}

void ModelBase::clearQuery()
{
    tsqlGenerator()->clear();
    //sqlGenerator->clear();
    lstCIV.clear();
    if ( usingGetRecordValueBase )
        customColumns=0;
    tsqlGenerator()->setTableName(tableName);
    //sqlGenerator->setTableName(tableName); //reinicia sqlGenerator
}

/*! Establece el valor a un atributo de un determinado registro.
Esta función es utilizada para llenar los registros del modelo con el contenido de una consulta.
\param p Registro a establecer valores.
\param iv Ruta de atributo para establecer valor.
\param valor Valor a establecer.
*/
void ModelBase::setAttributeValue(RecordBase* p,confInsertValue *iv,QVariant valor)
{
    QStringList lst=iv->lstRecord; //ruta al atributo a establecer valor

    if ( lst.size() > 0 )
    {
        p=p->getRecordFromPath(iv->lstRecord);

        //llegamos a la otra tabla y establecemos el valor
        p->setProperty(iv->att.toLocal8Bit(),valor);
    }
    else
        p->setProperty(iv->att.toLocal8Bit(),valor);
}

//! Establece que configuración usar para realizar las consultas.
void ModelBase::setConsConf(int c)
{
    consConf=c;
    fastConfiguration=false;
    usingGetRecordValueBase=false;
    testingCustomColumns=true;

    /*verificando la catidad de columnas personalizadas en getRecordValue el modelo heredado.
    si en este se llama a getRecordValue de la base entonces se establece la como cantidad de columnas como la personalizada, de lo contrario se calcula cuantas hay*/

    bool fallo=true;

    for ( int c=0; c<200; c++ ) //maximo de 200 columnas por si no establecieron el final
    {
        QVariant v= getRecordValue(defaultRecordBase(),c);

        QString str=v.toString();
        if ( str.compare("usingGetRecordValueBase=true!@#$",Qt::CaseSensitive) == 0 )
            usingGetRecordValueBase=true;

        if ( usingGetRecordValueBase )
        {
            //no se esta personalizando la salida, se queda customColumns como esta
            fallo=false;
            break;
        }

        //si paso es porque si esta configurado en el heredado.

        //verificando si el variant que se devolvio es nulo, si lo es terminamos la consulta
        //si no pusieron un variant nulo seguira hasta 200, que sera la cantidad de columnas personalizadas

        if ( ! v.isValid() )
        {
            //usingGetRecordValueBase esta en falso, se utilizara la vista personalizada cuando se ejecute data()
            fallo=false;
            customColumns=c;
            break;
        }
    }

    if ( fallo )
    {
        qDebug() << "Modelo " << tableName << ": Mala configuracion de vista personalizada en getRecordValue(), asegurece de que antes de terminar la funcion exita 'return QVariant()', no se utilizara la vista personalizada.";
        usingGetRecordValueBase=true;
    }

    testingCustomColumns=false;
}

void ModelBase::setRecordEnabledBackup(RecordBase *record,bool enabled)
{
    record->setRecordEnabledBackup(enabled);
}

/*! Devuelve como esta configurado la consulta.
\return Configuración de consulta.
*/
int ModelBase::getConsConf() const { return consConf; }

/*! Habilita o deshabilita la navegación en el modelo.
\param nh \a true habilita la navegación, \a false deshabilita la nevegación.
*/
void ModelBase::setEnableNavigation(bool nh) { navigationEnabled=nh; }

//public
//modelo

/*! Devuelve el número de filas (registros) del modelo.
\param parent Padre del item, al ser un modelo que representa una tabla este parametro es por defecto.
\return Número de filas (registros).

Reimplementado de QAbstractItemMode::rowCount().
*/
int ModelBase::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return lstRecord.size();
}

/*! Devuelve el número de columnas (atributos) del modelo.
\param parent Padre del item, al ser un modelo que representa una tabla este parametro es por defecto.
\return Número de columnas (atributos).

Reimplementado de QAbstractItemMode::columnCount().
*/
int ModelBase::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    if ( fastConfiguration )
    {
        if ( customColumns > 0 )
            return customColumns;
        else
            return lstCIV.size();
    }
    else
        return customColumns;
}

/*! Devuelve el valor de un elemento de modelo.
Este método sirve para devolver el valor de un elemento de modelo por medio de un \a index que contiene el número de fila y columna, es utilizada por los widgets de vista para llenarse con los datos del modelo o por el que necesite obtener esos datos de esta manera.
\param index Indice de modelo a consultar.
\param role Rol.
\return Valor del atributo.

Reimplementado de QAbstractItemMode::data().
*/
QVariant ModelBase::data(const QModelIndex &index, int role) const
{
    if (index.isValid())
    {
        switch (role)
        {
            case Qt::EditRole:
            case Qt::DisplayRole :
            {
                if ( fastConfiguration || usingGetRecordValueBase )
                    return ModelBase::getRecordValue( lstRecord.at(index.row()),
                                                       index.column() );
                else
                    return getRecordValue(lstRecord.at(index.row()),
                                          index.column());
            }
//			case Qt::DecorationRole :
//			{
//				if ( index.column() == 0 )
//					return ( listaItems[r]->icono() );
//				break;
//			}
        };
    }
    return QVariant();
}

bool ModelBase::setData(const QModelIndex &index,
                        const QVariant &value,
                        int role)
{
    if ( customColumns > 0 )
        return false;

    if (index.isValid() && role == Qt::EditRole)
    {
        confInsertValue* civ = lstCIV.at( index.column() );
        RecordBase *record = lstRecord.at( index.row() );

        setAttributeValue( record,civ,value );

        emit dataChanged(index, index);
        return true;
    }
    return false;
}

QVariant ModelBase::headerData(int section,
                                  Qt::Orientation orientation,
                                  int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if ( orientation == Qt::Vertical )
        return section+1;
    if ( section >= lstCIV.size() )
        return QVariant();

    foreach ( horizontalHeaderData *h, lstHorizontalHeaderData )
    {
        if ( h->section == section )
            return h->value;
    }

    return lstCIV.at( section )->att;
}

bool ModelBase::setHeaderData(int section,
                   Qt::Orientation orientation,
                   const QVariant & value,
                   int role)
{
    if ( ( role != Qt::DisplayRole && role != Qt::EditRole ) || orientation != Qt::Horizontal)
        return false;

    foreach ( horizontalHeaderData *h, lstHorizontalHeaderData )
    {
        if ( h->section == section )
        {
            h->value = value;
            return true;
        }
    }

    horizontalHeaderData *h = new horizontalHeaderData;
    h->section=section;
    h->value=value;
    lstHorizontalHeaderData.append(h);
    return true;
}

/*! Devuelve las banderas de un elemento de modelo.
\param index Indice de modelo a consultar.
\return Banderas del elemento.

Reimplementado de QAbstractItemMode::flags().
*/
Qt::ItemFlags ModelBase::flags(const QModelIndex &index) const
{
    if (!index.isValid())
             return Qt::ItemIsEnabled;

    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    flags |= Qt::ItemIsSelectable;
    if ( customColumns == 0 )
        flags |= Qt::ItemIsEditable;
    return flags;
}

TSqlError ModelBase::submitAll()
{
    TSqlError error;
    DB.transaction();
    foreach ( RecordBase *record, lstRecordValuesWithOutSave )
    {
        error.RecordMessage = "ModelBase: SubmitAll: Error";
        error = record->update();
        if ( error.isError() )
        {
            DB.rollback();
            return error;
        }
    }
    lstRecordValuesWithOutSave.clear();
    DB.commit();
    return error;
}

bool ModelBase::submit()
{
    TSqlError error;
    error = submitAll();
    if ( error.isError() )
        return false;

    return true;
}

void ModelBase::revert()
{
    beginResetModel();

    foreach ( RecordBase *record, lstRecordValuesWithOutSave )
        record->revert();
    lstRecordValuesWithOutSave.clear();

    endResetModel();
}

//consulta

/*! Devuelve el nombre de la tabla.
\return Nombre de la tabla que representa.
*/
QString ModelBase::getTableName()
{
    return tableName;
}

/*! Devuelve el código SQL de la última consulta realizada
\return Consulta SQL
*/
QString ModelBase::lastQuery() { return txtquery; }

/*! Actualiza el contenido del modelo.
Este método actualiza el contenido del modelo realizando una consulta a la base de datos.
\return Estado de la consulta.
*/
TSqlError ModelBase::select()
{
    //verificamos que este configurado la consulta
    if (lstCIV.size() == 0)
    {
        if ( ! fastConfiguration )
        {
            configureInternalSelectQuery();
            if ( usingGetRecordValueBase )
                customColumns=tsqlGenerator()->getLstCIV().size();
        }
        lstCIV=tsqlGenerator()->getLstCIV();
    }

    TSqlError error;
    if ( lstCIV.size() == 0 )
    {
        error.ModelMessage = "No hay campos para seleccionar en la tabla tableName\nConfigure la consulta en 'configurarConsulta'";
        return error;
    }

    //si es primera consulta se resetea offset
    if ( firstQuery )
        offset=0;

    //generamos la consultas
    clearData();
    if ( navigationEnabled )
    {
        if ( firstQuery )
        {
            QSqlQuery query( tsqlGenerator()->getSelectQuery(false));
            completeNavigationTotalRows=query.size();
        }
        tsqlGenerator()->setLimit(limit+1);
        tsqlGenerator()->setOffset(offset);
    }
    txtquery=tsqlGenerator()->getSelectQuery(navigationEnabled);
    firstQuery = false;

    qDebug() << txtquery;

    query->exec( txtquery );

    error.ModelMessage = "Select: Error al seleccionar los atributos";
    error.ModelQuery = txtquery;
    error = query->lastError();

    if ( error.type() != QSqlError::NoError )
        return error;

    emit beginResetModelSignal();

    beginResetModel();

    actualQuerySize=querySize(*query);

    //navegacion
    if ( navigationEnabled )
    {
        emit navPrevious( ! (offset == 0) );
        emit navNext( actualQuerySize > limit );
    }

    //llenar los registros del modelo
    addSelectQueryToRecords(*query);

    //limpiamos la lista de cambios en los registros recien ingresados
    //ya que al ponerles su valor se establecio como modificados
    foreach ( RecordBase *record, lstRecord )
        record->lstAttInsertUpdate.clear();

    endResetModel(); //este emite resetModel()

    emit endResetModelSignal();

    return error;
}

void ModelBase::resetModel()
{
    beginResetModel();
    endResetModel();
}

/*! Devuelve el registro de la posición \a pos en el modelo.
\param pos Indice.
\return Registro.
*/
RecordBase* ModelBase::getRecord(int pos) const
{
    if ( pos >= lstRecord.size() || pos < 0 )
        return NULL;

    return lstRecord.at(pos);
}

void ModelBase::resetSelectQuery()
{
    firstQuery=true;
}

int ModelBase::modelSize()
{
    return lstRecord.size();
}

//navegacion

/*! Establece el limite de consulta.
\param l Limite de consulta.
*/
void ModelBase::setSelectQueryLimit(int l)
{
    if ( l < 1 )
        return;
    limit=l;
}

//slots

/*! Agrega un atributo a la consulta
El atributo a agregrar consiste en el atributo y la ruta que se necesita para llegar a el. Si el atributo esta en la misma tabla solamente será el nombre del atributo, si el atributo esta en otra tabla será el nombre de las tablas que se deben pasar separadas por comas hasta llegar al atributo.

Ejemplo:

Tabla: Persona
Atributos: idPersona, Nombre, Direccion, Lugar_idLugar

Tabla: Lugar
Atributos: idLugar, Tipo_idTipo, Nombre

Tabla: Tipo
Atributos: Nombre

Si se agrega el atributo Nombre de Persona:

c=Nombre

Si se agrega el atributo Nombre de Lugar:

c=Lugar,Nombre

Si se agrega el atributo Nombre de Tipo:

c=Lugar,Tipo,Nombre

Al agregar el atributo se configura sqlGenerator para que se genere el código SQL cuando se necesite.

\param c Atributo a agregar.
*/
//void ModelBase::addAttributeToSelect(QString c)
//{
//	QStringList lstConsulta=c.split(",",QString::SkipEmptyParts);

//	if ( lstConsulta.size() > 1 )
//	{
//		//agregando tabla a la consulta
//		QString ultimo=tableName;
//		RecordBase *ultimoRec=defaultRecordBase();

//		for ( int con=0; con<lstConsulta.size()-1; con++ )
//		{
//			QString nt=lstConsulta.at(con); //nueva tabla

//			ultimoRec=ultimoRec->property( QString("R"+nt+"_").toLocal8Bit() ).value<RecordBase*>(); //nos pasamos a la otra tabla

//			sqlGenerator->addTable(nt);
//			foreach( QString pk, ultimoRec->getPKAttributesList() )
//				sqlGenerator->addRelation(ultimo,nt+"_"+pk,
//									  nt,pk);
//			ultimo=nt;
//		}

//		//agregando el campo a consulta
//		sqlGenerator->addSelectAttribute(lstConsulta.at(lstConsulta.size()-2),
//									 lstConsulta.last());

//		//agregando configuracion de consulta al modelo
//		confInsertValue *civ=new confInsertValue;
//		civ->att=lstConsulta.last();
//		lstConsulta.removeLast();
//		civ->lstRecord=lstConsulta;
//		lstCIV.append(civ);
//	}
//	else
//	{
//		//agregando el campo a consulta
//		sqlGenerator->addSelectAttribute(lstConsulta.last());

//		//agregando configuracion de consulta al modelo
//		confInsertValue *civ=new confInsertValue;
//		civ->att=lstConsulta.last();
//		lstCIV.append(civ);
//	}
//	if ( usingGetRecordValueBase )
//		customColumns++;
//}

//navegacion

//!Aumenta offset y realiza la consulta para que se obtengan las siguientes filas de la base de datos.
void ModelBase::navToNext()
{
    int newOffset = offset+limit;
    if ( navigationEnabled && newOffset<completeNavigationTotalRows )
    {
        offset=newOffset;
        select();
    }
}

//!Disminuye offset y realiza la consulta para que se obtengan las filas anteriores de la base de datos.
void ModelBase::navToPrevious()
{
    int newOffset = offset-limit;
    if ( navigationEnabled && newOffset >= 0 )
    {
        offset-=limit;
        select();
    }
}

void ModelBase::navToFirst()
{
    if ( navigationEnabled )
    {
        offset=0;
        select();
    }
}

void ModelBase::navToLast()
{
    if ( navigationEnabled )
    {
        offset=completeNavigationTotalRows-limit;
        select();
    }
}

void ModelBase::addRecord(RecordBase* record)
{
    connect( record,SIGNAL(hasValuesWithOutSave(bool,RecordBase*)),
            this,SLOT(record_hasRecordsWithOutSave(bool,RecordBase*)));
    lstRecord.append(record);
}

void ModelBase::record_hasRecordsWithOutSave(bool hasValues,RecordBase* record)
{
    if ( hasValues )
    {
        if ( ! lstRecordValuesWithOutSave.contains(record) )
            lstRecordValuesWithOutSave.append(record);
    }
    else
        lstRecordValuesWithOutSave.removeAt( lstRecordValuesWithOutSave.indexOf(record) );

    emit hasRecordsWithOutSave( lstRecordValuesWithOutSave.size() > 0 ? true : false );
}
