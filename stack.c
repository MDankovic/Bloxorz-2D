#pragma once

#include <stdlib.h>
#include "stack.h"

// Kreira prazan stek i vraca nam pokazivac na njega
Stack *initStack(int n)
{
	Stack *stek = (Stack*)malloc(sizeof(Stack));
	stek->arr = (int*)calloc(n, sizeof(int));
	stek->top = -1;
	stek->max_size = n;
	return stek;
}

// Dodaje element na stek
int push(Stack *stek, int val)
{
	stek->top = stek->top + 1;
//	if (stek->top == stek->max_size) {
//		stek->top--;
//		return 0;
//	}

	stek->arr[stek->top] = val;
	return 1;
}

// Skida jedan element sa steka ukoliko nije prazan
int pop(Stack *stek)
{
	if (!(stek->top == -1))
		return stek->arr[stek->top--];
	return INT_MIN;
}

// Proverava da li je stek pun. Vraca 1 ako jeste
int isFull(Stack *stek)
{
	if (stek->top == stek->max_size - 1)
		return 1;
	return 0;
}

// Proverava da li je stek prazan. Vraca 1 ako jeste
int isEmpty(Stack *stek)
{
	if (stek->top == -1)
		return 1;
	return 0;
}

int stackSize(Stack *stek)
{
	return stek->top + 1;
}