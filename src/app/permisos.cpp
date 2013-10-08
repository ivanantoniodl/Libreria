#include "permisos.h"

#include <QSqlDatabase>
#include <QDebug>

perm::perm(int permiso)
{
    if (permiso == -1)
    {
        valido = false;
        permisoR = false;
        permisoW = false;
    }
    else
    {
        valido = true;
        permisoR = permiso&4;
        permisoW = permiso&8;
    }
}

Permisos::Permisos()
{
}

perm Permisos::	validar(QString nombreFormulario, QString etiqueta, QString grupo)
{
	QSqlDatabase defaultDB;
	defaultDB = QSqlDatabase::database();
	int permisoRW = -1;

    QString user = defaultDB.userName();
    user.replace( QString(CUSTOMER)+"_","" );

    if (user != "root")
	{
        permisoRW = RolPermisoModel::staticBuscarPermiso(user,nombreFormulario,grupo);
		if (permisoRW > -1)
		{
			return perm(permisoRW);
		}
		else
			return perm(-1);
	}
	unsigned int idRol = 0;
	//qDebug()<<"inicio consulta usuario";
	UsuarioModel *usuario = new UsuarioModel(0);
	usuario->configureQuery()->allAttributes();
    usuario->configureQuery()->addWhereAttribute("usuario", user);
	usuario->select();
    if ( (usuario->rowCount() > 0) || ( user == "root" ))
	{
        if (user != "root")
		{
			UsuarioRecord *cuser = (UsuarioRecord *)usuario->getRecord(0);
			//qDebug()<<"no soy root";
			idRol = cuser->Rol_idRol();
		}

		GrupoPermisoModel *grupoPermiso = new GrupoPermisoModel(0);
		grupoPermiso->configureQuery()->allAttributes();
		grupoPermiso->configureQuery()->addWhereAttribute("Nombre",grupo);
		//qDebug()<<"inicio consulta grupo";
		grupoPermiso->select();
		/* si no existe el grupo se crea */
		if ( grupoPermiso->rowCount() == 0 )
		{
			GrupoPermisoRecord ingresoGrupoPermiso;
			ingresoGrupoPermiso.setNombre(grupo);
			QSqlError error = ingresoGrupoPermiso.insert();
			if (error.type() != QSqlError::NoError)
				qDebug()<<"insersion fallida"<<error.text()<<ingresoGrupoPermiso.lastQuery();
			grupoPermiso->select();
		}
		if (grupoPermiso->rowCount() == 0)
			return perm(-1);

		GrupoPermisoRecord *rGrupoPermiso = (GrupoPermisoRecord *)grupoPermiso->getRecord(0);
		unsigned int idGrupoPermiso = rGrupoPermiso->idGrupoPermiso();
		delete grupoPermiso;

		PermisoModel *permiso = new PermisoModel(0);
		permiso->configureQuery()->allAttributes();
		permiso->configureQuery()->addWhereAttribute("Formulario",nombreFormulario);
		permiso->configureQuery()->addWhereAttribute("GrupoPermiso_idGrupoPermiso",idGrupoPermiso);
		//qDebug()<<"inicio consulta permiso";
		permiso->select();

		/* si no existe el permiso se crea */
		if (permiso->rowCount() == 0)
		{
			PermisoRecord ingresoPermiso;
			ingresoPermiso.setGrupoPermiso_idGrupoPermiso(idGrupoPermiso);
			ingresoPermiso.setFormulario(nombreFormulario);
			ingresoPermiso.setEtiqueta(etiqueta);
			QSqlError error = ingresoPermiso.insert();
			if (error.type() != QSqlError::NoError)
				qDebug()<<"insersion fallida"<<error.text()<<ingresoPermiso.lastQuery();
			permiso->select();
		}
		if (permiso->rowCount() == 0)
			return perm(-1);
		//qDebug()<<"permiso pasado";
		PermisoRecord *rPermiso = (PermisoRecord *)permiso->getRecord(0);
		//qDebug()<<"permiso consultado";
		unsigned int idPermiso = rPermiso->idPermiso();
		//qDebug()<<"obtencion de id permiso";
		delete permiso;

		/*
		  Si es el usuario root se le conceden todos los permisos
		  */

        if (user != "root")
		{
			RolPermisoModel *rolPermiso = new RolPermisoModel(0);
			rolPermiso->configureQuery()->allAttributes();
			rolPermiso->configureQuery()->addWhereAttribute("Permiso_idPermiso",idPermiso);
			rolPermiso->configureQuery()->addWhereAttribute("Rol_idRol",idRol);
			//qDebug()<<"inicio consulta rolpermiso";
			rolPermiso->select();
			if (rolPermiso->rowCount() > 0)
			{
				RolPermisoRecord *rRolPermiso =(RolPermisoRecord *)rolPermiso->getRecord(0);
				permisoRW=rRolPermiso->Permiso();
			}
			delete rolPermiso;
		}
		else
		{
			//qDebug()<<"soy root";
			permisoRW = 12;
		}

	}
	delete usuario;
	perm respuesta(permisoRW);
	return respuesta;
}

perm Permisos::validar(QWidget *formulario, QString nombreAccion, QString etiqueta, QString grupo)
{
    return validar(formulario->objectName()+"."+nombreAccion, etiqueta, grupo);
}

perm Permisos::validar(QWidget *formulario, QString etiqueta, QString grupo)
{
    return validar(formulario->objectName(), etiqueta, grupo);
}
