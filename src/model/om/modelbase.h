#ifndef MODELBASE_H
#define MODELBASE_H

#include <QObject>
#include <QtSql>

#include "recordbase.h"
#include "recordconfigurequerybase.h"
#include "tsqlerror.h"
#include "../qantmv_global.h"

class TSqlGenerator;
class QRecordWidgetMapper;
class QRecordWidgetMapperDialog;
class TListViewModelRecord;
class TComboBoxModelRecord;
class TTableViewModelRecird;

/*!
\class ModelBase
\brief Esta clase provee una interfaz de registro abstracto que puede ser utilizada para heredar nuevos modelos de tablas.

    El funcionamiento de los modelos se describe en la Qt Reference Documentation en el capitulo Model/View Programming.

    En la arquitectura Model/View los modelos son la fuente de datos de los widgets que forman parte de la vista, estos son QTableView, QComboBox, QColumnView y QListView.

    Las clases que heredan de esta deben implementar configureQuery(), addSelectQueryToRecords(QSqlQuery) y defaultRecord().

    Esta clase es la base, por cada tabla se hereda una y de esta otra mas, así que si tenemos la tabla Persona, las clases son:

    ModelBase\n
    PersonaModelBase\n
    PersonaModel

    En PersonaModel se tendrá todo lo necesario y será la que puede editar el usuario para personalizarla. En esta se puede configurar las consultas.

\b Consultas.

    Este modelo provee de la capacidad de configurar una consulta SQL, de ejecutarla y guardar el resultado en una lista de registros heredados de Record, para que a la hora de acceder a los datos se obtengan como registros y no como columnas de datos. Para ello cada sub clase debe tener como miembro una clase hereda de Record y conectar las señales campoDeConsulta() del registro con addAttributeToSelect() del modelo y clearQuery() del registro con cleanSelectQueryAttributes() del modelo, esto se hace para que el modelo pueda configurar la consulta y como se guardarán los resultados dentro de sus registros internos.

\b Ejemplo:

Estan las siguientes tablas:

Tabla: Persona
Atributos: idPersona, Nombre, Direccion, Lugar_idLugar

Tabla: Lugar
Atributos: idLugar, Nombre

Clase Persona heredada de ModelBase:

\code
class PersonaModelBase : public ModelBase
{
Q_OBJECT
protected:
    PersonaRecord r;
\endcode

al ejecutar:

\code
r.setNombre();
r.setDireccion();
r.RLugar_idLugar()->setNombre();
\endcode

el registro r enviará al modelo las señales con los atributos a consultar.
El modelo recibirá:

Nombre\n
Direccion\n
Lugar,Nombre

Para generar el código SQL, ModelBase tiene un miembro de tipo TSqlGenerator y el código que se generaría es el siguiente:

\code
SELECT a.Nombre,b.Direccion,b.Nombre FROM Persona INNER JOIN Lugar b ON a.Lugar_idLugar=b.idLugar LIMIT 51
\endcode

<b>Donde configurar las consultas.</b>

    Las consultas pueden configurarse en dos lugares:

<b>1 Configurando la consulta en el modelo.</b>

    La consulta será configurada en la última clase de modelos de la tabla, mencionando el ejemplo de la tabla Persona, esta configuración se hará en la clase PersonaModel. configureQuery() es implementado para realizar esta tarea de configuración. En este método se indica que configuración es y el código de la consulta.

    Ejemplo:

    \code
    r.clear();
    switch (consConf)
    {
    case Default: //configuración Default
        r.setIdPersona();
        r.setNombre();
        r.setLugar_idLugar();
        r.fLugar_idLugar()->setNombre();
        break;
    }
    \endcode

    Cuando en se ejecute modelUpdate() y no esta configurada la consulta leerá este método, confurará la consulta y la realizará.

    Si se desea personalizar mas la consulta despues de escribir los atributos a consultar se puede usar sqlGenerator.

    Ejemplo:
    \code
    r.clear();
    switch (consConf)
    {
    case Default: //configuración Default
        r.setIdPersona();
        r.setNombre();
        r.setLugar_idLugar();
        r.fLugar_idLugar()->setNombre();
        sqlGenerator->addWhereAttribute("idPersona",1); //Configurando la consulta
        break;
    }
    \endcode

    Cuando alguien consulte del modelo la información se entregará tal y como se configuro.

    Se puede personalizar la manera como el modelo entregará la información, para ellos se edita el método getRecordValue().

    Ejemplo:

\code
    CompraRecord *r=(CompraRecord*)record;
    switch (consConf)
    {
    case (Default): //configuracion Default
        switch (column)
        {
        //example
        case 0:	return r->idCompra();
        case 1: return r->Fecha();
        case 2: return QString::number(r->RLugar_idLugar()->idLugar())+", "+
                r->RLugar_idLugar()->Nombre();
        case 3: return r->RCliente_idCliente()->Apellido()+", "+
                r->RCliente_idCliente()->Nombrw();
        };
        break;
    };
    return QVariant();
\endcode

    En este configuración el modelo mostrará 4 columnas, la tercera mostrará:

    Ejemplo:\n
    1, Guatemala

    la cuarta columna mostrará:

    Ejemplo:\n
    de León, Jose

    Se puede personalizar el nombre de las cabeceras para mostrar en una tabla, esto se hace modificando el método headerData().

    Ejemplo:
    \code
    if (role != Qt::DisplayRole)
        return QVariant();
    if ( orientation == Qt::Vertical )
        return section+1;

    switch (consConf)
    {
    case Default: //configuración Default
        switch ( section )
        {
        //example
        case 0: return "idPersona";
        case 1: return "Nombre";
        case 2: return "idLugar";
        case 3: return "Lugar";
        };
        break;
    };
    return QVariant();
    \endcode

<b>2 Código donde se este usando el módelo</b>

    Esto significa que si dentro del código de un formulario u otro lugar se necesita configurar una consulta se tiene que acceder al registro (Record) por defecto del modelo para configurar la consulta, esto se hace con sqlGenRecord(), al ejecutar este método se configurará el modelo como consulta rápida, significa que ya no ira a configureQuery() para configurar la consulta. Para personalizar la consulta se utiliza el método tsqlGenerator() para acceder al generador de código SQL.

    Ejemplo:
    \code
    PorductoLoteModel *model = new ProductoLoteModel(this);
    model->sqlGenRecord()->setIdProductoLote();
    model->sqlGenRecord()->RProducto_Codigo()->setNombre();
    model->sqlGenRecord()->setFechaIngreso();
    model->sqlGenRecord()->setCosto();
    model->sqlGenRecord()->setExistencia();
    productoLoteModel->tsqlGenerator()->addWhereAttribute("Terminado",false);
    model->select();
    \endcode

    Si se desea reiniciar una consulta para volverla a configurar se puede ejecutar clear() del registro por defecto del modelo, antes de la configuración:

    Ejemplo:

    \code
    model->sqlGenRecord()->clear();
    model->sqlGenRecord()->setIdProductoLote();
    model->sqlGenRecord()->RProducto_Codigo()->setNombre();
    \endcode

<b>Obtención de registros</b>

    Para mostrar el contenido del modelo en un widget de vista se utiliza el método setModel() del mismo, el modelo se encargará de devolver la información necesaria.

    Para obtener los datos como registros se utiliza el método getRecord(int) que nos devuelve un puntero al registro (Record) seleccionado. Podemos saber la cantidad de registros que tiene el modelo con rowCount().

Ejemplo:

\code
model->select();
for ( int c=0; c<model->rowCount(); c++ )
{
    personaRecord *pr = ( PersonaRecord* ) model->getRecord(c);
    qDebug() << pr->Nombre();
    qDebug() << pr->RLugar_idLugar()->Nombre();
}
\endcode

\b Navegación

    Internamente el modelo lleva el control del OFFSET y del LIMIT de la consulta. Cuando se inicia una consulta, \a offset se inicia en 0 y el limite por defecto en 50. Si la consulta sin limite tuviera mas de \a limit número de filas se emite la señal navNext(bool) con valor \true de lo contrario se emite con valor \a false.

    navToNext() aumenta el valor de \a offset a \a offset + \a limit y se realiza la consulta, con ello se obtienen las siguientes \a limit número de filas. Cuando \a offset es igual a 0 significa que no hay filas anteriores por lo tanto se emite la señal navPrevious(bool) con valor \false de lo contrario se emite con valor \true.

    navToPrevious() disminuye el valor de \a offset a \offset - \a limit y se realiza la consulta, con ello se obtienen las anteriores \a limit número de filas.

\warning Esta clase no se usa directamente, se debe heredar.

\warning Por el momento este modelo solo es de lectura.
*/

class QANTMVSHARED_EXPORT ModelBase : public QAbstractTableModel
{
friend class QRecordWidgetMapper;
friend class QRecordWidgetMapperDialog;
friend class TListViewModelRecord;
friend class TComboBoxModelRecord;
friend class TTableViewModelRecord;
Q_OBJECT
private:
    //consulta
    int customColumns;
    int consConf;
    bool usingGetRecordValueBase; //si es true se usa la funcion
    bool testingCustomColumns; //se usa cuando se configura la consulta con setConsConf, ya que se prueba si se esta configurando una vista personalizada en el modelo heredado o no, esto para saber cuantas columnas tendra el modelo a mostrar
    bool navigationEnabled;

    struct horizontalHeaderData
    {
        int section;
        QVariant value;
    };
    QList<horizontalHeaderData*> lstHorizontalHeaderData;

    void addRecord(RecordBase*); //para q qrecordwidgetmapper agregue
    void resetModel();

protected:
    QObject *Parent;
    QSqlDatabase DB;

    //!Lista de registros donde se guarda el resultado de las consultas
    QList<RecordBase*> lstRecord;
    QList<RecordBase*> lstRecordValuesWithOutSave;

    //navegacion
    int limit; //!<Valor del limite de la consulta
    int offset;//!<Valor del offset de la consulta
    long long completeNavigationTotalRows;
    int actualQuerySize;
    bool firstQuery;

    //consulta
    QSqlQuery *query;
    QString tableName;//!<Nombre que representa el nombre de la tabla
    QString txtquery;
    //TSqlGenerator *sqlGenerator;//!<Encargado de generar el código SQL de la consulta
    bool fastConfiguration;

    QList<confInsertValue*> lstCIV;

    //metodos

    //!Configura la consulta
    virtual void configureInternalSelectQuery() = 0;

    virtual TSqlGenerator *tsqlGenerator() = 0;

    //!Devuelve el registro por defecto del modelo
    //virtual RecordConfigureQuery *defaultRecordConfigureQuery() = 0;

    virtual RecordBase *defaultRecordBase() = 0;

    /*!Ingresa el resultado de una consulta a los registros.
    \param query Consulta
    */
    virtual void addSelectQueryToRecords(QSqlQuery query) = 0;

    int querySize(QSqlQuery query);
    virtual QVariant getRecordValue(RecordBase*,int column=-1) const;
    void setAttributeValue(RecordBase*,confInsertValue*,QVariant);

    void setConsConf(int);

    void setRecordEnabledBackup(RecordBase*,bool);

public:
    explicit ModelBase(QObject *parent = 0,
                       QSqlDatabase db = QSqlDatabase::database());
    ~ModelBase();

    //modelo
    int rowCount(const QModelIndex &parent=QModelIndex()) const;
    int columnCount(const QModelIndex &parent=QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role)const;
    bool setData(const QModelIndex &index, const QVariant &value,
                      int role = Qt::EditRole);
    QVariant headerData(int section, Qt::Orientation orientation,
                            int role) const;
    bool setHeaderData ( int section,
                         Qt::Orientation orientation,
                         const QVariant & value,
                         int role = Qt::EditRole );
    Qt::ItemFlags flags(const QModelIndex &index) const;

    //consulta
    QString getTableName();
    QString lastQuery();
    TSqlError select();
    RecordBase* getRecord(int index) const;
    template <class T> QList<T*> getTRecords() const;
    //void addSelectQueryFilter(TSqlGenerator &sg,bool temporal=false);
    void resetSelectQuery();
    int modelSize();
    int getConsConf() const;
    void setEnableNavigation(bool);
    void clearData();
    void clearQuery();

    /*!Devuelve un nuevo registro para que se le ingresen datos y se inserte en la base de datos*/
    virtual RecordBase *getNewRecord() = 0;

    //navegacion
    void setSelectQueryLimit(int);

    TSqlError submitAll();

public slots:
    //void addAttributeToSelect(QString);

    //navegacion
    void navToNext();
    void navToPrevious();

    void navToFirst();
    void navToLast();

    bool submit();
    void revert();

private slots:
    void record_hasRecordsWithOutSave(bool,RecordBase*);

signals:
    //actualizacion del contenido del modelo
    void beginResetModelSignal();
    void endResetModelSignal();

    //navegacion
    /*!Se emite cuando se actualiza el contenido del modelo.

      \param[out] next Se puede navegar hacia los siguientes registros. */
    void navNext(bool next);

    /*!Se emite cuando se actualiza el contenido del modelo.

      \param[out] prev Se puede navegar hacia los registros anteriores. */
    void navPrevious(bool prev);

    void hasRecordsWithOutSave(bool);
};

template <class T> QList<T*> ModelBase::getTRecords() const
{
    QList<T*> lst;
    foreach ( RecordBase* r, lstRecord )
        lst.append( (T*)r );
    return lst;
}

#endif // MODELBASE_H
