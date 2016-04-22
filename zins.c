#define JAHR 365
#define HDT 100
#include <stdio.h>

float CountCentsFloat(unsigned int betrag);
double CountCentsDouble(unsigned int betrag);
float CalcFloatInterest(float amount, float intinPercent, int days);
double CalcDoubleInterest(double amount, double intinPercent, int days);
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
	
	6.)
	1 = 0,9999
	*/
	float sg = 1000.25; //einfache Genauigkeit
	double dg = 1000.25; //doppelte Genauigkeit
	
	unsigned int betrag = 0;
	
	printf("Bitte Betrag eingeben:");
	scanf("%ld", &betrag);
	
	printf("Mit Cents in Float gezaehlt ergibt: %.2f\n", CountCentsFloat(betrag));
	
	printf("Mit Cents in Double gezaehlt ergibt: %.2lF\n", CountCentsDouble(betrag));
	
	// Aufgabe 9
	printf("Bitte Zinssatz in %% eingeben:");
	double zins = 0;
	scanf("%f", &zins);
	printf("Laufzeit in Tagen eingeben:");
	int days = 0;
	scanf("%i", &days);
	printf("Die Zinsen mit Float betragen: %.2lf\n", CalcFloatInterest(betrag, (float)zins, days));
	
	//Aufgabe 10
	printf("Die Zinsen mit Double betragen: %.2lf\n", CalcDoubleInterest((double)betrag, zins, days));
	return 0;
}

float CountCentsFloat(int betrag) {
	float cent = 0.0f;
	for(int i = 0; i < betrag * HDT; i++) {
		cent = cent + (float)0.01;
	}
	return cent ;
}

double CountCentsDouble(int betrag) {
	double cent = 0.0f;
	for(int i = 0; i < (int) betrag * HDT; i++) {
		cent = cent + 0.01;
	}
	return cent;
}

//Funktioniert noch nicht richtig
float CalcFloatInterest(float amount, float intInPercent, int days) { 
	if(days < 1) {
		return amount;
	}
	float zins = 0;
	/*
	for(int i = 0; i < days; i++) {
		zins = amount * (intInPercent / JAHR);
		amount = zins + amount;
		printf("Tag: %d Amount: %f Zins: %f\n", i, amount, zins);
	}
	*/
	
	//Fuer ein Jahr
	zins = amount * intInPercent;
	return zins;
}

//noch nicht implementiert
double CalcDoubleInterest(double amount, double intInPercent, int days) { 
	if(days < 1) {
		return amount;
	}
	double zins = amount;
	
	return zins;
}