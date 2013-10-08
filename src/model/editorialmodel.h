#ifndef EDITORIALMODEL_H
#define EDITORIALMODEL_H

#include "om/editorialmodelbase.h"
#include "editorialrecord.h"

/*!
  Modelo de la tabla Editorial.

  Esta clase puede ser editada por el usuario y así personalizarla.

  Para mayor información ver ModelBase.
*/

class QANTMVSHARED_EXPORT EditorialModel : public EditorialModelBase
{
Q_OBJECT
public:
	//! Representa que configuración de consulta se esta utilizando. Para mas configuraciones agregarlas aqui.
	enum ConsConfEnum
	{
		Default//,CustomEnum
	};
	EditorialModel(QObject *parent=NULL,
				 ConsConfEnum conf=Default);
	~EditorialModel();

	QVariant headerData(int section, Qt::Orientation orientation,
							int role) const;

protected:
	QVariant getRecordValue(RecordBase*,int column=-1) const;
	void configureInternalSelectQuery();
};

#endif // EDITORIALMODEL_H
