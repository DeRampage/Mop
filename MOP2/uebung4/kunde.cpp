#include <iostream>
#include "kunde.h"

using namespace std;


/* Implementierung Klasse Kunde ******************************************/
Kunde::Kunde(const MyString &Name, const MyString &Anschrift, const MyString &Tel):Name(Name),Anschrift(Anschrift),Telefon(Tel)
{

}

void Kunde::KundenDatenAusgeben()
{
	cout << "Name:........" << Name << endl;
	cout << "Anschrift:..." << Anschrift << endl;
	cout << "Telefon:....." << Telefon << endl;
}

/* Implementierung Klasse PrivatKunde ************************************/

PrivatKunde::PrivatKunde(const MyString &Name, const MyString &Anschrift, const MyString &Tel,
                         const MyString &Arbeitgeber, const MyString &TelGeschaeft):Kunde(Name,Anschrift,Tel),Arbeitgeber(Arbeitgeber),TelGeschaeft(TelGeschaeft)
{

}


void PrivatKunde::KundenDatenAusgeben()
{
	Kunde::KundenDatenAusgeben();
	cout << "Arbeitgeber:." << Arbeitgeber << endl;
	cout << "TelGeschaeft:" << TelGeschaeft << endl;
}


