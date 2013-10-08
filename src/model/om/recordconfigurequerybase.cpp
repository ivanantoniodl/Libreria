#include "recordconfigurequerybase.h"

RecordConfigureQueryBase::RecordConfigureQueryBase(RecordConfigureQueryBase *rparent):
	PARENT(rparent)
{
}

/*! Agrega un atributo a la lista de atributos a consultar.
Si el padre del registro es nulo se emite el atributo a agregar para que el modelo que lo utiliza configure la consulta.
Si el padre es otro registro se le antepone el nombre de la tabla al del atributo y se envía como parametro a esta misma función en el padre. Esta función recursiva entre instancias se termina cuando el registro no tiene padre y se emite el resultado.

\param c Atributo o Tabla, Atributo a agregar

\b Ejemplo:

Tablas: Persona, Lugar, Tipo\n
Relaciones: \n
Persona.Lugar_idLugar <----- Lugar.idLugar\n
Lugar.Tipo_idTipo <--------- Tipo.idTipo

\code
PersonaRecord pr;
pr.setIdNombre(); // emite "idPersona"
pr.Nombre(); // emite "Nombre"
pr.RLugar_idLugar()->setNombre(); // emite "Lugar,Nombre"
pr.RLugar_idLugar()->RTipo_idTipo()->setNombre(); //emite "Lugar,Tipo,Nombre"
\endcode

Se guarda la configuración de la consulta para saber como guardar el resultado utilizando setRecordValues()

Configuración del código anterior:

\code
idPersona
Nombre
Lugar,Nombre
Lugar,Tipo,Nombre
\endcode
*/
void RecordConfigureQueryBase::addAttributeToQuery(QString c)
{
	if ( lstTables.size() == 1 )
	{
		//pertenece a herencia utilizando el padre maxima de la misma o simplemente no pertene a herencia

		if ( c.contains(".") )
			c=c.split(".").at(1); //con una sola tabla no nos sirve la tabla de Tabla.idTabla

		if ( PARENT == NULL )
			lstAttributesToQueryReady(c);//lista el camino del atributo para la consulta
		else
		{
			//el padre no es NULL significa que todavia hay que pasarlo al mismo

			if ( ! id.isEmpty() )
				c.prepend( lstTables.at(0)+"("+id+")," );
			else
				c.prepend( lstTables.at(0)+"," );

			//se agrega la tabla y se envia
			RecordConfigureQueryBase *rcqparent = (RecordConfigureQueryBase*)PARENT;
			rcqparent->addAttributeToQuery(c);
		}
	}
	else
	{
		//pertenece a una herencia

		QStringList path;
		if ( PARENT == NULL )
		{
			//sin padre
			if ( c.contains(".") )
			{
				//es la primera vez que se agrega porque tiene punto

				QString comingtable = c.split(".").at(0);//pertenece a herencia, sacamos la tabla de Tabla.idTabla

				//es la misma tabla, de una vez se envia
				if ( comingtable == lstTables.at(0) )
				{
					lstAttributesToQueryReady(c.split(".").at(1));
					return;
				}

				for ( int f=1; f<lstTables.size(); f++ )
				{
					QString table=lstTables.at(f);
					path.append(table);
					if ( table == comingtable ) //si la tabla es igual a la tabla que viene con c llegamos a la ultima
						break;
				}
				lstAttributesToQueryReady(path.join(",")+","+c.split(".").at(1));
			}
			else
			{
				//viene de otra tabla o grupo de herencia, ya no tiene punto

				for ( int f=lstTables.size()-1; f>0; f-- )
					path.prepend(lstTables.at(f));

				lstAttributesToQueryReady(path.join(",")+","+c);
			}
		}
		else
		{
			//con padre
			if ( c.contains(".") )
			{
				//es la primera vez que se agrega porque tiene punto

				QString comingtable = c.split(".").at(0);//pertenece a herencia, sacamos la tabla de Tabla.idTabla
				for ( int f=0; f<lstTables.size(); f++ )
				{
					QString table=lstTables.at(f);
					path.append(table);
					if ( table == comingtable ) //si la tabla es igual a la tabla que viene con c llegamos a la ultima
						break;
				}
				c=c.split(".").at(1);
			}
			else
			{
				//viene de otra tabla o grupo de herencia, ya no tiene punto

				for ( int f=lstTables.size()-1; f>=0; f-- )
					path.prepend(lstTables.at(f));
			}
			RecordConfigureQueryBase *rcqparent = (RecordConfigureQueryBase*)PARENT;
			rcqparent->addAttributeToQuery(path.join(",")+","+c);
		}
	}
}

void RecordConfigureQueryBase::lstAttributesToQueryReady(QString c)
{
	Q_UNUSED(c);
}
