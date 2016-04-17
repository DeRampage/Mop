#define ZTSD 10000 //speichert die Zehntausend
#define HTSD 100000 //speicher die Tausend
#define MAX_GS 27 //Maximaler Wert für den Goldenen Schnitt
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

long FibRekursiv(int n);
long GoldSchnitt(int n);
int OptimumLength (int n, int b);
int main(void){
	int n=0;
	printf("Bitte Eingabe machen:");
	scanf("%d", &n);
	printf("Die Fibo Zahl ist: %d\n", FibRekursiv(n));
	
	if(n <= 1) { //Abbruch: Keine Division durch 0
		printf("Fehler: Die Eingabe ist zu klein!");
		return 0;
	}
	
	if(n > MAX_GS) { //Abbruch: Keine Berechnung moeglich
		printf("Fehler: Die Eingabe ist zu groß!");
		return 0;
	}
	
	printf("Der Goldene Schnitt betraegt: %d,%d\n", GoldSchnitt(n) / ZTSD, GoldSchnitt(n) % ZTSD / 10);
	char a[2] = {0, 0};
	int b = 0;
	printf("Die Breite b in Meter eingeben:");
	scanf("%d,%s", &b, &a);
	
	if(!isdigit(a[0]) || a[0] == '\0') {
		printf("Fehler: Nachkomma muss (als Zahl) angegeben werden!");
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
		printf("Die ideale Laenge betraegt: %d,%d m\n", OptimumLength(n, b) / ZTSD , OptimumLength(n, b) % HTSD / 10 / 10);
	}
	return 0;
}

long FibRekursiv(int n) {//Fibo Zahl ermitteln
	if(n == 0) {
		return 0;
	}
	if(n == 1) {
		return 1;
	}
	return FibRekursiv(n - 1) + FibRekursiv( n - 2);
}

long GoldSchnitt (int n) { //Goldenen Schnitt mit Nachkommastellen berechnen!
	n = FibRekursiv(n) * ZTSD / FibRekursiv(n - 1);
	n = n + 5;
	return n;
}

int OptimumLength (int n, int b) {
	return GoldSchnitt(n) * b / 10;
}