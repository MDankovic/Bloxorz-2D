#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "stack.h"
#include "graph.h"
#include <Windows.h>

int checkConnection(int **mat, int i, int j, int m, int n)
{
	if (i < 0 || i > m || j < 0 || j > n)
		return -1;
	else if (mat[i][j] == -1)
		return -1;
	else
		return mat[i][j];	
}

int addTile(Direction ***adjm, int size, int **mat, int xcoor, int ycoor, int m, int n, int *s, int *t, int *pos)
{
	if (xcoor < 0 || xcoor >= m || ycoor < 0 || ycoor >= n)
		printf("Coordinates out of map!\n");
	else if (mat[xcoor][ycoor] != -1)
		printf("Tile already there!\n");
	else {
		int id = 0;
		for (int p = 0; p < m; p++) {
			for (int q = 0; q < n; q++) {
				if (p * n + q < xcoor * n + ycoor) {
					if (mat[p][q] != -1) {
						id = mat[p][q];
					}
				}
				else if (p == xcoor && q == ycoor) {
					if(id != 0)
						id++;
					//printf("new id: %d\n\n", id);
					if (*s >= id) {
						*s += 1;
					}
					if (*t >= id) {
						*t += 1;
						//printf("povecao t");
						//Sleep(3000);
					}
					if (*pos >= id) {
						*pos += 1;
					}
					//printf("\npostavio id");
					//Sleep(3000);
					mat[p][q] = id;
				}
				else {
					if (mat[p][q] != -1) {
						mat[p][q]++;
					}
				}
			}
		}

		*adjm = realloc(*adjm, (size + 1) * sizeof(Direction *));
		(*adjm)[size] = calloc(size + 1, sizeof(Direction));

		size++;
		for (int p = 0; p < size; p++) {
			(*adjm)[p] = realloc((*adjm)[p], size * sizeof(Direction));
		}

		// Shifting right
		for (int p = size - 1; p > id; p--) {
			for (int q = 0; q < size - 1; q++) {
				//printf("p = %d q = %d\n", p, q);
				(*adjm)[p][q] = (*adjm)[p - 1][q];
			}
		}
		for (int p = size - 1; p > id; p--) {
			for (int q = size - 1; q > id; q--) {
				(*adjm)[p][q] = (*adjm)[p][q - 1];
			}
		}

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				(*adjm)[i][j] = NOT_CONNECTED;
			}
		}
		/*
		printf("\n\n\n");
		printf("\t");
		for (int i = 0; i < size; i++) {
			printf("%02d ", i);
		}
		printf("\n");
		for (int i = 0; i < size; i++) {
			printf("%02d.\t", i);
			for (int j = 0; j < size; j++) {
				printf("%-2d ", (*adjm)[i][j]);
			}
			printf("\n");
		}
		*/
		int edge;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				//printf("%d ", mat[i][j]);
				if (mat[i][j] != -1) {
					//printf("mat[%d][%d] = %d\n", i, j, mat[i][j]);
					if ((edge = checkConnection(mat, i - 1, j, m - 1, n - 1)) != -1) {
						(*adjm)[mat[i][j]][edge] = NORTH;
						//printf("\tN -> mat[%d][%d] = %d\n", i-1, j, mat[i-1][j]);
					}

					if ((edge = checkConnection(mat, i, j - 1, m - 1, n - 1)) != -1) {
						(*adjm)[mat[i][j]][edge] = WEST;
						//printf("\tW -> mat[%d][%d] = %d\n", i, j - 1, mat[i][j - 1]);
					}

					if ((edge = checkConnection(mat, i + 1, j, m - 1, n - 1)) != -1) {
						(*adjm)[mat[i][j]][edge] = SOUTH;
						//printf("\tS -> mat[%d][%d] = %d\n", i + 1, j, mat[i + 1][j]);
					}

					if ((edge = checkConnection(mat, i, j + 1, m - 1, n - 1)) != -1) {
						(*adjm)[mat[i][j]][edge] = EAST;
						//printf("\tE -> mat[%d][%d] = %d\n", i, j + 1, mat[i][j + 1]);
					}
				}
			}
			//printf("\n");
		}
		//Sleep(20000);
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if ((*adjm)[i][j] != NORTH && (*adjm)[i][j] != WEST &&
					(*adjm)[i][j] != SOUTH && (*adjm)[i][j] != EAST)
					(*adjm)[i][j] = NOT_CONNECTED; ///VODI RACUNA!!!!!!!
			}
		}
		/*
		printf("\n\n\n");
		printf("\t");
		for (int i = 0; i < size; i++) {
			printf("%02d ", i);
		}
		printf("\n");
		for (int i = 0; i < size; i++) {
			printf("%02d.\t", i);
			for (int j = 0; j < size; j++) {
				printf("%-2d ", (*adjm)[i][j]);
			}
			printf("\n");
		}
		Sleep(40000);
		*/
	}
	return size;
}

int deleteTile(Direction ***adjm, int size, int **mat, int xcoor, int ycoor, int m, int n, int *s, int *t, int *pos)
{
	if (xcoor < 0 || xcoor >= m || ycoor < 0 || ycoor >= n) {
		printf("Coordinates out of map!\n");
		printf("\n\nPress enter to continue. . .");
		_getch();
	}
	else if (mat[xcoor][ycoor] == -1) {
		printf("No tile there!\n");
		printf("\n\nPress enter to continue. . .");
		_getch();
	}
	else if (mat[xcoor][ycoor] == *s) {
		printf("Can't remove start!\n");
		printf("\n\nPress enter to continue. . .");
		_getch();
	}
	else if (mat[xcoor][ycoor] == *t) {
		printf("Can't remove finish!\n");
		printf("\n\nPress enter to continue. . .");
		_getch();
	}
	else if (mat[xcoor][ycoor] == *pos) {
		printf("Can't remove current position!\n");
		printf("\n\nPress enter to continue. . .");
		_getch();
	}
	else {
		int id = 0;
		for (int p = 0; p < m; p++) {
			for (int q = 0; q < n; q++) {
				if (p * n + q < xcoor * n + ycoor) {
					if (mat[p][q] != -1) {
						id = mat[p][q];
					}
				}
				else if (p == xcoor && q == ycoor) {
					if (id != 0)
						id++;
					if (*s >= id) {
						*s -= 1;
					}
					if (*t >= id) {
						*t -= 1;
					}
					if (*pos >= id) {
						*pos -= 1;
					}
					mat[p][q] = -1;
				}
				else {
					if (mat[p][q] != -1) {
						mat[p][q]--;
					}
				}
			}
		}

		// Shifting left
		for (int p = id; p < size - 1; p++) {
			for (int q = 0; q < size; q++) {
				(*adjm)[p][q] = (*adjm)[p + 1][q];
			}
		}
		for (int p = 0; p < size; p++) {
			for (int q = id; q < size - 1; q++) {
				(*adjm)[p][q] = (*adjm)[p][q + 1];
			}
		}

		*adjm = realloc(*adjm, (size - 1) * sizeof(Direction *));
		size--;

		for (int p = 0; p < size; p++) {
			(*adjm)[p] = realloc((*adjm)[p], size * sizeof(Direction));
		}

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				(*adjm)[i][j] = NOT_CONNECTED;
			}
		}
		
		int edge;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				//printf("%d ", mat[i][j]);
				if (mat[i][j] != -1) {
					//printf("mat[%d][%d] = %d\n", i, j, mat[i][j]);
					if ((edge = checkConnection(mat, i - 1, j, m - 1, n - 1)) != -1) {
						(*adjm)[mat[i][j]][edge] = NORTH;
						//printf("\tN -> mat[%d][%d] = %d\n", i-1, j, mat[i-1][j]);
					}

					if ((edge = checkConnection(mat, i, j - 1, m - 1, n - 1)) != -1) {
						(*adjm)[mat[i][j]][edge] = WEST;
						//printf("\tW -> mat[%d][%d] = %d\n", i, j - 1, mat[i][j - 1]);
					}

					if ((edge = checkConnection(mat, i + 1, j, m - 1, n - 1)) != -1) {
						(*adjm)[mat[i][j]][edge] = SOUTH;
						//printf("\tS -> mat[%d][%d] = %d\n", i + 1, j, mat[i + 1][j]);
					}

					if ((edge = checkConnection(mat, i, j + 1, m - 1, n - 1)) != -1) {
						(*adjm)[mat[i][j]][edge] = EAST;
						//printf("\tE -> mat[%d][%d] = %d\n", i, j + 1, mat[i][j + 1]);
					}
				}
			}
			//printf("\n");
		}
		//Sleep(20000);
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if ((*adjm)[i][j] != NORTH && (*adjm)[i][j] != WEST &&
					(*adjm)[i][j] != SOUTH && (*adjm)[i][j] != EAST)
					(*adjm)[i][j] = NOT_CONNECTED; ///VODI RACUNA!!!!!!!
			}
		}
		
	}
	return size;
}

// Vraca cvor koji je sa "dir" strane zadatog cvora v ili -1 ako ne postoji
// dir = {NORTH, SOUTH, WEST, EAST}
int findNode(Graph graph, Direction dir, int v)
{
	for (int i = 0; i < graph.size; i++)
		if (graph.adjMat[v][i] == dir)
			return i;

	return -1;
}

// Isto sto i prethodna mrzi me da menjam ime u dz3.c fajlu
int hasConnection(Graph graph, Direction dir, int v)
{
	for (int i = 0; i < graph.size; i++)
		if (graph.adjMat[v][i] == dir)
			return i;

	return -1;
}

Graph getField(int ***idMatrix, int *ysize, int *xsize)
{
	char filename[256];
	printf("Map location is: ");
	scanf("%s", &filename);
	system("cls");
	FILE *file = fopen(filename, "r");
	if (!file) {
		//printf("Doslo je do greske prilikom otvaranja fajla. . .");
		Graph graph;
		graph.size = -1;
		return graph;
	}
	char **mat = NULL;
	int **idMat = NULL;
	int id = 0;
	char c;
	int m = 0, n = 0, numberOfNodes = 0;

	// Ucitavamo mapu iz fajla u matricu karaktera
	while ((c = fgetc(file)) != EOF) {
		switch (c)
		{
		// Ako dodje neki od znakova koji nije novi red
		case 'o':
		case '-':
		case 'S':
		case 'T':
			// Ako smo tek poceli sa ucitavanjem zauzememo jednu vrstu za matricu i stavimo je na NULL
			if (m == 0 && n == 0) {
				mat = realloc(mat, sizeof(char*));
				mat[0] = NULL;
			}
			
			// Alociramo dodatno mesto unutar vrste i u njega upisemo procitani karakter
			mat[m] = realloc(mat[m], (n + 1) * sizeof(char));
			mat[m][n] = c;

			n++; // Povecamo broj elemenata u trenutnoj vrsti

			// Ako je procitani karakter != '-' i != '\n' to znaci da je na toj poziciji ploca pa inkrementiramo broj ploca
			if(c != '-')
				numberOfNodes++;
			break;
		case '\n':
			m++;											// Povecavamo broj vrsta za 1
			n = 0;											// Vracamo se u kolonu 0
			mat = realloc(mat, (m + 1) * sizeof(char*));	// Povecamo matricu za jos jednu vrstu
			mat[m] = NULL;									// Stavimo vrstu na NULL da bi mogli da je realociramo posle
			break;
		}
	}
	n--;
	
	// Alociramo memoriju za matricu u kojoj cuvamo id svakog cvora na njegovoj realnoj poziciji
	idMat = realloc(idMat, (m + 1) * sizeof(int*));
	for (int i = 0; i <= m; i++)
		idMat[i] = calloc(n + 1, sizeof(int));

	// Alociramo memoriju za matricu susednosti
	Graph newTable;
	newTable.size = numberOfNodes;
	newTable.adjMat = calloc(newTable.size, sizeof(Direction *));
	for (int i = 0; i < newTable.size; i++)
		newTable.adjMat[i] = calloc(newTable.size, sizeof(Direction));

	// Popunjavamo idMat id vrednostima cvorova (plocica)
	int cnt = 0;
	for (int i = 0; i <= m; i++) {
		for (int j = 0; j <= n; j++) {
			if (mat[i][j] == 'o') {
				idMat[i][j] = cnt;
				cnt++;
			}
			else if (mat[i][j] == 'S') {
				idMat[i][j] = cnt;
				newTable.S = cnt;
				cnt++;
			}
			else if (mat[i][j] == 'T') {
				idMat[i][j] = cnt;
				newTable.T = cnt;
				cnt++;
			}
			else {
				idMat[i][j] = -1;
			}
		}
	}

	// Popunjavamo matricu susednosti
	int edge;
	for (int i = 0; i <= m; i++) {
		for (int j = 0; j <= n; j++) {
			if (idMat[i][j] != -1) {
				if ((edge = checkConnection(idMat, i - 1, j, m, n)) != -1) 
					newTable.adjMat[idMat[i][j]][edge] = NORTH;
				
				if ((edge = checkConnection(idMat, i, j - 1, m, n)) != -1) 
					newTable.adjMat[idMat[i][j]][edge] = WEST;
				
				if ((edge = checkConnection(idMat, i + 1, j, m, n)) != -1) 
					newTable.adjMat[idMat[i][j]][edge] = SOUTH;
				
				if ((edge = checkConnection(idMat, i, j + 1, m, n)) != -1) 
					newTable.adjMat[idMat[i][j]][edge] = EAST;			
			}
		}
	}

	// Preostala polja matrice susednosti stavljamo na NOT_CONNECTED
	for (int i = 0; i < newTable.size; i++) {
		for (int j = 0; j < newTable.size; j++) {
			if (newTable.adjMat[i][j] != NORTH && newTable.adjMat[i][j] != WEST &&
				newTable.adjMat[i][j] != SOUTH && newTable.adjMat[i][j] != EAST)
				newTable.adjMat[i][j] = NOT_CONNECTED; ///VODI RACUNA!!!!!!!
		}
	}
	
	// "Vracamo" matricu koja cuva id vrednosti i njene dimenzije
	*idMatrix = idMat;
	//printf("\n\n%d ", m + 1);
	//printf("%d \n\n", n + 1);
	*xsize = n + 1;
	*ysize = m + 1;

	// Brisemo matricu karaktera koju smo ucitali
	for (int i = 0; i <= m; i++)
		free(mat[i]);
	free(mat);

	fclose(file);
	return newTable;
}

// Dodaje granu u graf izmedju cvorova koji imaju id u i id v
void addEgde(Graph graph, int u, int v)
{
	graph.adjMat[u][v] = TEMP;
	graph.adjMat[v][u] = TEMP;
}

// Brise granu iz grafa izmedju cvorova koji imaju id u i id v
void deleteEdge(Graph graph, int u, int v)
{
	graph.adjMat[u][v] = NOT_CONNECTED;
	graph.adjMat[v][u] = NOT_CONNECTED;
}

// Pretraga po sirini
int bfs(Graph graph, int v)
{
	int *visit = calloc(graph.size, sizeof(int));

	Queue *queue = initQueue();
	printf("Visited %d\n", v);
	visit[v] = 1;
	insert(queue, v);

	while (!isEmptyQueue(queue)) {
		v = get(queue);
		for (int i = 0; i < graph.size; i++) {
			if (graph.adjMat[v][i]) {
				if (!visit[i]) {
					printf("Visited %d\n", i);
					visit[i] = 1;
					insert(queue, i);
				}
			}
		}
	}

	for (int i = 0; i < graph.size; i++)
		if (visit[i] == 0)
			return 0;

	return 1;
}

// dfs utility funkcija
void dfs_visit(Graph graph, int v, int *visit)
{
	printf("Visited %d\n", v);
	visit[v] = 1;
	for (int i = 0; i < graph.size; i++) {
		if (graph.adjMat[v][i]) {
			if (!visit[i]) {
				dfs_visit(graph, i, visit);
			}
		}
	}
}

// Pretraga po dubini
int dfs(Graph graph)
{
	int *visit = calloc(graph.size, sizeof(int));

	dfs_visit(graph, 0, visit);

	for (int i = 0; i < graph.size; i++)
		if (visit[i] == 0)
			return 0;

	return 1;
}

// Stampa graf u obliku matrice susednost
void printGraph(Graph graph)
{
	for (int i = 0; i < graph.size; i++) {
		for (int j = 0; j < graph.size; j++) {
			printf("%d ", graph.adjMat[i][j]);
		}
		printf("\n");
	}
}

// Oslobadja memoriju koju zauzima matrica susednosti
void deleteGraph(Graph graph)
{
	for (int i = 0; i < graph.size; i++)
		free(graph.adjMat[i]);
	free(graph.adjMat);
}