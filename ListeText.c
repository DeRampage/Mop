#include <stdio.h>
#include <stdlib.h>

typedef struct list {
	struct list *next;
	char* data[1];
} tList;

tList* neu = malloc (sizeof(tList));

tList * CreateWord (char * word) {
	neu->next = 'NULL';
	neu->data = word;
	return neu;	
}

tList* AddElement (tList* head, char* word) {
	if(head == NULL) {
		tList* neu = calloc(1, sizeof(tList));
		neu->next = NULL;
		neu->data = word;
		return neu->data;
	} else {
			
	}
}

int main(void){
	char* bimbam = CreateWord("Hallo");
	/*
	tList* head = AddElement(NULL, "Kopf");
	AddElement(AddElement(head, "bis"), "Fuss");
	*/
	return 0;
}