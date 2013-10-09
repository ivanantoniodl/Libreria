SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';


-- -----------------------------------------------------
-- Table `Rol`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Rol` ;

CREATE  TABLE IF NOT EXISTS `Rol` (
  `idRol` INT(11) NOT NULL AUTO_INCREMENT ,
  `Rol` VARCHAR(50) NOT NULL COMMENT '_view_' ,
  PRIMARY KEY (`idRol`) )
ENGINE = InnoDB
PACK_KEYS = 0
ROW_FORMAT = DEFAULT;


-- -----------------------------------------------------
-- Table `GrupoPermiso`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `GrupoPermiso` ;

CREATE  TABLE IF NOT EXISTS `GrupoPermiso` (
  `idGrupoPermiso` INT(11) NOT NULL AUTO_INCREMENT ,
  `Nombre` VARCHAR(50) NOT NULL COMMENT '_view_' ,
  PRIMARY KEY (`idGrupoPermiso`) )
ENGINE = InnoDB
PACK_KEYS = 0
ROW_FORMAT = DEFAULT;


-- -----------------------------------------------------
-- Table `Permiso`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Permiso` ;

CREATE  TABLE IF NOT EXISTS `Permiso` (
  `idPermiso` INT(11) NOT NULL AUTO_INCREMENT ,
  `GrupoPermiso_idGrupoPermiso` INT(11) NOT NULL ,
  `Formulario` VARCHAR(100) NOT NULL ,
  `Etiqueta` VARCHAR(50) NOT NULL COMMENT '_view_' ,
  PRIMARY KEY (`idPermiso`) ,
  INDEX `Permiso_FKIndex1` (`GrupoPermiso_idGrupoPermiso` ASC) ,
  CONSTRAINT `fk_b9104b36-6acc-11e0-92aa-00242c5e35bb0`
    FOREIGN KEY (`GrupoPermiso_idGrupoPermiso` )
    REFERENCES `GrupoPermiso` (`idGrupoPermiso` )
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB
PACK_KEYS = 0
ROW_FORMAT = DEFAULT;


-- -----------------------------------------------------
-- Table `RolPermiso`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `RolPermiso` ;

CREATE  TABLE IF NOT EXISTS `RolPermiso` (
  `idRolPermiso` INT(11) NOT NULL AUTO_INCREMENT ,
  `Permiso_idPermiso` INT(11) NOT NULL ,
  `Rol_idRol` INT(11) NOT NULL ,
  `Permiso` TINYINT UNSIGNED NOT NULL COMMENT '_view_' ,
  PRIMARY KEY (`idRolPermiso`) ,
  INDEX `Table_42_FKIndex1` (`Rol_idRol` ASC) ,
  INDEX `Table_42_FKIndex2` (`Permiso_idPermiso` ASC) ,
  CONSTRAINT `fk_b9094a3e-6acc-11e0-92aa-00242c5e35bb0`
    FOREIGN KEY (`Rol_idRol` )
    REFERENCES `Rol` (`idRol` )
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_b90dd4d2-6acc-11e0-92aa-00242c5e35bb0`
    FOREIGN KEY (`Permiso_idPermiso` )
    REFERENCES `Permiso` (`idPermiso` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
PACK_KEYS = 0
ROW_FORMAT = DEFAULT;


-- -----------------------------------------------------
-- Table `UsuarioCargo`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `UsuarioCargo` ;

CREATE  TABLE IF NOT EXISTS `UsuarioCargo` (
  `idUsuarioCargo` TINYINT UNSIGNED NOT NULL AUTO_INCREMENT ,
  `Cargo` VARCHAR(15) NOT NULL COMMENT '_view_' ,
  PRIMARY KEY (`idUsuarioCargo`) )
ENGINE = InnoDB
PACK_KEYS = 0
ROW_FORMAT = DEFAULT;


-- -----------------------------------------------------
-- Table `Empresa`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Empresa` ;

CREATE  TABLE IF NOT EXISTS `Empresa` (
  `idEmpresa` INT(11) NOT NULL AUTO_INCREMENT ,
  `Nombre` VARCHAR(45) NULL DEFAULT NULL COMMENT '_view_' ,
  PRIMARY KEY (`idEmpresa`) )
ENGINE = InnoDB
PACK_KEYS = 0
ROW_FORMAT = DEFAULT;


-- -----------------------------------------------------
-- Table `Usuario`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Usuario` ;

CREATE  TABLE IF NOT EXISTS `Usuario` (
  `idUsuario` INT(11) NOT NULL AUTO_INCREMENT ,
  `Empresa_idEmpresa` INT(11) NOT NULL ,
  `Rol_idRol` INT(11) NOT NULL ,
  `UsuarioCargo_idUsuarioCargo` TINYINT UNSIGNED NOT NULL ,
  `Nombres` VARCHAR(100) NOT NULL COMMENT '_view_' ,
  `Apellidos` VARCHAR(100) NOT NULL ,
  `Usuario` VARCHAR(35) NOT NULL ,
  `FechaHora` DATETIME NOT NULL ,
  `Turno` VARCHAR(45) NULL ,
  PRIMARY KEY (`idUsuario`) ,
  UNIQUE INDEX `Usuarios_indice` (`Usuario` ASC) ,
  INDEX `Usuarios_FKIndex1` (`UsuarioCargo_idUsuarioCargo` ASC) ,
  INDEX `Usuarios_FKIndex2` (`Rol_idRol` ASC) ,
  INDEX `Usuario_FKIndex3` (`Empresa_idEmpresa` ASC) ,
  CONSTRAINT `fk_b8dc818e-6acc-11e0-92aa-00242c5e35bb0`
    FOREIGN KEY (`UsuarioCargo_idUsuarioCargo` )
    REFERENCES `UsuarioCargo` (`idUsuarioCargo` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_b8ecbe1e-6acc-11e0-92aa-00242c5e35bb0`
    FOREIGN KEY (`Rol_idRol` )
    REFERENCES `Rol` (`idRol` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_b8f82a74-6acc-11e0-92aa-00242c5e35bb0`
    FOREIGN KEY (`Empresa_idEmpresa` )
    REFERENCES `Empresa` (`idEmpresa` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
PACK_KEYS = 0
ROW_FORMAT = DEFAULT;


-- -----------------------------------------------------
-- Table `LugarTipo`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `LugarTipo` ;

CREATE  TABLE IF NOT EXISTS `LugarTipo` (
  `idLugarTipo` TINYINT UNSIGNED NOT NULL AUTO_INCREMENT ,
  `Tipo` VARCHAR(25) NOT NULL COMMENT '_view_' ,
  PRIMARY KEY (`idLugarTipo`) )
ENGINE = InnoDB
PACK_KEYS = 0
ROW_FORMAT = DEFAULT;


-- -----------------------------------------------------
-- Table `Lugar`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Lugar` ;

CREATE  TABLE IF NOT EXISTS `Lugar` (
  `idLugar` TINYINT UNSIGNED NOT NULL AUTO_INCREMENT ,
  `Empresa_idEmpresa` INT(11) NOT NULL ,
  `LugarTipo_idLugarTipo` TINYINT UNSIGNED NOT NULL ,
  `Nombre` VARCHAR(60) NULL DEFAULT NULL COMMENT '_view_' ,
  `Direccion` VARCHAR(255) NULL DEFAULT NULL ,
  `Telefono` VARCHAR(9) NULL DEFAULT NULL ,
  `NumPlaca` VARCHAR(8) NULL DEFAULT NULL ,
  PRIMARY KEY (`idLugar`) ,
  INDEX `Lugares_FKIndex1` (`LugarTipo_idLugarTipo` ASC) ,
  INDEX `Lugar_FKIndex2` (`Empresa_idEmpresa` ASC) ,
  CONSTRAINT `fk_b8da4644-6acc-11e0-92aa-00242c5e35bb0`
    FOREIGN KEY (`LugarTipo_idLugarTipo` )
    REFERENCES `LugarTipo` (`idLugarTipo` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_b8f62940-6acc-11e0-92aa-00242c5e35bb0`
    FOREIGN KEY (`Empresa_idEmpresa` )
    REFERENCES `Empresa` (`idEmpresa` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
PACK_KEYS = 0
ROW_FORMAT = DEFAULT;


-- -----------------------------------------------------
-- Table `Libro`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Libro` ;

CREATE  TABLE IF NOT EXISTS `Libro` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `Nombre` VARCHAR(45) NULL ,
  `AnioImp` VARCHAR(5) NULL ,
  PRIMARY KEY (`id`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Editorial`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Editorial` ;

CREATE  TABLE IF NOT EXISTS `Editorial` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `Nombre` VARCHAR(45) NULL ,
  `Direccion` VARCHAR(45) NULL ,
  PRIMARY KEY (`id`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `EditorialLibro`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `EditorialLibro` ;

CREATE  TABLE IF NOT EXISTS `EditorialLibro` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `Editorial_id` INT NOT NULL ,
  `Libro_id` INT NOT NULL ,
  INDEX `fk_Editorial_has_Libro_Libro1_idx` (`Libro_id` ASC) ,
  INDEX `fk_Editorial_has_Libro_Editorial1_idx` (`Editorial_id` ASC) ,
  PRIMARY KEY (`id`) ,
  CONSTRAINT `fk_Editorial_has_Libro_Editorial1`
    FOREIGN KEY (`Editorial_id` )
    REFERENCES `Editorial` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Editorial_has_Libro_Libro1`
    FOREIGN KEY (`Libro_id` )
    REFERENCES `Libro` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Autor`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Autor` ;

CREATE  TABLE IF NOT EXISTS `Autor` (
  `id` INT NOT NULL ,
  `Nombre` VARCHAR(45) NULL ,
  `Direccion` VARCHAR(45) NULL ,
  PRIMARY KEY (`id`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `LibroAutor`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `LibroAutor` ;

CREATE  TABLE IF NOT EXISTS `LibroAutor` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `Libro_id` INT NOT NULL ,
  `Autor_id` INT NOT NULL ,
  PRIMARY KEY (`id`) ,
  INDEX `fk_Libro_has_Autor_Autor1_idx` (`Autor_id` ASC) ,
  INDEX `fk_Libro_has_Autor_Libro1_idx` (`Libro_id` ASC) ,
  CONSTRAINT `fk_Libro_has_Autor_Libro1`
    FOREIGN KEY (`Libro_id` )
    REFERENCES `Libro` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Libro_has_Autor_Autor1`
    FOREIGN KEY (`Autor_id` )
    REFERENCES `Autor` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Maquina`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Maquina` ;

CREATE  TABLE IF NOT EXISTS `Maquina` (
  `idMaquina` INT(11) NOT NULL AUTO_INCREMENT ,
  `Ip` VARCHAR(15) NULL DEFAULT NULL ,
  `Lugar_idLugar` TINYINT UNSIGNED NOT NULL ,
  PRIMARY KEY (`idMaquina`) ,
  UNIQUE INDEX `Ip_UNIQUE` (`Ip` ASC) ,
  INDEX `fk_Maquina_Lugar1_idx` (`Lugar_idLugar` ASC) ,
  CONSTRAINT `fk_Maquina_Lugar1`
    FOREIGN KEY (`Lugar_idLugar` )
    REFERENCES `Lugar` (`idLugar` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;



SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
