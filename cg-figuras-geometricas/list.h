#ifndef LIST_H
#define LIST_H

//includes
#include <stdio.h>
#include <stdlib.h>

//typedefs
typedef void* ITEM;
typedef struct node NODE;
typedef struct list LIST;
typedef struct iterator ITERATOR;


//struct node
struct node{
	NODE* next;
	NODE* previous;
	ITEM item;
};

//funções do nó
NODE* createNode(NODE* previous, NODE* next, ITEM item);
void deleteNode(NODE* node);

//struct list
struct list{
	NODE* start;
	NODE* end;
	int size;
};

//funções da lista
LIST* createList();
void deleteList(LIST* list);

void insertOnStart(LIST* list, ITEM item);
void insertOnEnd(LIST* list, ITEM item);
void insertOnPosition(LIST* list, ITEM item, int position);

ITEM removeOnStart(LIST* list);
ITEM removeOnEnd(LIST* list);
ITEM removeOnPosition(LIST* list, int position);

ITEM getOnStart(LIST* list);
ITEM getOnEnd(LIST* list);
ITEM getOnPosition(LIST* list, int position);

int getSizeOfList(LIST* list);
int listIsEmpty(LIST* list);
LIST* joinLists(LIST* list1, LIST* list2);

//struct iterator
struct iterator{
	NODE* pointer;
	int direction;
	//valor 0 indica do inicio para o fim,
	//o valor 1 indica o inverso
};

//funções do iterador
ITERATOR* initIterator(LIST* list, int direction);
void itGoNext(ITERATOR* it);
int itIsEnd(ITERATOR* it);

ITEM itGetItem(ITERATOR* it);
ITEM* itGetPointerItem(ITERATOR* it);

#endif // LIST_H
