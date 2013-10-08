#ifndef EDITORIALLIBROMODEL_H
#define EDITORIALLIBROMODEL_H

#include "om/editoriallibromodelbase.h"
#include "editoriallibrorecord.h"

/*!
  Modelo de la tabla EditorialLibro.

  Esta clase puede ser editada por el usuario y así personalizarla.

  Para mayor información ver ModelBase.
*/

class QANTMVSHARED_EXPORT EditorialLibroModel : public EditorialLibroModelBase
{
Q_OBJECT
public:
	//! Representa que configuración de consulta se esta utilizando. Para mas configuraciones agregarlas aqui.
	enum ConsConfEnum
	{
		Default//,CustomEnum
	};
	EditorialLibroModel(QObject *parent=NULL,
				 ConsConfEnum conf=Default);
	~EditorialLibroModel();

	QVariant headerData(int section, Qt::Orientation orientation,
							int role) const;

protected:
	QVariant getRecordValue(RecordBase*,int column=-1) const;
	void configureInternalSelectQuery();
};

#endif // EDITORIALLIBROMODEL_H
