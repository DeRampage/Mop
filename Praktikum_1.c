#define TSD 1000 //speicher die Tausend
#define ZTSD 10000
#define MAX_GS 47 //Maximaler Wert für den Goldenen Schnitt
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

long FibRekursiv(long n);
long GoldSchnitt(long n);
int OptimumLength (int n, int b);

int main(void){
	long n=0;
	printf("Bitte Eingabe machen:");
	scanf("%ld", &n);
	printf("Die Fibo Zahl ist: %d\n", FibRekursiv(n));
	
	if(n <= 1) { //Abbruch: Keine Division durch 0
		printf("Fehler: Die Eingabe ist zu klein!");
		return 0;
	}
	
	if(n > MAX_GS) { //Abbruch: Keine Berechnung moeglich
		printf("Fehler: Die Eingabe ist zu groß!");
		return 0;
	}
	
	printf("Der Goldene Schnitt betraegt: %ld,%ld\n", GoldSchnitt(n) / TSD, GoldSchnitt(n) % TSD);
	char a[2] = {0, 0};
	int b = 0;
	printf("Die Breite b in Meter eingeben:");
	scanf("%d,%s", &b, &a);
	
	if(!isdigit(a[0]) || a[0] == '\0') {
		printf("Fehler: Nachkomma muss als Zahl angegeben werden!");
		return 0;
	}
	
	if(a[1] != '\0' || a[0] == '.') {
		printf("Fehler: Nur ein Nachkomma/ Trennung mit Punkt!");
		return 0;
	}
	if(b < 0) {
		printf("Fehler: Breite muss positiv sein!");
		return 0;
	}
	else {
		b = b * 10 + atoi(a);
		printf("Die ideale Laenge betraegt: %d,%2d m\n", OptimumLength(n, b) / TSD , OptimumLength(n, b) % TSD /10);
	}
	return 0;
}

long FibRekursiv(long n) {//Fibo Zahl ermitteln
	if(n == 0) {
		return 0;
	}
	if(n == 1) {
		return 1;
	}
	return FibRekursiv(n - 1) + FibRekursiv( n - 2);
}

long GoldSchnitt (long n) { //Goldenen Schnitt mit Nachkommastellen berechnen!
	if((((FibRekursiv(n) * ZTSD) / FibRekursiv(n - 1)) % ZTSD) > 4) {
		n = FibRekursiv(n) * TSD / FibRekursiv(n - 1) + 1;
	} 
	else {
		n = FibRekursiv(n) * TSD / FibRekursiv(n - 1);
	}
	return n;
}

int OptimumLength (int n, int b) {
	return GoldSchnitt(n) * b / 10;
}