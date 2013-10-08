delimiter //


-- Usuarios -----

-- Procedimiento para insertar RolesPermisos

DROP PROCEDURE IF EXISTS VerificarRolesPermisos//

CREATE PROCEDURE VerificarRolesPermisos()
BEGIN
  DECLARE varIdRol INT UNSIGNED DEFAULT 0;
  DECLARE varIdPermiso INT UNSIGNED DEFAULT 0;
  DECLARE doneRol INT DEFAULT 0;
  DECLARE curRolPermiso CURSOR FOR SELECT RP.idRol, RP.idPermiso FROM 
      (SELECT idRol, idPermiso FROM Rol R, Permiso P) RP 
        LEFT JOIN RolPermiso R ON RP.idRol = R.Rol_idRol AND RP.idPermiso = R.Permiso_idPermiso 
      WHERE R.idRolPermiso IS NULL ORDER BY RP.idRol;
  DECLARE CONTINUE HANDLER FOR SQLSTATE '02000' SET doneRol = 1;

  OPEN curRolPermiso;
  FETCH curRolPermiso INTO varIdRol, varIdPermiso;
  WHILE NOT doneRol DO
    INSERT INTO RolPermiso ( Permiso_idPermiso, Rol_idRol, Permiso) VALUES ( varIdPermiso, varIdRol, 0);
    FETCH curRolPermiso INTO varIdRol, varIdPermiso;
  END WHILE;
  CLOSE curRolPermiso;     
END;//

-- ------- Tabla Rol

DROP TRIGGER IF EXISTS AIAct_RolPermisoRol//

CREATE TRIGGER AIAct_RolPermisoRol AFTER INSERT ON Rol
FOR EACH ROW
BEGIN
  CALL VerificarRolesPermisos();
END;//

-- --- Tabla Rol

DROP TRIGGER IF EXISTS AIAct_RolPermisoPermiso//

CREATE TRIGGER AIAct_RolPermisoPermiso AFTER INSERT ON Permiso
FOR EACH ROW
BEGIN
  CALL VerificarRolesPermisos();
END;//

-- --- Tabla Usuario

DROP TRIGGER IF EXISTS BIAct_UsuarioFecha//

CREATE TRIGGER BIAct_UsuarioFecha BEFORE INSERT ON Usuario
FOR EACH ROW
BEGIN
  SET NEW.FechaHora = NOW();
END//


delimiter ;







