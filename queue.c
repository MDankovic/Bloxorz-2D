#include "queue.h"
#include <stdlib.h>

Queue *initQueue()
{
	Queue *queue = (Queue*)malloc(sizeof(Queue));
	queue->front = NULL;
	queue->rear = NULL;
	queue->size = 0;
	return queue;
}

qNode *new_qNode(int val)
{
	qNode *temp = (qNode*)malloc(sizeof(qNode));
	temp->info = val;
	temp->next = NULL;

	return temp;
}

// Dodaje element na kraj reda
int insert(Queue *queue, int val)
{
	qNode *temp = new_qNode(val);

	if (queue->rear == NULL) {
		queue->front = queue->rear = temp;
	}
	else {
		queue->rear->next = temp;
		queue->rear = temp;
	}

	queue->size += 1;

	return 1;
}

// Vraca i brise jedan element iz reda ukoliko nije prazan
int get(Queue *queue)
{
	if (queue->front == NULL)
		return NULL;

	qNode *tmp = queue->front;
	queue->front = queue->front->next;

	if (queue->front == NULL)
		queue->rear = NULL;

	queue->size -= 1;
	return tmp->info;
}

// Vraca velicinu reda
int sizeofQueue(Queue *queue)
{
	return queue->size;
}

// Proverava da li je red prazan. Vraca 1 ako jeste
int isEmptyQueue(Queue *queue)
{
	if (queue->front == NULL)
		return 1;
	return 0;
}