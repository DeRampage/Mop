#ifndef _LIST_H_
#define _LIST_H_

#include <stdlib.h>

/* adds an element to the list */
void GenAddElement(void* basis, void*newElement, void*(*fpNext)(void*), void(*fpSetNext)(void*,void*));

/* adds an element at the top of the list */
void GenAddElementTop(void* basis, void*newElement, void*(*fpNext)(void*), void(*fpSetNext)(void*,void*));

/* adds an element sorted */
void GenAddElementSorted(void* basis, void*newElement, void*(*fpNext)(void*), void(*fpSetNext)(void*,void*),int (*fpCompare)(void*,void*));

/* returns a copy of the list element */
void* GenCopyElement(void* in,size_t size);


#endif