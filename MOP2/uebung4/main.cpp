#include <vector>
#include <iostream>
#include "mystring.h"
#include "kunde.h"



int main(void)
{
	/* Uebung 4.1 */
    MyString eins("eins");
	{
        MyString zwei("zwei");
		MyString drei = zwei;
        MyString vier(zwei);
        eins = zwei;
        std::cout << "eins:" << eins.Get() << std::endl;
    }
    MyString test("test");

	std::cout << "eins:" << eins.Get() << std::endl; 

    // Uebung 4.2
    PrivatKunde kunde("Heinz Denker","Denkeralm Strasse 1, Denkerdorf","336537","UniBwM","7777");
    kunde.KundenDatenAusgeben();

    // Ende?

    return 0;
}
		



