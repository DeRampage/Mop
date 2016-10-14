#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int addInt (int n, int m);
int(*functionPtr)(int, int);
int (*functionFactory(int n))(int, int);

int main(void){
	
	functionPtr = &addInt;
	printf("Einfacher Pointer\n");
	printf("Die Zahl ist: %d\n\n", (*functionPtr)(1,2));
	printf(" Pointer in Funktion\n");
	printf("Die Zahl ist: %d\n", functionFactory(5));
}
int addInt(int n, int m) {
    return n+m;
}
int (*functionFactory(int n))(int, int) {
    printf("Got parameter %d\n", n);
    int (*functionPtr)(int,int) = &addInt;
    return functionPtr;
}