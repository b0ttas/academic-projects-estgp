#include <stdio.h>
#include <stdlib.h>
#include "list.h"

//implementação das funções do nó
NODE* createNode(NODE* previous, NODE* next, ITEM item){
	NODE* newNode = NULL;

	newNode = (NODE*) malloc(sizeof(NODE));
	newNode->next = next;
	newNode->previous = previous;
	newNode->item = item;

	return newNode;
}

void deleteNode(NODE* node){
	free(node);
}

//implementação das funções da lista
LIST* createList(){
	LIST* list;

	list = (LIST*) malloc(sizeof(LIST));
	list->start = NULL;
	list->end = NULL;
	list->size = 0;
	return list;
}

void deleteList(LIST* list){
	NODE* aux;

	if(listIsEmpty(list) == 0){
		aux = list->start->next;
		while(aux != NULL){
			deleteNode(aux->previous);
			aux = aux->next;
		}
		deleteNode(list->end);
		list->start = NULL;
		list->end = NULL;
		list->size = 0;
	}
}

void insertOnStart(LIST* list, ITEM item){
	NODE* newNode;

	if(listIsEmpty(list) == 1){
		newNode = createNode(NULL, NULL, item);
		list->start = newNode;
		list->end = newNode;
	}else{
		newNode = createNode(NULL, list->start, item);
		list->start->previous = newNode;
		list->start = newNode;
	}
	(list->size)++;
}

void insertOnEnd(LIST* list, ITEM item){
	NODE* newNode;
	if(listIsEmpty(list) == 1){
		newNode = createNode(NULL, NULL, item);
		list->start = newNode;
		list->end = newNode;
	}else{
		newNode = createNode(list->end, NULL, item);
		list->end->next = newNode;
		list->end = newNode;
	}
	(list->size)++;
}


NODE* getNodeInPosition(LIST* list, int position){
	int i=0;
	NODE* iterator = list->start;
	for(i=0;i<position;i++,iterator=iterator->next);
	return iterator;
}

void insertOnPosition(LIST* list, ITEM item, int position){
	NODE* aux;
	NODE* newNode;

	if(position <= 0)
		insertOnStart(list, item);
	else if(position >= list->size)
		insertOnEnd(list, item);
	else{
		aux = getNodeInPosition(list, position);
		newNode = createNode(aux->previous, aux, item);
		aux->previous->next = newNode;
		aux->previous = newNode;

		(list->size)++;
	}
}

ITEM removeOnStart(LIST* list){
	ITEM item;
	NODE* aux;

	item = list->start->item;
	aux = list->start;

	if(listIsEmpty(list) == 0){
		if(aux->next != 0){
			list->start = aux->next;
			list->start->previous = NULL;
		}else{
			list->start = NULL;
			list->end = NULL;
		}
		deleteNode(aux);
		(list->size)--;
	}

	return item;
}

ITEM removeOnEnd(LIST* list){
	ITEM item;
	NODE* aux;

	item = list->end->item;
	aux = list->end;

	if(listIsEmpty(list) == 0){
		if(aux->previous != 0){
			list->end = aux->previous;
			list->end->next = NULL;
		}else{
			list->start = NULL;
			list->end = NULL;
		}
		deleteNode(aux);
		(list->size)--;
	}

	return item;
}

ITEM removeOnPosition(LIST* list, int position){
	NODE* aux;
	ITEM item;

	if(position <= 0)
		item = removeOnStart(list);
	else if(position >= list->size)
		item = removeOnEnd(list);
	else{
		aux = getNodeInPosition(list, position);
		aux->previous->next = aux->next;
		aux->next->previous = aux->previous;

		item = aux->item;
		deleteNode(aux);
		(list->size)--;
	}

	return item;
}

ITEM getOnStart(LIST* list){
	if(listIsEmpty(list) == 0)
		return list->start->item;
	else
		return 0;
}

ITEM getOnEnd(LIST* list){
	if(listIsEmpty(list) == 0)
		return list->end->item;
	else
		return 0;
}

ITEM getOnPosition(LIST* list, int position){
	ITEM item;
	NODE* aux;

	if(position <= 0)
		item = getOnStart(list);
	else if(position >= list->size)
		item = getOnEnd(list);
	else{
		aux = getNodeInPosition(list, position);
		item = aux->item;
	}

	return item;
}

int getSizeOfList(LIST* list){
	return list->size;
}

int listIsEmpty(LIST* list){
	if(list->size == 0)
		return 1;
	else
		return 0;
}

LIST* joinLists(LIST* list1, LIST* list2){
	int i=0;
	LIST* list;
	NODE* aux;

	list = createList();

	aux = list1->start;
	while(i<list1->size){
		insertOnEnd(list, aux->item);
		aux = aux->next;
		i++;
	}
	deleteList(list1);

	i=0;
	aux = list2->start;
	while(i< list2->size){
		insertOnEnd(list, aux->item);
		aux = aux->next;
		i++;
	}
	deleteList(list2);

	return list;
}

//implementação das funções do iterador
ITERATOR* initIterator(LIST* list, int direction){
	ITERATOR* it = NULL;
	it = (ITERATOR*) malloc(sizeof(ITERATOR));
	it->direction = direction;

	if(!direction)
		it->pointer = list->start;
	else
		it->pointer = list->end;
	return it;
}

void itGoNext(ITERATOR* it){
	if(!it->direction)
		it->pointer = it->pointer->next;
	else
		it->pointer = it->pointer->previous;
}

int itIsEnd(ITERATOR* it){
	return (it->pointer == 0);
}

ITEM itGetItem(ITERATOR* it){
	return it->pointer->item;
}

ITEM* itGetPointerItem(ITERATOR* it){
	return &(it->pointer->item);
}