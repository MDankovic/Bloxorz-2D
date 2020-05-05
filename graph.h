#pragma once

#include <stdlib.h>
#include "queue.h"
#include "stack.h"

typedef enum { NORTH = 1, SOUTH, EAST, WEST, TEMP, NOT_CONNECTED } Direction;

typedef struct
{
	Direction **adjMat;
	int size;
	int S;
	int T;
} Graph;

void addEgde(Graph graph, int u, int v);

void deleteEdge(Graph graph, int u, int v);

int bfs(Graph graph, int v);

void dfs_visit(Graph graph, int v, int *visit);

int dfs(Graph graph);

int shortestPathBetween(Graph graph, int i, int j);

int numberOfConnectedComponents(Graph graph);

int **warshall(Graph graph);

void path(int **trace, int i, int j);

int **floyd(Graph graph);

void printGraph(Graph graph);

void deleteGraph(Graph graph);

void deleteEdge(Graph graph, int u, int v);

void addEdge(Graph graph, int u, int v);

int findNode(Graph graph, Direction dir, int v);

int hasConnection(Graph graph, Direction dir, int v);

Graph getField(int ***idMatrix, int *ysize, int *xsize);

int addTile(Direction ***adjm, int size, int **mat, int i, int j, int m, int n, int *s, int *t, int *pos);

int deleteTile(Direction ***adjm, int size, int **mat, int xcoor, int ycoor, int m, int n, int *s, int *t, int *pos);