#include "rolpermisomodel.h"

RolPermisoModel::RolPermisoModel(QObject *parent,
						   ConsConfEnum conf) :
RolPermisoModelBase(parent)
{
	Q_UNUSED(conf)	//delete
	//setConsConf( conf ); //uncomment
}

RolPermisoModel::~RolPermisoModel()
{
}

/*! Configura una consulta

  Ver ModelBase para mayor información.

  Implementada de ModelBase::configurarQuery().
*/
void RolPermisoModel::configureInternalSelectQuery()
{
	switch (getConsConf())
	{
	case Default:
		break;
//	case CustomEnum:
//		r.setIdPersona();
//		r.setNombre();
//		r.setLugar_idLugar();
//		r.RLugar_idLugar()->setNombre();
		break;
	}
}

/*! Devuelve el valor de un atributo de registro.
	Si al ejecutarse este método esta:

	\code
	return ModelBase::getRecordValue(record,column);
	\endcode

	se mostrarán las columnas tal y como se configuro la consulta, de lo contrario se mostrarán las columnas personalizadas.

	Ver ModelBase para mayor información.

	Implementada de ModelBase::getRecordValue().
*/
QVariant RolPermisoModel::getRecordValue(RecordBase *record,int column) const
{
	return ModelBase::getRecordValue(record,column); //delete

//	RolPermisoRecord *r=(RolPermisoRecord*)record;
//	switch (getConsConf())
//	{
//	case Default:
//		return ModelBase::getRecordValue(record,column);
//	case CustomEnum:
//		switch (column)
//		{
////	case 0:	return r->idPersona();
////	case 1: return r->Nombre();
////	case 2: return QString::number(r->RLugar_idLugar()->idLugar())+", "+
////			r->RLugar_idLugar()->Nombre();
//		};
//		break;
//	};
//	return QVariant();
}

/*! Configura el nombre de las cabeceras de las columnas.

  Ver ModelBase para mayor información.

  Reimplementado de QAbstractItemModel::headerData().
*/
QVariant RolPermisoModel::headerData(int section,
								  Qt::Orientation orientation,
								  int role) const
{
	return RolPermisoModelBase::headerData(section,
									orientation,
									role); //delete

//	if (role != Qt::DisplayRole)
//		return QVariant();
//	if ( orientation == Qt::Vertical )
//		return section+1;

//	switch (getConsConf())
//	{
//	case Default:
//		return RolPermisoModelBase::headerData(section,
//										orientation,
//										role);
//	case CustomEnum:
//		switch ( section )
//		{
////	case 0: return "idPersona";
////	case 1: return "Name";
////	case 2: return "idLugar";
////	case 3: return "Lugar";
//		};
//		break;
//	};
//	return QVariant();
}

int RolPermisoModel::staticBuscarPermiso(QString usuario, QString nombreFormulario, QString grupo)
{
   //qDebug()<<"inicio de consulta";
	QString query = QString("SELECT R.Permiso FROM (RolPermiso R INNER JOIN (Rol R1 INNER JOIN Usuario U ON U.Rol_idRol=R1.idRol AND U.Usuario = '%1') ON R.Rol_idRol=R1.idRol) INNER JOIN (Permiso P INNER JOIN GrupoPermiso G ON P.GrupoPermiso_idGrupoPermiso=G.idGrupoPermiso AND P.Formulario = '%2' AND G.Nombre = '%3') ON R.Permiso_idPermiso=P.idPermiso").arg(usuario).arg(nombreFormulario).arg(grupo);
	//query.arg(usuario).arg(nombreFormulario).arg(grupo);
	//qDebug()<<query;
	QSqlQuery queryPermisos(query);
	if (queryPermisos.first())
	{
		//qDebug()<<"select de permiso logrado";
		return queryPermisos.value(0).toInt();
	}
	else
		return -1;
}

