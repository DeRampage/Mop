#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* include generic list functions */
#include "list.h"



typedef struct listTyp
{
	char surname[32];
	char name[32];
	unsigned long number;
	struct listTyp* next;
} tStudent;


tStudent* ReadElement(FILE *f)
{
	tStudent*newElement = malloc(sizeof(tStudent));
	if (newElement)
	{
		newElement->next = NULL;
		fscanf(f,"%s %s %ld",newElement->surname, newElement->name, &newElement->number);
	}
	return newElement;
}


/* ToDo: Vergleichsfunktionen */

int CompareName(void* a,void*b){
	tStudent *ap = a, *bp = b;
	return strcmp((ap)->name, (bp)->name);
}
int CompareSurname(void* a,void*b){
	tStudent *ap = a, *bp = b;
	return strcmp((ap)->surname, (bp)->surname);
}
int CompareNumber(void* a,void*b){
	tStudent *ap = a, *bp = b;
	return (((ap)->number) - ((bp)->number));
}


/* ToDo: Zugriffsfunktionen schreiben */

void* TStudentNext(void*in){
	return (((tStudent*)in)->next);
}
void TStudentSetNext(void*in,void*next) {
	tStudent* element = (tStudent*) next;
	(((tStudent*)in)->next) = element;
}


void PrintList(tStudent* basis)
{
	printf("%-16s%-16s%-16s\n","Vorname","Name", "Matrikelnummer");
	printf("==============================================\n");
	basis = basis->next; // skip dummy
	while(basis)
	{
		printf("%-16s%-16s%-16d\n",basis->surname, basis->name, basis->number);
		basis = basis->next;
	}
}

void main(void)
{
	FILE *f;
	tStudent liste1 = { "","",0,NULL }; /* dummy element */
	tStudent liste2 = { "","",0,NULL }; /* dummy element */
	int sort=0;
	
	printf("**************** unsortiert *****************\n");
	f=fopen("studenten.txt","r");
	if (f)
	{
		while(!feof(f))
		{
			tStudent* newElement = ReadElement(f);
		    GenAddElement(&liste1,newElement,TStudentNext,TStudentSetNext);
		}
		fclose(f);
	}
	
	PrintList(&liste1);
    
	printf("Sortierung: 0-Name, 1-Vorname, 2-Nummer? ->");
	scanf("%d",&sort);
	printf("***************** sortiert ******************\n");
	f=fopen("studenten.txt","r");
	if (f)
	{
		while(!feof(f))
		{
   			tStudent* newElement = ReadElement(f);
		    switch(sort)
		    {
			   case 0: GenAddElementSorted(&liste2,newElement,TStudentNext,TStudentSetNext,CompareName);
					   break;
			   case 1: GenAddElementSorted(&liste2,newElement,TStudentNext,TStudentSetNext,CompareSurname);
					   break;
			   case 2: GenAddElementSorted(&liste2,newElement,TStudentNext,TStudentSetNext,CompareNumber);
					   break;
			   default:break;
			}
		}
		fclose(f);
	}
    
	PrintList(&liste2);
}
