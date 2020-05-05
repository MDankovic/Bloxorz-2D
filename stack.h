#pragma once

#include <stdlib.h>

//Stek
typedef struct stack
{
	int top;
	int max_size;
	int *arr;
} Stack;

//Kreira prazan stek i vraca nam pokazivac na njega
Stack *initStack(int n);

//Dodaje element na stek
int push(Stack *stek, int val);

//Skida jedan element sa steka ukoliko nije prazan
int pop(Stack *stek);

//Proverava da li je stek pun. Vraca 1 ako jeste
int isFull(Stack *stek);

//Proverava da li je stek prazan. Vraca 1 ako jeste
int isEmpty(Stack *stek);

int stackSize(Stack *stek);