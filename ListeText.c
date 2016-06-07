#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list {
	struct list *next;
	char data[1];
} tList;


tList* CreateWord (char * word) {						//erzeugt neues listenelement u. setzt next = null
	tList* neu = calloc(1, sizeof(tList) + strlen(word));//Platz fürListe + Wordlaenge freigeben
	neu->next = NULL;									
	strcpy(neu->data, word);								//Fuegt das Wort an der ersten Stelle ein
	return neu;	
}

tList* AddElement (tList* head, char* word) {
	if(head == NULL) {									//Leere Liste? CreateWord!
		tList* neu = CreateWord(word);
		return neu;
	} else {												//Liste ist nicht leer
		tList* temporary = head;							//durchlaufzeiger erstellen
		while(temporary->next != NULL) {					//Liste bis zum Ende durchlaufen
			temporary = temporary->next;					//Einen Schritt weitergehen
		}
		temporary->next = CreateWord(word);				//Wort einfügen
		return head;
	}
}

tList* AddElementTop (tList* head, char* word) {
	if(head == NULL) {									//Leere Liste? CreateWord!
		tList* neu = CreateWord(word);
		return neu;
	} else {												//Liste ist nicht leer
		tList* temporary = CreateWord(word);
		temporary->next = head;			
		return temporary;
	}
}

void PrintList(tList* head) {
	while(head->next != NULL) {
		printf("%s ", head->data);
		head = head->next;
	}
	printf("%s\n", head->data);
}

tList* ReadText (void) {
	char string[1024];
	int abort = 0;
	tList* list = NULL;
	printf("Geben Sie bitte Ihren Text ein: ");
	while(abort == 0) {
		scanf("%1024s", string);
		if(list == NULL) {
			list = CreateWord(string);
		} else {
			AddElement(list, string);
		}
		if(strcmp(string, ".") == 0) {
			abort = 1;
		}
	}
	return list;
}

tList* InReplaceWord(tList* head, char* suchwort, char* ersetzwort) {
	tList* temporary = head;
	if(strcmp(temporary->data, suchwort) == 0) {
			tList* neu = CreateWord(ersetzwort);
			neu->next = temporary->next;
			head = neu;
			temporary = head;
		}
	while(temporary){
		if(strcmp(temporary->next->data, suchwort) == 0) {
			tList* neu = CreateWord(ersetzwort);
			neu->next = temporary->next->next;
			temporary->next = neu;
		}
		temporary = temporary->next;
	}
	return head;
}

tList* CopyReverse(tList* original) {
	tList* temporary = original;
	tList* neu = NULL;
	while(temporary) {
		neu = AddElementTop(neu, temporary->data);
		temporary = temporary->next;
	}
	return neu;
}

int main(void){
	/*
	tList* neu = CreateWord("Hallo");
	
	tList* head = AddElement(NULL, "Kopf");
	AddElement(AddElement(head, "bis"), "Fuss");
	*/
	
	tList* newHead = AddElementTop(
						AddElementTop(
							AddElementTop(NULL, "Fuss"), "bis"), "Kopf");
	
	PrintList(newHead);
	newHead = CopyReverse(newHead);
	PrintList(newHead);
	/*
	tList* einlesen = ReadText();
	PrintList(einlesen);
	
	char suchwort[1024];
	char ersetzwort[1024];
	printf("Gesuchtes Wort ist: ");
	scanf("%1023s", &suchwort);
	printf("Ersetzendes Wort ist: ");
	scanf("%1023s", &ersetzwort);
	
	einlesen = InReplaceWord(einlesen, suchwort, ersetzwort);
	PrintList(einlesen);
	*/
	return 0;
}