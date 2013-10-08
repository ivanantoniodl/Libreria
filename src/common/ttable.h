#ifndef TABLA_H
#define TABLA_H

#include <QtCore>
#include <QApplication>
#include <QClipboard>
#include "common_global.h"

class QAbstractTableModel;

class COMMONSHARED_EXPORT Celda
{
private:
	QString VALOR;
public:
	Celda();
	Celda(Celda *arriba,Celda *abajo,Celda *izquierda,Celda *derecha);
	void setValor(QString);
	QString valor();

	Celda *celdaArriba,*celdaAbajo,*celdaIzquierda,*celdaDerecha;
};

class COMMONSHARED_EXPORT TTable
{
private:
	Celda *celdaRaiz;
	int filas,columnas,filasInsertar,columnasInsertar;

	Celda* ultimaCeldaPrimeraColumna();
	Celda* ultimaCeldaPrimeraFila();

	Celda* ultimaCeldaDeColumna(int);
	Celda* ultimaCeldaDeFila(int);
public:
	TTable(int columnas,int filas);
	TTable();

	void setSize(int columnas,int filas);
	Celda* at(int columna,int fila);
	void insertarFilas(int);
	void eliminarFila(int);
	void insertarColumna(int);
	void copiarColumnaDeTabla(TTable,int colorigen,int coldestino);
	int rowCount();
	int columnCount();
	void clear();
	void destroy();

	static TTable convertirTextoATabla(QString texto);
    static TTable convertirTextoATablaServiceCenter(QString texto);
	static void copiarTablaAlPortapapeles(TTable tabla);
    static void copiarTablaModelAlPortapapeles(QAbstractItemModel* tabla);
    static void copiarQModelIndexesAlPortapapeles(QModelIndexList lst);
};

#endif // TABLA_H
