#include "genorpt.h"

#include <QMessageBox>
#include <QFile>
#include <QPrinter>
#include <QPrintDialog>

#include <renderobjects.h>
#include <orprerender.h>
#include <orprintrender.h>

#include "previewdialog.h"

genORPT::genORPT(QWidget *parent)
{
    this->parent = parent;
    this->params = NULL;
}

genORPT::~genORPT()
{
    if (params)
        delete params;
}

bool genORPT::abrirArchivo(QString &filename)
{
    QDomDocument doctmp;
    QString errMsg;
    int errLine, errColm;
    QFile file(filename);
    if(!doctmp.setContent(&file, &errMsg, &errLine, &errColm))
    {
      QMessageBox::critical(parent, "Error Loading File",
        QString("There was an error opening the file %1."
           "\n\n%2 on line %3 column %4.")
           .arg(filename).arg(errMsg).arg(errLine).arg(errColm) );
      return false;
    }

    QDomElement root = doctmp.documentElement();
    if(root.tagName() != "report")
    {
      QMessageBox::critical(parent, "Not a Valid File",
        QString("The file %1 does not appear to be a valid file."
           "\n\nThe root node is not 'report'.").arg(filename) );
      return false;
    }

    return setDoc(doctmp);
}

bool genORPT::setDoc(QDomDocument &doc)
{
    QDomElement root = doc.documentElement();
    if(root.tagName() != "report")
    {
      QMessageBox::critical(parent, "Not a Valid Report",
        QString("The report definition does not appear to be a valid report."
           "\n\nThe root node is not 'report'."));
      return false;
    }
    this->doc = doc;
    return true;
}

void genORPT::imprimir(bool showPreview, int numCopies)
{
    ORPreRender *pre = new ORPreRender;
    pre->setDom(doc);
    if (params)
        pre->setParamList(*params);
    ORODocument * ptrdoc = pre->generate();

    if(ptrdoc)
    {
      QPrinter printer(QPrinter::HighResolution);
      printer.setNumCopies( numCopies );

      if(showPreview)
      {
        PreviewDialog preview (ptrdoc, &printer, parent);
        if (preview.exec() == QDialog::Rejected)
          return;
      }

      ORPrintRender render;
      render.setupPrinter(ptrdoc, &printer);

      QPrintDialog pd(&printer);
      pd.setMinMax(1, ptrdoc->pages());
      if(pd.exec() == QDialog::Accepted)
      {
        render.setPrinter(&printer);
        render.render(ptrdoc);
      }
      delete ptrdoc;

    }
    delete pre;
}

ParameterList *genORPT::parametro()
{
    if (!params)
        params = new ParameterList;
    return params;
}
