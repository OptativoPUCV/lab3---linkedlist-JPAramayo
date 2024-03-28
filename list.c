#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List * newList = (List *)malloc(sizeof(List));
  assert(newList != NULL);
  newList->head = NULL;
  newList->tail = NULL;
  newList->current = NULL;
  return newList;
}

void * firstList(List * list) {
  if (list->head == NULL) return NULL;
  list->current = list->head;
  return list->current->data;
}

void * nextList(List * list) {
  if (list->current == list->tail || list->current == NULL)
    return NULL;

  
  list->current = list->current->next;
  return list->current->data;
}

void * lastList(List * list) {
  if (list->tail == NULL) return NULL;
  list->current = list->tail;
  return list->current->data;
}

void * prevList(List * list) {
  if (list->current == list->head  || list->current == NULL) return NULL;
  list->current = list->current->prev;
  return list->current->data;
}

void pushFront(List * list, void * data) {
  Node * newNode = createNode(data);
  if (list->head == NULL) {
    list->head = newNode;
    list->tail = newNode;
    return;
  }
  newNode->next = list->head;
  list->head->prev = newNode;
  list->head = newNode;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  Node * newNode = createNode(data);
  list->current->next = newNode;
  newNode->prev = list->current;
  list->tail = newNode;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
  list->current = list->tail;
  return popCurrent(list);
}

void * popCurrent(List * list) {
  int* dato = list->current->data;
  
  if (list->current == list->head) {
    list->head = list->head->next;
    list->head->prev = NULL;
    free(list->head->prev);
  }
  else if (list->current == list->tail) {
    list->tail = list->tail->prev;
    list->tail->next = NULL;
    free(list->tail->next);
  }
  else {
  Node* prevNode = list->current->prev;
  Node* nextNode = list->current->next;
      
  prevNode->next = list->current->next;
  nextNode->prev = list->current->prev;

  free(list->current);
  }
  return dato;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}