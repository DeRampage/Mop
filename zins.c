#define JAHR 365
#define HDT 100
#include <stdio.h>

float CountCentsFloat(unsigned int betrag);
double CountCentsDouble(unsigned int betrag);

float CalcFloatInterest(float amount, float intinPercent, int days);
double CalcDoubleInterest(double amount, double intinPercent, int days);

int CalcSaveTimeFloat(float amount, float intInPercent);
int CalcSaveTimeDouble(double amount, double intInPercent);

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
	float sg = 0.25; //einfache Genauigkeit
	double dg = 0.25; //doppelte Genauigkeit
	
	unsigned int betrag = 0;
	
	printf("Bitte Betrag eingeben:");
	scanf("%ld", &betrag);
	
	printf("Mit Cents in Float gezaehlt ergibt: %.2f\n", CountCentsFloat(betrag));
	
	printf("Mit Cents in Double gezaehlt ergibt: %.2lF\n", CountCentsDouble(betrag));
	
	// Aufgabe 9
	printf("Bitte Zinssatz in %% eingeben: ");
	float zins = 0;
	scanf("%f", &zins);
	printf("Laufzeit in Tagen eingeben: ");
	int days = 0;
	scanf("%i", &days);
	printf("Die Zinsen mit Float betragen: %.2f\n", CalcFloatInterest(betrag, zins , days));
	
	//Aufgabe 10
	printf("Die Zinsen mit Double betragen: %.2lf\n", CalcDoubleInterest(betrag, zins, days));
	
	//Aufgabe 11
	printf("Tage zu sparen mit Float: %d\n", CalcSaveTimeFloat(betrag, zins));
	printf("Tage zu sparen mit Double: %d\n", CalcSaveTimeDouble(betrag, zins));
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

float CalcFloatInterest(float amount, float intInPercent, int days) { 
	intInPercent = intInPercent / HDT;
	float zins = amount;
	for(int i = 0; i < days; i++) {
		zins = (float)zins * (1.0 + intInPercent / JAHR);
	}
	return zins - amount;
}

double CalcDoubleInterest(double amount, double intInPercent, int days) { 
	intInPercent = intInPercent / HDT;
	double zins = amount;
	for(int i = 0; i < days; i++) {
		zins = zins * (1 + intInPercent / JAHR);
	}
	return zins - amount;
}

int CalcSaveTimeFloat(float amount, float intInPercent) {
	int days = 0;
	intInPercent = intInPercent / HDT;
	float i = 0.00;
	while(i < amount) {
		i = i + (float)0.01;
		i = i + i * (intInPercent / JAHR);
		days++;
	}
	return days;
}


int CalcSaveTimeDouble(double amount, double intInPercent){
	int days = 0;
	double i = 0.0f;
	while(i < amount) {
		i = i + 0.01;
		i = i + i * (intInPercent / HDT / JAHR);
		days++;
	}
	return days;
}