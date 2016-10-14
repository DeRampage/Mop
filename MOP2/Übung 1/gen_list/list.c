#include <string.h>
#include "list.h"

/* Generic List ********************************************************/

/* adds an element at the end of the list */
void GenAddElement(void* basis, void *newElement, void*(*fpNext)(void*), void(*fpSetNext)(void*,void*))
{
	/* Adds element to the end of the list "basis" */
	void* next=NULL; /* next element */
	while(next=fpNext(basis))
	{
		basis = next; /* basis: local index */
	}
	fpSetNext(basis,newElement);
}

/* adds an element at the top of the list */
void GenAddElementTop(void* basis, void*newElement, void*(*fpNext)(void*), void(*fpSetNext)(void*,void*))
{
	if (newElement)
	{	/* Adds element to the top of the list "basis" */
		fpSetNext(newElement,fpNext(basis));
		fpSetNext(basis,newElement);
	}
}

/* adds an element sorted */
void GenAddElementSorted(void* basis, void*newElement, void*(*fpNext)(void*), void(*fpSetNext)(void*,void*),int (*fpCompare)(void*,void*))
{
	if (newElement)
	{	/* Adds an element at the correct position in the list "basis" according to fpCompare */
		void* idx = fpNext(basis);
		void* pre = basis; /* predecessor */
		while(idx)
		{
			if (fpCompare(newElement,idx)<0)
			{
				fpSetNext(pre,newElement); // pre->next = newElement;
				fpSetNext(newElement,idx);
				return;				
			} 
			pre=idx;
			idx=fpNext(idx);
		}
		/* not yet in the list, so add at the end */
		fpSetNext(pre,newElement);
	}
}

/* returns a copy of the list element */
void* GenCopyElement(void* in,size_t size,void(*fpSetNext)(void*,void*))
{
	void* newElement = malloc(size);
	memcpy(newElement,in,size);
	return newElement;
}
