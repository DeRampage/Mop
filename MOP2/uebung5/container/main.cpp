#include <ctime> // for clock_t & clock()

#include <iostream>
#include <vector>
#include <list>

using namespace std;

#define MAXIMUM 100000


int main(void)
{
    /* Zeitmessung fuer vector-Operationen */
    clock_t start = clock();
    // ToDo: Vektor fuer int anlegen
        std::vector<int> myVector(0);
        for(int i= 0; i <= MAXIMUM; i++){
            //myVector.insert(myVector.begin(),i);
            myVector.insert(myVector.end(),i);

        }
    // ToDo: Schleife 0 bis MAXIMUM, vorne einfuegen
	clock_t end = clock();

	cout << "Zeit bei Vektor: " << end-start << " ms" <<endl;

    /* Zeitmessung fuer list-Operationen */
	start = clock();

    // ToDo: list fuer int anlegen
    std::list<int> myList;
    std::list<int>::iterator it;
    it = myList.begin();
    for(int i= 0; i <= MAXIMUM; i++){
        //myList.insert(myList.begin(),i);
        myList.insert(myList.end(),i);
    }

    // ToDo: Schleife 0 bis MAXIMUM, vorne einfuegen

	end = clock();
	cout << "Zeit bei List: " << end-start << " ms" << endl;

	return 0;
}
