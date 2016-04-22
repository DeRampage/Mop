#include <stdio.h>

float CountCentsFloat(unsigned int betrag);

int main(void){
	/* Protokollblatt
	1. und 2.)
	
	//Werte fuer sg
	// Fuer 0.01 = 0a d7 23 3c
	// Fuer 0.25 = 00 00 80 3e
	
	// Werte fuer dg
	// Fuer 0.01 = 7b 14 ae 47 e1 7a 84 3f
	// Fuer 0.25 = 00 00 00 00 00 00 d0 3f
	
	5.)
	153
	*/
	float sg = 0.25; //einfache Genauigkeit
	double dg = 0.25; //doppelte Genauigkeit
	
	unsigned int betrag = 0;
	
	printf("Bitte Betrag eingeben:");
	scanf("%u", &betrag);
	printf("Mit Cents in Float gezaehlt ergibt: %.2f", CountCentsFloat(betrag));
	return 0;
}

float CountCentsFloat(unsigned int betrag) {
	int b = 0;
	while (b < (int) betrag) {
		b++;
	}
	float cent = 0.0f;
	int i;
	for(i = 0; i < b * 100; i++) {
		cent = cent + 0.01;
	}
	return cent;
}