#pragma once

#include "mystring.h"
/* Deklaration Klasse Kunde ***********************************/
class Kunde
{
public:
    Kunde(const MyString &Name="Kein Angaben",const MyString &Anschrift="Kein Angaben",const MyString &Tel="Kein Angaben");
	virtual void KundenDatenAusgeben();
protected:
	MyString Name;
	MyString Anschrift;
	MyString Telefon;
};

/* Deklaration Klasse Privatkunde ******************************/

class PrivatKunde: public Kunde
{
public:
    PrivatKunde(const MyString &Name,const MyString &Anschrift,const MyString &Tel,const MyString &Arbeitgeber,
                const MyString &TelGeschaeft);
	virtual void KundenDatenAusgeben();
protected:
	MyString Arbeitgeber;
	MyString TelGeschaeft;
};

