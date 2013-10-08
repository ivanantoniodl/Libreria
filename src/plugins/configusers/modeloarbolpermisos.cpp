#include "modeloarbolpermisos.h"

#include <QMessageBox>
#include <QtSql>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QDebug>

NodoPermisos::NodoPermisos()
{
    permisoR = permisoW = 0;
    padre = 0;
    idDB = 0;
    tieneHijos=false;
}

NodoPermisos::NodoPermisos(QString nombre, bool r, bool w, int id, QString nombreForm)
{
    nombreEtiqueta = nombre;
    permisoR = r;
    permisoW = w;
    padre = 0;
    idDB = id;
    this->nombreForm=nombreForm;
}

NodoPermisos::~NodoPermisos()
{
    qDeleteAll(hijos);
}

NodoPermisos *NodoPermisos::buscarNombre(QString nombre)
{
    for (int i=0; i < hijos.size(); i++)
    {
        if (hijos[i]->nombreEtiqueta == nombre)
            return hijos[i];
    }
    return 0;
}

NodoPermisos *NodoPermisos::buscarFormulario(QString nombre)
{
    for (int i=0; i < hijos.size(); i++)
    {
        if (hijos[i]->nombreForm == nombre)
            return hijos[i];
    }
    return 0;
}

void NodoPermisos::addHijo(NodoPermisos *hijo)
{
    hijo->padre=this;
    this->hijos.append(hijo);
    tieneHijos = true;
}

void NodoPermisos::setIdDB(int id)
{
    idDB=id;
}

int NodoPermisos::getIdDB()
{
    return idDB;
}

int NodoPermisos::getPermisoRW()
{
    return 4*(int)(permisoR)+8*(int)(permisoW);
}


modeloArbolPermisos::modeloArbolPermisos(QObject *parent)
        : QAbstractItemModel(parent)
{
    nodoRaiz = new NodoPermisos();
    grupoPermisos = new GrupoPermisoModel(this);
    rolesPermisos = new RolPermisoModel(this);

	connect( this,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(cambioDatos(QModelIndex,QModelIndex)) );

    grupoPermisos->configureQuery()->allAttributes();
    grupoPermisos->configureQuery()->addOrderBy("Nombre");
    grupoPermisos->select();

	foreach (GrupoPermisoRecordBase *rec, grupoPermisos->getRecords())
    {
        nodoRaiz->addHijo(new NodoPermisos(rec->Nombre(), 0, 0, rec->idGrupoPermiso()));
    }
}

modeloArbolPermisos::~modeloArbolPermisos()
{
    delete nodoRaiz;
}

void modeloArbolPermisos::setNodoRaiz(NodoPermisos *nodo)
{
    delete nodoRaiz;
    nodoRaiz=nodo;
    reset();
}

QModelIndex modeloArbolPermisos::index(int row, int column, const QModelIndex &parent) const
{
    if (!nodoRaiz)
        return QModelIndex();
    NodoPermisos *nodoPadre = nodoDesdeIndice(parent);
    return createIndex(row, column, nodoPadre->hijos[row]);
}

NodoPermisos *modeloArbolPermisos::nodoDesdeIndice(const QModelIndex &index) const
{
    if (index.isValid())
        return static_cast<NodoPermisos *>(index.internalPointer());
    else
        return nodoRaiz;
}

int modeloArbolPermisos::rowCount(const QModelIndex &parent) const
{
    NodoPermisos *nodoPadre = nodoDesdeIndice(parent);
    if (!nodoPadre)
        return 0;
    return nodoPadre->hijos.count();
}

int modeloArbolPermisos::columnCount(const QModelIndex &) const
{
    return 3;
}

QModelIndex modeloArbolPermisos::parent(const QModelIndex &child) const
{
    NodoPermisos *nodo = nodoDesdeIndice(child);
    if (!nodo)
        return QModelIndex();
    NodoPermisos *nodoPadre = nodo->padre;
    if (!nodoPadre)
        return QModelIndex();
    if (nodoPadre == nodoRaiz)
        return QModelIndex();
    NodoPermisos *nodoAbuelo = nodoPadre->padre;
    if (!nodoAbuelo)
        return QModelIndex();
    int row = nodoAbuelo->hijos.indexOf(nodoPadre);
    return createIndex(row, 0, nodoPadre);
}

bool modeloArbolPermisos::hasChildren ( const QModelIndex & parent ) const
{
    NodoPermisos *nodoPadre= nodoDesdeIndice(parent);
    if (nodoPadre->hijos.size() > 0)
        return true;
    return false;
}

QVariant modeloArbolPermisos::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    NodoPermisos *nodo = nodoDesdeIndice(index);
    if (!nodo)
        return QVariant();
    switch (index.column())
    {
        case 0: return nodo->nombreEtiqueta;
		case 1: return nodo->permisoR;
        case 2: return nodo->permisoW;
    }
    return QVariant();
}

QVariant modeloArbolPermisos::headerData(int section, Qt::Orientation orientacion, int role) const
{
    if (orientacion == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section)
        {
            case 0: return "Formulario";
            case 1: return "R";
            case 2: return "W";
        }
    }
    return QVariant();
}

bool modeloArbolPermisos::setData ( const QModelIndex & index, const QVariant & value, int role )
{
    Q_UNUSED(role);
    NodoPermisos *nodo = nodoDesdeIndice(index);
    if (nodo)
	{
        if (index.column() == 1)
        {
			nodo->permisoR = value.toBool();
            setValorNodosHijos(nodo,1,nodo->permisoR);
        }
        else if (index.column() == 2)
        {
            nodo->permisoW = value.toBool();
            setValorNodosHijos(nodo,2,nodo->permisoW);
        }
		emit dataChanged(index, index);
		return true;
    }
	else
		return false;
}

Qt::ItemFlags modeloArbolPermisos::flags ( const QModelIndex & index ) const
{
	if (index.column() > 0)
        return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
    else
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

void modeloArbolPermisos::filtrar(int idRol)
{
	for (int i = 0; i< nodoRaiz->hijos.count();i++)
        nodoRaiz->hijos.at(i)->hijos.clear();

    rolesPermisos->clearQuery();
    rolesPermisos->configureQuery()->idRolPermiso();
    rolesPermisos->configureQuery()->Permiso();
    rolesPermisos->configureQuery()->RPermiso_()->Formulario();
    rolesPermisos->configureQuery()->RPermiso_()->Etiqueta();
    rolesPermisos->configureQuery()->RPermiso_()->RGrupoPermiso_()->Nombre();
    rolesPermisos->configureQuery()->addWhereAttribute("Rol_idRol",idRol);
    rolesPermisos->configureQuery()->addOrderBy("Permiso","Etiqueta");
	TSqlError error = rolesPermisos->select();

	qDebug() << rolesPermisos->lastQuery();

    NodoPermisos *ptrTemp;
	foreach (RolPermisoRecordBase *recRP, rolesPermisos->getRecords())
    {
//		qDebug() << recRP->RPermiso_()->RGrupoPermiso_()->Nombre() << "nombre";

        if ((ptrTemp=nodoRaiz->buscarNombre(recRP->RPermiso_()->RGrupoPermiso_()->Nombre())))
        {
            /*
              Si el nombre esta compuesto buscar por la primera
              */
            QStringList subForm = recRP->RPermiso_()->Formulario().split(".");
            if (subForm.size() > 1)
            {
                NodoPermisos *ptrSubForm=0;
                if ((ptrSubForm=ptrTemp->buscarFormulario(subForm.at(0))))
                {
                    ptrSubForm->addHijo(new NodoPermisos(
                            recRP->RPermiso_()->Etiqueta(),
							recRP->Permiso()&4,
                            recRP->Permiso()&8,
                            recRP->idRolPermiso(),
                            recRP->RPermiso_()->Formulario()
                            ));
//					qDebug()<< "encontrado" << ptrSubForm->nombreEtiqueta;
                }
                else
                {
                    NodoPermisos *nuevoFormulario=new NodoPermisos(
                            "Acciones",
                            0,
                            0,
                            recRP->idRolPermiso(),
                            subForm.at(0)
                            );
                    nuevoFormulario->addHijo(new NodoPermisos(
                            recRP->RPermiso_()->Etiqueta(),
                            recRP->Permiso()&4,
                            recRP->Permiso()&8,
                            recRP->idRolPermiso(),
                            recRP->RPermiso_()->Formulario()
                            ));
                    ptrTemp->addHijo(nuevoFormulario);
                }
            }
            else
            {
                ptrTemp->addHijo(new NodoPermisos(
                        recRP->RPermiso_()->Etiqueta(),
                        recRP->Permiso()&4,
                        recRP->Permiso()&8,
						recRP->idRolPermiso(),
                        recRP->RPermiso_()->Formulario()
                        ));
            }
        }
    }
}

/**TODO permisos->validar("formulario", 'grupo' , opt etiqueta);
  **/

/**setValorNodosHijos
  rw
    1 = R
    2 = W
  */
void modeloArbolPermisos::setValorNodosHijos(NodoPermisos *nodo, int rw, bool value)
{
    if ( nodo )
    {
        if ( nodo->hijos.count() > 0 )
        {
            for (int i = 0; i< nodo->hijos.count(); i++)
            {
                if (rw == 1)
                    nodo->hijos.at(i)->permisoR = value;
                else if (rw == 2)
                    nodo->hijos.at(i)->permisoW = value;
                if (nodo->hijos.at(i)->hijos.count() > 0)
                    setValorNodosHijos(nodo->hijos[i],rw,value);
            }
        }
    }
}

bool modeloArbolPermisos::saveNode(NodoPermisos *nodo)
{
    RolPermisoModel *rolPermisoUpdate = new RolPermisoModel(this);
    RolPermisoRecord *recRPU;
    TSqlError error;
    //qDebug()<<nodo->nombreForm;
    for (int j = 0; j < nodo->hijos.count(); j++)
    {
        //qDebug()<<nodo->nombreEtiqueta;
        if (nodo->hijos.at(j)->tieneHijos)
        {
            if ( ! saveNode(nodo->hijos[j]) )
                return false;
        }
        else
        {
            rolPermisoUpdate->clearQuery();
            rolPermisoUpdate->configureQuery()->allAttributes();
            rolPermisoUpdate->configureQuery()->addWhereAttribute(
                    "idRolPermiso",
                    nodo->hijos.at(j)->getIdDB()
                    );
            rolPermisoUpdate->select();
            recRPU=(RolPermisoRecord *)rolPermisoUpdate->getRecord(0);
            //qDebug()<<recRPU->Permiso()<<recRPU->idRolPermiso();
            recRPU->setPermiso(nodo->hijos.at(j)->getPermisoRW());
            error=recRPU->update();
            if (error.type() != QSqlError::NoError)
                return false;
        }
    }
    return true;
}

void modeloArbolPermisos::cambioDatos ( const QModelIndex & topLeft,
										const QModelIndex & bottomRight )
{
	NodoPermisos *nodo = nodoDesdeIndice(topLeft);
	//qDebug() << nodo->getIdDB() << nodo->nombreEtiqueta << nodo->permisoR << nodo->permisoW;
}
