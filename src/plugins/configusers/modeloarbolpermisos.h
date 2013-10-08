#ifndef MODELOARBOLPERMISOS_H
#define MODELOARBOLPERMISOS_H

#include <QAbstractItemModel>
#include <QAbstractItemDelegate>
#include <QString>

#include "grupopermisomodel.h"
#include "rolpermisomodel.h"
#include "permisomodel.h"
#include "configusers_global.h"

class CONFIGUSERSSHARED_EXPORT NodoPermisos
{
public:
    NodoPermisos();
    NodoPermisos(QString nombre, bool r, bool w, int id = 0, QString nombreForm = "");
    ~NodoPermisos();
    NodoPermisos *buscarNombre(QString nombre);
    NodoPermisos *buscarFormulario(QString nombre);

    QString nombreEtiqueta;
    bool permisoR, permisoW;
    NodoPermisos *padre;
    QList<NodoPermisos *> hijos;
    void addHijo(NodoPermisos *hijo);
    void setIdDB(int id);
    int getIdDB();
    int getPermisoRW();
    bool tieneHijos;
private:
    int idDB;
    QString nombreForm;
};

class CONFIGUSERSSHARED_EXPORT modeloArbolPermisos : public QAbstractItemModel
{
    Q_OBJECT
public:
    modeloArbolPermisos(QObject *parent=0);
    ~modeloArbolPermisos();
    void setNodoRaiz(NodoPermisos *nodo);
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientacion, int role) const;
    bool hasChildren ( const QModelIndex & parent = QModelIndex() ) const;
    bool setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
    Qt::ItemFlags flags ( const QModelIndex & index ) const;
    void filtrar(int idRol);
    bool saveData();

	NodoPermisos *nodoDesdeIndice(const QModelIndex &index) const;
private:
    NodoPermisos *nodoRaiz;
    void setValorNodosHijos(NodoPermisos *nodo, int rw, bool value);
    /*
    ModeloGrupoPermiso *grupoPermisos;
    ModeloRolPermiso *rolesPermisos;
    */
    GrupoPermisoModel *grupoPermisos;
    RolPermisoModel *rolesPermisos;

    bool saveNode(NodoPermisos *nodo);

private slots:
	void cambioDatos ( const QModelIndex & topLeft, const QModelIndex & bottomRight );
};

#endif // MODELOARBOLPERMISOS_H
