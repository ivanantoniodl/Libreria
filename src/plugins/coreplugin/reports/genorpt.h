#ifndef GENORPT_H
#define GENORPT_H

#include <QDomDocument>

#include <xsqlquery.h>

#include <dbtools.h>
#include <login.h>

#include <parameter.h>
#include <xvariant.h>
#include <stdio.h>
#include "../core_global.h"

class CORESHARED_EXPORT genORPT
{
public:
    genORPT(QWidget *parent);
    ~genORPT();
    bool abrirArchivo(QString &filename);
    void imprimir(bool showPreview, int numCopies);
    ParameterList *parametro();
private:
    QWidget *parent;
    ParameterList *params;
    QDomDocument doc;
    bool setDoc(QDomDocument &doc);
};

#endif // GENORPT_H
