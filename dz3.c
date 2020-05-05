#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>
#include "queue.h"
#include "stack.h"
#include "graph.h"
#include "game.h"
#include "nextMove.h"

// STRELICE
#define UP     0x48
#define DOWN   0x50
#define LEFT   0x4B
#define RIGHT  0x4D

// BOJE
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// POMOC
#define HELP 3

void freeMat(int **mat, int m, int n)
{
	for (int i = 0; i < m; i++) {
		free(mat[i]);
	}
	free(mat);
}

// ISPIS TRENUTNOG STANJA MAPE
void printCurrentState(Game game, int **mat, int m, int n)
{
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (game.orientation == VERTICAL && game.position == mat[i][j]) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE);
				printf(ANSI_COLOR_BLUE "B " ANSI_COLOR_RESET);
			}
			else if (game.orientation == HORIZONTAL_EW && (game.position == mat[i][j] || (j > 0 && game.position == mat[i][j - 1]))) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE);
				printf(ANSI_COLOR_BLUE "B " ANSI_COLOR_RESET);
			}
			else if (game.orientation == HORIZONTAL_NS && (game.position == mat[i][j] || (i > 0 && game.position == mat[i - 1][j]))) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE);
				printf(ANSI_COLOR_BLUE "B " ANSI_COLOR_RESET);
			}
			else if (mat[i][j] == game.field.S) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED);
				printf(ANSI_COLOR_RED "S " ANSI_COLOR_RESET);
			}
			else if (mat[i][j] == game.field.T) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
				printf(ANSI_COLOR_GREEN "T " ANSI_COLOR_RESET);
			}
			else if (mat[i][j] != -1) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
				printf("  "); // o
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY);
				printf("  "); // x
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		printf("\n");
	}
}

// MENI ZA IZBOR SLEDECEG POTEZA
char move()
{
	char opt = 'x', temp;
	printf("\n\n");
	opt = _getch();

	if (opt)
		opt = _getch();

	switch (opt)
	{
	case UP:
		return 'W';
	case LEFT:
		return 'A';
	case DOWN:
		return 'S';
	case RIGHT:
		return 'D';
	}

	return opt;
}

// MENI ZA IZBOR AKCIJE U IGRI
int menu()
{
	int opt;
	printf("1. Start game\n");
	printf("2. About the game\n");
	printf("3. End game\n");
	scanf("%d", &opt);

	return opt;
}

int main(void)
{
	system("color 07");
	//printf("Welcome to BLOXORZ ;)\nUse arrow keys to operate game.\nGood luck!\n\n");
	
	Game game;								// promenljiva gde cuvamo sve vezano za igru
	int **mat, m, n;						// matrica koja cuva id svakog cvora na odgovarajucoj poziciji
	char dir;								// dir odredjuje smer sledeceg poteza
	int id1, id2;							// pomocne promenljive koje cuvaju id nekih cvorova
	int option = 0;							// Akcija korisnika za izbor sledece aktivnosti u igri
	int helpsLeft;

	while (option != 3) {
		option = menu();
		switch (option) {
		case 1:
			game.field = getField(&mat, &m, &n);	// pravimo graf koji predstavlja nasu mapu
			if (game.field.size == -1) {
				printf("Error opening file!");
				printf("\n\nPress enter to continue. . .");
				_getch();
				break;
			}
			game.orientation = VERTICAL;			// u pocetnu kvadar je u vertikalnom polozaju
			game.state = STILL_PLAYING;				// stanje igre je da jos uvek traje
			game.position = game.field.S;			// pocetna pozicija je na polju S (START)	
			helpsLeft = HELP;
			int numOfMoves = 0;

			int xcoor, ycoor;
			
			// Zapoceli smo igru
			printCurrentState(game, mat, m, n);		// stampamo trenutno stanje
			printf("\nHELPS LEFT: %d\nMOVES: %d\n", helpsLeft, numOfMoves);
			while (game.state == STILL_PLAYING) {	// dok je stanje igre da se jos igra ponavljaj sledece korake
				dir = move(); // ucitaj potez
				switch (dir)
				{
				case 'W':
					numOfMoves++;
					if (game.orientation == VERTICAL) {
						if ((id1 = hasConnection(game.field, NORTH, game.position)) != -1) {
							if ((id2 = hasConnection(game.field, NORTH, id1)) != -1) {
								game.orientation = HORIZONTAL_NS;
								game.position = id2;
							}
							else {
								game.state = GAME_LOST;
							}
						}
						else {
							game.state = GAME_LOST;
						}
					}
					else if (game.orientation == HORIZONTAL_EW) {
						if (((id1 = hasConnection(game.field, NORTH, game.position)) != -1)
							&& ((id2 = hasConnection(game.field, NORTH, game.position + 1)) != -1)) {
							game.position = id1;
						}
						else {
							game.state = GAME_LOST;
						}
					}
					else if (game.orientation == HORIZONTAL_NS) {
						if ((id1 = hasConnection(game.field, NORTH, game.position)) != -1) {
							game.orientation = VERTICAL;
							game.position = id1;
						}
						else {
							game.state = GAME_LOST;
						}
					}
					break;
				case 'A':
					numOfMoves++;
					if (game.orientation == VERTICAL) {
						if ((id1 = hasConnection(game.field, WEST, game.position)) != -1) {
							if ((id2 = hasConnection(game.field, WEST, game.position - 1)) != -1) {
								game.orientation = HORIZONTAL_EW;
								game.position = id2;
							}
							else {
								game.state = GAME_LOST;
							}
						}
						else {
							game.state = GAME_LOST;
						}
					}
					else if (game.orientation == HORIZONTAL_EW) {
						if ((id1 = hasConnection(game.field, WEST, game.position)) != -1) {
							game.orientation = VERTICAL;
							game.position = id1;
						}
						else {
							game.state = GAME_LOST;
						}
					}
					else if (game.orientation == HORIZONTAL_NS) {
						if (((id1 = hasConnection(game.field, WEST, game.position)) != -1)
							&& ((id2 = hasConnection(game.field, WEST, findNode(game.field, SOUTH, game.position))) != -1)) {
							game.orientation = HORIZONTAL_NS;
							game.position = id1;
						}
						else {
							game.state = GAME_LOST;
						}
					}
					break;
				case 'S':
					numOfMoves++;
					if (game.orientation == VERTICAL) {
						if ((id1 = hasConnection(game.field, SOUTH, game.position)) != -1) {
							if ((id2 = hasConnection(game.field, SOUTH, id1)) != -1) {
								game.orientation = HORIZONTAL_NS;
								game.position = id1;
							}
							else {
								game.state = GAME_LOST;
							}
						}
						else {
							game.state = GAME_LOST;
						}
					}
					else if (game.orientation == HORIZONTAL_EW) {
						if (((id1 = hasConnection(game.field, SOUTH, game.position)) != -1)
							&& ((id2 = hasConnection(game.field, SOUTH, game.position + 1)) != -1)) {
							game.position = id1;
						}
						else {
							game.state = GAME_LOST;
						}
					}
					else if (game.orientation == HORIZONTAL_NS) {
						id2 = findNode(game.field, SOUTH, game.position);

						if ((id1 = hasConnection(game.field, SOUTH, id2)) != -1) {
							game.orientation = VERTICAL;
							game.position = id1;
						}
						else {
							game.state = GAME_LOST;
						}
					}
					break;
				case 'D':
					numOfMoves++;
					if (game.orientation == VERTICAL) {
						if ((id1 = hasConnection(game.field, EAST, game.position)) != -1) {
							if ((id2 = hasConnection(game.field, EAST, id1)) != -1) {
								game.orientation = HORIZONTAL_EW;
								game.position = id1;
							}
							else {
								game.state = GAME_LOST;
							}
						}
						else {
							game.state = GAME_LOST;
						}
					}
					else if (game.orientation == HORIZONTAL_EW) {
						if ((id1 = hasConnection(game.field, EAST, game.position + 1)) != -1) {
							game.orientation = VERTICAL;
							game.position = id1;
						}
						else {
							game.state = GAME_LOST;
						}
					}
					else if (game.orientation == HORIZONTAL_NS) {
						if (((id1 = hasConnection(game.field, EAST, game.position)) != -1)
							&& ((id2 = hasConnection(game.field, EAST, findNode(game.field, SOUTH, game.position))) != -1)) {
							game.orientation = HORIZONTAL_NS;
							game.position = id1;
						}
						else {
							game.state = GAME_LOST;
						}
					}
					break;
				case 'h':
					if (helpsLeft) {
						printf("Winning sequence: ");
						solveGame(game);
						printf("\n\nPress enter to continue. . .");
						_getch();
						helpsLeft--;
					}
					else {
						printf(ANSI_COLOR_RED "No more helps left. . ." ANSI_COLOR_RESET);
						printf("\n\nPress enter to continue. . .");
						_getch();
					}
					break;
				case 't':
					printf("Y X: ");
					scanf("%d %d", &xcoor, &ycoor);
					game.field.size = addTile(&game.field.adjMat, game.field.size, mat, xcoor, ycoor, m, n, &game.field.S, &game.field.T, &game.position);
					break;
				case 'y':
					printf("Y X: ");
					scanf("%d %d", &xcoor, &ycoor);
					game.field.size = deleteTile(&game.field.adjMat, game.field.size, mat, xcoor, ycoor, m, n, &game.field.S, &game.field.T, &game.position);
					break;
				default:
					printf(ANSI_COLOR_RED "\nWrong input. . .\n\n" ANSI_COLOR_RESET);
					printf("\n\nPress enter to continue. . .");
					_getch();
					break;
				}

				// Provera pobednicke pozicije (uspravno na polju T)
				if (game.orientation == VERTICAL && game.position == game.field.T)
					game.state = GAME_WIN;

				system("cls");
				printCurrentState(game, mat, m, n);
				printf("\nHELPS LEFT: %d\nMOVES: %d\n", helpsLeft, numOfMoves);
			}
			system("cls");

			// Ispis rezultata igre
			if (game.state == GAME_LOST) {
				system("color 40");
				printf(ANSI_COLOR_RED "GAME LOST\n\n\n\n" ANSI_COLOR_RESET);
			}
			else if (game.state == GAME_WIN) {
				system("color 20");
				printf(ANSI_COLOR_GREEN "GAME WON\n\n\n\n" ANSI_COLOR_RESET);
			}
		
			deleteGraph(game.field);
			freeMat(mat, m, n);
			Sleep(1000);

			// Kraj igre
			break;
			case 2:
				system("cls");
				printf("  About BLOXORZ:\n");
				printf("\n\tBloxorz is a straightforward yet addictive game - move a block around a floating platform using the arrow keys\n\tdropping it through the square hole to finish the known level. That's it! Simple since it sounds, the known\n\tamounts get a growing number of taxing, though we are able to assure you they are all solveable actually!");
				printf(ANSI_COLOR_RED "\n\n\tBe warned - every single day start playing this you might find it hard to stop!\n" ANSI_COLOR_RESET);
				printf("\n\n  Press enter to continue. . .");
				_getch();
				break;
			case 3:
				// exit
				break;
		}
		system("cls");
		system("color 07");
	}
	return 0;
}