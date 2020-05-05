#pragma once

#include <stdlib.h>

typedef struct
{
	int info;
	struct qnode *next;
} qNode;

typedef struct
{
	qNode *front;
	qNode *rear;
	int size;
} Queue;

Queue *initQueue();

qNode *new_qNode(int val);

//Dodaje element na kraj reda
int insert(Queue *queue, int val);

//Vraca i brise jedan element iz reda ukoliko nije prazan
int get(Queue *queue);

int sizeofQueue(Queue *queue);

//Proverava da li je red prazan. Vraca 1 ako jeste
int isEmptyQueue(Queue *queue);