#include "tvalidator.h"

#include <QRegExp>
#include <QRegExpValidator>
#include <QValidator>

QValidator* TValidator::vcodigo = NULL;
QValidator* TValidator::vdireccion = NULL;
QValidator* TValidator::vtelefono = NULL;
QValidator* TValidator::vmail = NULL;
QValidator* TValidator::vnit = NULL;
QValidator* TValidator::vnombre = NULL;
QValidator* TValidator::vplaca = NULL;

QValidator* TValidator::codigo()
{
	if ( !vcodigo )
	{
		QRegExp regexp( "([a-z]|[A-Z]|[-]|[0-9]|[.]|[/])*" );
		vcodigo = new QRegExpValidator(regexp,NULL);
	}
	return vcodigo;
}

QValidator* TValidator::direccion()
{
	if ( !vdireccion )
	{
		QRegExp regexp( "([a-z]|[A-Z]|[ ]|[ñ-Ñ]|[á-ú]|[0-9]|[-]|[.])*" );
		vdireccion = new QRegExpValidator(regexp,NULL);
	}
	return vdireccion;

}

QValidator* TValidator::telefono()
{
	if ( !vtelefono )
	{
		QRegExp regexp( "([0-9]||[-])*" );
		vtelefono = new QRegExpValidator(regexp,NULL);
	}
	return vtelefono;
}

QValidator* TValidator::mail()
{
	if ( !vmail )
	{
		QRegExp regexp( "([a-z]{1})([a-z]|[0-9]|[-]|[.]|[_])*([@]{1})([a-z]|[0-9])*([.]{1})([a-z]|[0-9]){1,3}([.]{1})([a-z]|[0-9]){2}" );
		vmail = new QRegExpValidator(regexp,NULL);
	}
	return vmail;
}

QValidator* TValidator::nombre()
{
	if ( !vnombre )
	{
		QRegExp regexp( "([a-z]|[A-Z]|[0-9]){1}([a-z]|[A-Z]|[ ]|[-]|[,]|[0-9]|[á-ú]|[/]|[.])*" );
		vnombre = new QRegExpValidator(regexp,NULL);
	}
	return vnombre;
}

QValidator* TValidator::nit()
{
	if ( !vnit )
	{
		QRegExp regexp( "([0-9]{1,7}[-]{1}([0-9]|[A-Z]|[a-z]){1})||([C]||[c]){1}[/]{1}([F]||[f])" );
		vnit = new QRegExpValidator(regexp,NULL);
	}
	return vnit;
}

QValidator* TValidator::placa()
{
	if ( !vplaca )
	{
		QRegExp regexp( "(([A-Z]{1}|[a-z]{1})([-]{1})([A-Z]{3}|[a-z]{3})([0-9]{3}))" );
		vplaca = new QRegExpValidator(regexp,NULL);
	}
	return vplaca;
}

