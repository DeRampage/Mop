/* Beispiel zu "Start in die C-Programmierung" von D. Pawelczak */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 3

typedef struct {
	char vorname[8];
	char nachname[8];
	long kundennummer;
} tKunde;

/* Initialisieren */
void Init(tKunde* kunden[], int from, int to)
{
	int i = 0;
	for (i = from; i < to; i++) 
		kunden[i] = NULL;
}

/* Alle Kunden ausgeben */ 
void Print(tKunde* kunden[], int maxKunden)
{
	int i = 0;

	for (i = 0; i < maxKunden; i++)
		if (kunden[i] != NULL)
			printf("Kundennummer: %d, Name: %s\n",
				kunden[i]->kundennummer, kunden[i]->nachname);
}


/* Datensätze anlegen */
int Add(tKunde** pKunden[], int maxKunden, char* vorName, char* nachName)
{
	static long kundenNummer = 0;
	int i = 0;
	tKunde *neuKunde = (tKunde*) calloc(sizeof(tKunde), 1);
	neuKunde->kundennummer = ++kundenNummer;
	strcpy(neuKunde->vorname, vorName);
	strcpy(neuKunde->nachname, nachName);
	
	for (i = 0; i < maxKunden; i++)
		if ((*pKunden)[i] == NULL)
			break;
	
	if (i < maxKunden)
		(*pKunden)[i] = neuKunde;
	else
	{
		*pKunden = realloc(*pKunden, sizeof(tKunde) 
		   * maxKunden * 2);
		Init(*pKunden, maxKunden, maxKunden * 2);
		(*pKunden)[maxKunden] = neuKunde;
		return maxKunden * 2;
	}
	
	return maxKunden;
}

int main(void)
{
	int maxKunden = MAX; /* initiale Feldgröße */
	tKunde** kunden = calloc(maxKunden, sizeof(tKunde*));
	
	Init(kunden, 0, maxKunden);
	maxKunden = Add(&kunden, maxKunden, "Anna", "Adam");
	maxKunden = Add(&kunden, maxKunden, "Bernd", "Bertram");
	maxKunden = Add(&kunden, maxKunden, "Carl", "Copper");
	maxKunden = Add(&kunden, maxKunden, "Detlev", "David");
	/* Weitere Aktionen: Anlegen, Löschen etc. */
	free(kunden[1]);
	kunden[1] = NULL;
	maxKunden = Add(&kunden, maxKunden, "Julia", "Bach");
	Print(kunden, maxKunden);
	return 0;
}
