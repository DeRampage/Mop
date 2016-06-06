// unter Debug / Plugins das Plugin "Linked List Visualization" öffnen und als Head "head" bzw "head2" eintragen
#include <stdio.h>
#include <stdlib.h>

typedef struct list {
	char* data;
	struct list * next;
} tList;

tList* CreateList(char* data) {
	tList* neu = calloc(1, sizeof(tList));
	// neu->next = NULL;
	neu->data = data;
	return neu;
}

tList* AddElement(tList* head, tList* neu)
{
	if (head == NULL)
		return neu;
	tList* it = head;
	while (it->next != NULL) {
		it = it -> next;
	}
	it -> next = neu;
	return head;
}

tList* PrintList(tList* head) {
	tList* idx = head;
	while(idx != NULL) {
		printf("%s ", idx->data);
		idx = idx->next;
	} 
}

void FreeList(tList* idx)
{
	while(idx) {
		tList* tmp = idx;
// nicht!	free(idx);
		idx = idx->next;
		free(tmp);
	}
}

int main(void){
	tList* head = CreateList("Kopf");
	head->next = CreateList("Mitte");
	head->next->next = CreateList("Fuß");
	PrintList(head);
	tList* head2 = AddElement(NULL, 
				CreateList("Start!"));
	head2 = AddElement(head2, head);
	PrintList(head2);
	FreeList(head2);
	head2 = NULL;
	head = NULL;
	PrintList(head);
	return 0;
}




