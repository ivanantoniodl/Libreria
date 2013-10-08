#ifndef CONFIGODSREPORT_H
#define CONFIGODSREPORT_H

#include <QObject>
#include "reporteods.h"
#include <QStringList>

class configOdsReport : public QObject
{
    Q_OBJECT
public:
    explicit configOdsReport(QObject *parent = 0);
    bool exportar();
    bool agregarCabecera(QStringList cabeceras);
    bool agregarFila(QStringList fila);
    void forzarFilaACadena(int fila);
    void forzarFilaAFecha(int fila);
    void forzarFilaANumero(int fila);
    void forzarFilaAMoneda(int fila);

private:
    reporteODS *reporte;

signals:

public slots:

};

#endif // CONFIGODSREPORT_H
