#include "ttable.h"
#include <QAbstractTableModel>

//Celda
//*************************************************
Celda::Celda()
{
	celdaAbajo=NULL;
	celdaArriba=NULL;
	celdaIzquierda=NULL;
	celdaDerecha=NULL;
}

Celda::Celda(Celda *arriba,Celda *abajo,Celda *izquierda,Celda *derecha)
{
	celdaArriba=arriba;
	celdaAbajo=abajo;
	celdaIzquierda=izquierda;
	celdaDerecha=derecha;
}

void Celda::setValor(QString valor){ VALOR = valor; }

QString Celda::valor() { return VALOR; }

//TTable
//*************************************************
TTable::TTable()
{
	filas=columnas=0;
	filasInsertar=0;
	columnasInsertar=0;
	celdaRaiz=new Celda;
}

TTable::TTable(int col,int fil)
{
	filas=columnas=0;
	filasInsertar=fil;
	columnasInsertar=col;
	celdaRaiz=new Celda;
	insertarFilas(filasInsertar);
}

void TTable::setSize(int columnas,int filas)
{
	filasInsertar=filas;
	columnasInsertar=columnas;
	insertarFilas(filasInsertar);
}

//privado

Celda* TTable::ultimaCeldaPrimeraColumna()
{
	Celda *celda = celdaRaiz;
	while ( celda->celdaAbajo != NULL )
		celda = celda->celdaAbajo;
	return celda;
}

Celda* TTable::ultimaCeldaPrimeraFila()
{
	Celda *celda = celdaRaiz;
	while ( celda->celdaDerecha != NULL )
		celda = celda->celdaDerecha;
	return celda;
}

Celda* TTable::ultimaCeldaDeColumna(int columna)
{
	if ( columna > columnas )
		return NULL;

	Celda *celda = celdaRaiz->celdaDerecha;
	for ( int c=0; c<columna ; c++ )
		celda = celda->celdaDerecha;
	while ( celda->celdaAbajo != NULL )
		celda = celda->celdaAbajo;
	return celda;
}

Celda* TTable::ultimaCeldaDeFila(int fila)
{
	if ( fila > filas )
		return NULL;

	Celda *celda = celdaRaiz->celdaAbajo;
	for ( int f=0; f<fila ; f++ )
		celda = celda->celdaAbajo;
	while ( celda->celdaDerecha != NULL )
		celda = celda->celdaDerecha;
	return celda;
}

Celda* TTable::at(int columna,int fila)
{
	Celda *celda=celdaRaiz->celdaDerecha;
	for ( int c=0;c<columna;c++ )
		celda = celda->celdaDerecha;
	for ( int f=0;f<fila;f++ )
		celda = celda->celdaAbajo;
	return celda;
}

//publico
void TTable::insertarFilas(int filasConteo)
{
	for ( int f=0; f<filasConteo; f++ )
	{
		Celda *uc = ultimaCeldaPrimeraColumna();
		columnas=0;

		for ( int c=0; c<columnasInsertar; c++ )
		{
			Celda *nc = new Celda;
			//nc->setValor(QString::number(f)+","+QString::number(c));
			if ( c==0 )
			{
				//si es la primera celda que insertarmos en la fila
				uc->celdaAbajo=nc;
				if ( filas == 0 )
					uc->celdaDerecha=nc;
				uc=uc->celdaAbajo;
			}
			else
			{
				uc->celdaDerecha=nc;
				uc=uc->celdaDerecha;

				//si hay mas de una fila se conecta la nueva celda con la ultima de celda de
				//su columnna, para ir formando la maya
				if ( filas > 0 )
				{
					Celda *ucc = ultimaCeldaDeColumna(c);
					ucc->celdaAbajo=nc;
				}
			}
			columnas++;
		}
		filas++;
	}
}

void TTable::insertarColumna(int pos)
{
	Celda *celda;
	if ( pos == 0 )
		celda=at(pos,0);
	else
		celda=at(pos-1,0);

	qDebug() << "filas" << filas;
	for ( int f=0; f<filas; f++ )
	{
		qDebug() << f;
		Celda *nc=new Celda;
		if ( pos == 0 ) //es la primera columna donde vamos a insertar
		{
			qDebug() << "pos = 0";
			if ( f==0 ) //es la primera fila
			{
				qDebug() << "primera fila";
				celdaRaiz->celdaAbajo=nc;
				celdaRaiz->celdaDerecha=nc;
				nc->celdaDerecha=celda;
				celda=nc;
			}
			else //ya se inserto la primera celda
			{
				qDebug() << "fila mayor a 0";
				celda->celdaAbajo=nc;
				nc->celdaDerecha=at(pos+1,f);
				celda=nc;
			}
		}
		else
		{
			qDebug() << "celda valor" << celda->valor();
			//qDebug() << "pos != 0";
			if ( pos != (columnas-1) ) //es medio
			{
				//qDebug() << "col medio";
				nc->celdaDerecha= celda->celdaDerecha;				
			}

			celda->celdaDerecha=nc;

			if ( f!=0 )
			{
				//qDebug()<< "no es la primera fila";
				at(pos,f-1)->celdaAbajo=nc;
			}

			qDebug() << celda->celdaDerecha->valor() <<
					nc->celdaDerecha->valor() ;

			celda=celda->celdaAbajo;
		}
	}
	qDebug() << "3" << at(3,3)->valor();
	//qDebug() << "4" << at(4,3)->valor();
	qDebug() << "5" << at(5,3)->valor();
	columnas++;
}

void TTable::copiarColumnaDeTabla(TTable tabla,
								 int columnaorigen,
								 int columnadestino)
{
	if ( columnaorigen > tabla.columnCount() ||
		 columnadestino > this->columnas )
		return;

	for ( int f=0; f<tabla.rowCount(); f++ )
	{
		if ( this->columnas == f )
			break;

		this->at(columnadestino,f)->setValor(tabla.at(columnaorigen,
													  f)->valor());
	}
}

void TTable::eliminarFila(int fila)
{
	Celda *celda;
	if ( fila == 0 )
		celda=at(0,fila);
	else
		celda=at(0,--fila);

	for ( int c=0; c<columnas; c++ )
	{
		Celda *celdaBorrar;
		if ( fila == 0 )
		{
			if ( c==0 ) // es la primera, redireccionamos la direccion de la primera fila en la raiz
			{
				celdaRaiz->celdaAbajo=celda->celdaAbajo;
				celdaRaiz->celdaDerecha=celda->celdaAbajo;
			}
			celdaBorrar=celda;
			celda=celda->celdaDerecha;
			delete celdaBorrar;
		}
		else if ( fila == (filas-0) ) //es la ultima fila
		{
			celdaBorrar=celda->celdaAbajo;
			celda->celdaAbajo=NULL;
			celda=celda->celdaDerecha;
			delete celdaBorrar;
		}
		else //es una fila media
		{
			celdaBorrar=celda->celdaAbajo;
			celda->celdaAbajo=celda->celdaAbajo->celdaAbajo;
			celda=celda->celdaDerecha;
			delete celdaBorrar;
		}
	}
	filas--;
}

int TTable::rowCount()
{
	return filas;
}

int TTable::columnCount()
{
	return columnas;
}

void TTable::clear()
{
	for ( int f=0; f<filas; f++ )
		eliminarFila(0);
	filas=columnas=0;
	filasInsertar=columnasInsertar=0;
	celdaRaiz->celdaDerecha=NULL;
	celdaRaiz->celdaAbajo=NULL;
}

void TTable::destroy()
{
	clear();
	delete celdaRaiz;
}

TTable TTable::convertirTextoATabla(QString texto)
{
	TTable tabla;

	QStringList filas;
	bool cortar=true;
	int ultimoCorte=-1;
	int cuantos=0;
	char ultimaLetra=0;

//    foreach ( QChar letra, texto )
//        qDebug() << "letra" << letra << "numero" << (int)letra.toAscii();

	//separamos el texto por filas
	for ( int c=0; c<texto.size(); c++ )
	{
		char letra = texto.at(c).toAscii();

        if ( letra == 34 )
		{
			if ( cortar &&  ( ultimaLetra == 10 || ultimaLetra == 9 ))
				cortar=false;
		}
		if ( letra == 9 )
		{
			if ( ultimaLetra == 34 )
				cortar = true;
		}
		if ( letra == 10 )
		{
			if ( ultimaLetra == 34 )
				cortar=true;

			if ( cortar )
			{
				filas.append( texto.mid( ultimoCorte+1,cuantos ) );
				ultimoCorte=c;
				cuantos=0;
			}
			else
				cuantos++;
		}
		else
			cuantos++;

		if ( c==texto.size()-1 )
			filas.append( texto.mid( ultimoCorte+1,cuantos ) );

		ultimaLetra = letra;
	}

    for ( int f=0; f<filas.size()-1; f++ )
	{
		QStringList columnas;
		cortar=true;
		ultimoCorte=-1;
		cuantos=0;
		ultimaLetra=0;

		QString fila = filas.at(f);

//        qDebug() << "fila" << fila;

		//separamos la fila en celdas
		for ( int c=0; c<fila.size(); c++ )
		{
			char letra = fila.at(c).toAscii();
			if ( letra == 34 )
			{
				if ( cortar && ultimaLetra == 9 )
					cortar=false;
			}

			if ( letra == 9 )
			{
				if ( ultimaLetra == 34 )
					cortar=true;

				if ( cortar )
				{
					columnas.append( fila.mid( ultimoCorte+1,cuantos) );
					ultimoCorte=c;
					cuantos=0;
				}
			}
			else
				cuantos++;

			if ( c==fila.size()-1 )
				columnas.append( fila.mid( ultimoCorte+1,cuantos ) );

			ultimaLetra = letra;
		}

        //***************************

		for ( int c=0; c<columnas.size(); c++ )
		{
//            qDebug() << "columna" << columnas.at(c);

			if ( f==0 && c==0 )
			{
				tabla.setSize(columnas.size(),filas.size()-1);
			}
			tabla.at(c,f)->setValor( columnas.at(c) );
		}
	}
	return tabla;
}

TTable TTable::convertirTextoATablaServiceCenter(QString texto)
{
    QString salida;

    foreach ( QString linea, texto.split( "\n" ) )
    {
        if ( salida.isEmpty() )
        {
            salida = linea;
            continue;
        }

        if ( linea.contains(QRegExp("^F\\d+")) )
            salida+="\n"+linea;
        else
            salida+=" "+linea;
    }

    TTable tabla(8,0);

    QStringList lstFilas = salida.split( "\n" );
    for ( int f=0; f<lstFilas.size(); f++ )
    {
        QStringList cols = lstFilas.at(f).split("^");

//        qDebug() << "fila" << QString::number(f);
//        for ( int a=0; a<cols.size(); a++  )
//            qDebug() << "col" << a << cols.at(a);

        if ( cols.size() != 8 )
        {
            qDebug() << "Error en la conversion, el texto no tiene 8 columnas";
            tabla.clear();
            return TTable();
        }

        tabla.insertarFilas(1);
        for ( int c=0; c<cols.size(); c++ )
            tabla.at( c, f )->setValor( cols.at(c) );
    }

    return tabla;
}

void TTable::copiarTablaAlPortapapeles(TTable tabla)
{
	QString copiar;
	for ( int f=0; f<tabla.rowCount(); f++ )
	{
		for ( int c=0; c<tabla.columnCount(); c++ )
		{
			copiar+=tabla.at(c,f)->valor();
			if ( tabla.columnCount()-1 != c )
				copiar+=QString((char) 9 );
		}

		copiar+=QString((char) 10 );
	}

	QApplication::clipboard()->setText(copiar);
}

void TTable::copiarTablaModelAlPortapapeles(QAbstractItemModel* tabla)
{
    QString copiar;
    for ( int f=0; f<tabla->rowCount(); f++ )
    {
        for ( int c=0; c<tabla->columnCount(); c++ )
        {            
            QString co = tabla->index( f,c ).data().toString();

            if ( co.contains(QRegExp("\\d+-\\d+-\\d+T\\d+:\\d+:\\d+")) )
                co.replace("T"," ");

            co.replace( QString((char) 9 )," " );
            co.replace( QString((char) 10 )," " );
            copiar+=co;
            if ( tabla->columnCount()-1 != c )
                copiar+=QString((char) 9 );
        }

        copiar+=QString((char) 10 );
    }

    QApplication::clipboard()->setText(copiar);
}

void TTable::copiarQModelIndexesAlPortapapeles(QModelIndexList lst)
{
    if ( lst.size() == 0 )
        return;

    QModelIndex ordenado;

    for ( int c=0; c<lst.size(); c++ )
    {
        for ( int f=0; f<lst.size(); f++ )
        {

        }
    }

//    for ( int f=0; f<lst.rowCount(); f++ )
//    {
//        for ( int c=0; c<tabla.columnCount(); c++ )
//        {
//            copiar+=tabla.at(c,f)->valor();
//            if ( tabla.columnCount()-1 != c )
//                copiar+=QString((char) 9 );
//        }

//        copiar+=QString((char) 10 );
//    }

//    for ( int c=0; c < lsti.size(); c++ )
//    {

//    }

}
