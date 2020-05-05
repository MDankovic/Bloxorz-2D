#include "game.h"
#include <stdio.h>

int playPossible(Game game, Direction dir, Orientation orientation, int position)
{
	int id1;
	int id2;

	switch (dir)
	{
	case NORTH:
		if (orientation == VERTICAL) {
			if ((id1 = hasConnection(game.field, NORTH, position)) != -1) {
				if ((id2 = hasConnection(game.field, NORTH, id1)) != -1) {
					return 1;
				}
				else {
					return 0;
				}
			}
			else {
				return 0;
			}
		}
		else if (orientation == HORIZONTAL_EW) {
			if (((id1 = hasConnection(game.field, NORTH, position)) != -1)
				&& ((id2 = hasConnection(game.field, NORTH, position + 1)) != -1)) {//game.position + 1
				return 1;
			}
			else {
				return 0;
			}
		}
		else if (orientation == HORIZONTAL_NS) {
			if ((id1 = hasConnection(game.field, NORTH, position)) != -1) {
				return 1;
			}
			else {
				return 0;
			}
		}
		break;
	case WEST:
		if (orientation == VERTICAL) {
			if ((id1 = hasConnection(game.field, WEST, position)) != -1) {
				if ((id2 = hasConnection(game.field, WEST, position - 1)) != -1) {//game.position - 1
					return 1;
				}
				else {
					return 0;
				}
			}
			else {
				return 0;
			}
		}
		else if (orientation == HORIZONTAL_EW) {
			if ((id1 = hasConnection(game.field, WEST, position)) != -1) {
				return 1;
			}
			else {
				return 0;
			}
		}
		else if (orientation == HORIZONTAL_NS) {
			if (((id1 = hasConnection(game.field, WEST, position)) != -1)
				&& ((id2 = hasConnection(game.field, WEST, findNode(game.field, SOUTH, position))) != -1)) {
				return 1;
			}
			else {
				return 0;
			}
		}
		break;
	case SOUTH:
		if (orientation == VERTICAL) {
			if ((id1 = hasConnection(game.field, SOUTH, position)) != -1) {
				if ((id2 = hasConnection(game.field, SOUTH, id1)) != -1) {
					return 1;
				}
				else {
					return 0;
				}
			}
			else {
				return 0;
			}
		}
		else if (orientation == HORIZONTAL_EW) {
			if (((id1 = hasConnection(game.field, SOUTH, position)) != -1)
				&& ((id2 = hasConnection(game.field, SOUTH, position + 1)) != -1)) {//game.position + 1
				return 1;
			}
			else {
				return 0;
			}
		}
		else if (orientation == HORIZONTAL_NS) {
			if ((id1 = hasConnection(game.field, SOUTH, findNode(game.field, SOUTH, position))) != -1) {
				return 1;
			}
			else {
				return 0;
			}
		}
		break;
	case EAST:
		if (orientation == VERTICAL) {
			if ((id1 = hasConnection(game.field, EAST, position)) != -1) {
				if ((id2 = hasConnection(game.field, EAST, id1)) != -1) {
					return 1;
				}
				else {
					return 0;
				}
			}
			else {
				return 0;
			}
		}
		else if (orientation == HORIZONTAL_EW) {
			if ((id1 = hasConnection(game.field, EAST, position + 1)) != -1) {//game.position + 1
				return 1;
			}
			else {
				return 0;
			}
		}
		else if (orientation == HORIZONTAL_NS) {
			if (((id1 = hasConnection(game.field, EAST, position)) != -1)
				&& ((id2 = hasConnection(game.field, EAST, findNode(game.field, SOUTH, position))) != -1)) {
				return 1;
			}
			else {
				return 0;
			}
		}
		break;
	}
	return 0;
}

void playMove(Game game, Direction dir, Orientation *ori, int *ps, Orientation orientation, int position)
{
	int id1, id2;

	switch (dir)
	{
	case NORTH:
		if (orientation == VERTICAL) {
			if ((id1 = hasConnection(game.field, NORTH, position)) != -1)
				if ((id2 = hasConnection(game.field, NORTH, id1)) != -1) {
					//printf("id1 %d <-> id2 %d\n", id1, id2);
					*ori = HORIZONTAL_NS;
					*ps = id2;
				}
		}
		else if (orientation == HORIZONTAL_EW) {
			if (((id1 = hasConnection(game.field, NORTH, position)) != -1)
				&& ((id2 = hasConnection(game.field, NORTH, position + 1)) != -1)) {//game.position + 1
				//printf("id1 %d <-> id2 %d\n", id1, id2);
				*ori = HORIZONTAL_EW;
				*ps = id1;
			}
		}
		else if (orientation == HORIZONTAL_NS) {
			if ((id1 = hasConnection(game.field, NORTH, position)) != -1) {
				//printf("id1 %d\n", id1);
				*ori = VERTICAL;
				*ps = id1;
			}
		}
		break;
	case WEST:
		if (orientation == VERTICAL) {
			if ((id1 = hasConnection(game.field, WEST, position)) != -1)
				if ((id2 = hasConnection(game.field, WEST, position - 1)) != -1) {//game.position - 1
					//printf("id1 %d <-> id2 %d\n", id1, id2);
					*ori = HORIZONTAL_EW;
					*ps = id2;
				}
		}
		else if (orientation == HORIZONTAL_EW) {
			if ((id1 = hasConnection(game.field, WEST, position)) != -1) {
				//printf("id1 %d\n", id1);
				*ori = VERTICAL;
				*ps = id1;
			}
		}
		else if (orientation == HORIZONTAL_NS) {
			if (((id1 = hasConnection(game.field, WEST, position)) != -1)
				&& ((id2 = hasConnection(game.field, WEST, findNode(game.field, SOUTH, position))) != -1)) {
				//printf("id1 %d <-> id2 %d\n", id1, id2);
				*ori = HORIZONTAL_NS;
				*ps = id1;
			}
		}
		break;
	case SOUTH:
		if (orientation == VERTICAL) {
			if ((id1 = hasConnection(game.field, SOUTH, position)) != -1)
				if ((id2 = hasConnection(game.field, SOUTH, id1)) != -1) {
					//printf("id1 %d <-> id2 %d\n", id1, id2);
					*ori = HORIZONTAL_NS;
					*ps = id1;
				}
		}
		else if (orientation == HORIZONTAL_EW) {
			if (((id1 = hasConnection(game.field, SOUTH, position)) != -1)
				&& ((id2 = hasConnection(game.field, SOUTH, position + 1)) != -1)) {//game.position + 1
				//printf("id1 %d <-> id2 %d\n", id1, id2);
				*ori = HORIZONTAL_EW;
				*ps = id1;
			}
		}
		else if (orientation == HORIZONTAL_NS) {
			if ((id1 = hasConnection(game.field, SOUTH, findNode(game.field, SOUTH, position))) != -1) {
				//printf("id1 %d\n", id1);
				*ori = VERTICAL;
				*ps = id1;
			}
		}
		break;
	case EAST:
		if (orientation == VERTICAL) {
			if ((id1 = hasConnection(game.field, EAST, position)) != -1)
				if ((id2 = hasConnection(game.field, EAST, id1)) != -1) {
					//printf("id1 %d <-> id2 %d\n", id1, id2);
					*ori = HORIZONTAL_EW;
					*ps = id1;
				}
		}
		else if (orientation == HORIZONTAL_EW) {
			if ((id1 = hasConnection(game.field, EAST, position + 1)) != -1) {//game.position + 1
				//printf("id1 %d\n", id1);
				*ori = VERTICAL;
				*ps = id1;
			}
		}
		else if (orientation == HORIZONTAL_NS) {
			if (((id1 = hasConnection(game.field, EAST, position)) != -1)
				&& ((id2 = hasConnection(game.field, EAST, findNode(game.field, SOUTH, position))) != -1)) {
				//printf("id1 %d <-> id2 %d\n", id1, id2);
				*ori = HORIZONTAL_NS;
				*ps = id1;
			}
		}
		break;
	}
}

// NORTH 0
// SOUTH 1
// EAST  2
// WEST  3

// VERTICAL 0
// HOR_EW   1
// HOR_NS   2


// solver
void solveGame(Game game)
{
	int position = game.position, ps;
	Orientation orientation = game.orientation, or;
	Direction prevDir;
	char moves[10000];
	int moveCounter = 0;

	Stack *positions = initStack(1000000);
	Stack *cameFrom = initStack(1000000);
	Stack *orientations = initStack(1000000);
	Stack *level = initStack(1000000);
	//Stack *moves = initStack(1000000);

	push(positions, game.position);
	push(cameFrom, TEMP);
	push(orientations, game.orientation);
	push(level, -1);
	int i = 0;
	int currLevel = -1;
	int prevLevel = -1;
	int cnt = 0;

	//printf("Stack size: %d\n", stackSize(positions));

	int visited[1000][4];
	for (int i = 0; i < game.field.size; i++) {
			visited[i][0] = -1;
			visited[i][1] = -1;
			visited[i][2] = -1;
	}
	int okMove = 1;
	while (!isEmpty(positions)) {
		position = pop(positions);
		orientation = pop(orientations);
		prevDir = pop(cameFrom);
		currLevel = pop(level);
		visited[position][orientation] = 1;

		//printf("\ncurrLevel of popped node = %d\n", currLevel);
		if (okMove) {
			
			switch (prevDir)
			{
			case NORTH:
				moves[currLevel] = 'S';
				break;
			case EAST:
				moves[currLevel] = 'A';
				break;
			case WEST:
				moves[currLevel] = 'D';
				break;
			case SOUTH:
				moves[currLevel] = 'W';
				break;
			default:
				break;
			}
			cnt++;
		}
		else {
			switch (prevDir)
			{
			case NORTH:
				moves[currLevel] = 'S';
				break;
			case EAST:
				moves[currLevel] = 'A';
				break;
			case WEST:
				moves[currLevel] = 'D';
				break;
			case SOUTH:
				moves[currLevel] = 'W';
				break;
			default:
				break;
			}
		}
		okMove = 0;
		//printf("moveCounter = %d\n", moveCounter);

		
		//printf("position %d\norientation %d\n", position, orientation);

		if (position == game.field.T && orientation == VERTICAL) {
			//printf("\nMOGUCE\n");
			//printf("steps: ");
			for (int i = 0; i < currLevel+1; i++) {
				printf("\x1b[32m%c \x1b[0m", moves[i]);
			}
			//printf("\n\n");
			return;
		}

		if (playPossible(game, NORTH, orientation, position)) {
			playMove(game, NORTH, &or , &ps, orientation, position);
			if (visited[ps][or] == -1) {
				//moves[moveCounter++] = 'W';
				push(positions, ps);
				push(cameFrom, SOUTH);
				push(orientations, or);
				push(level, currLevel + 1);
				//printf("level = %d\n", currLevel+1);
				visited[ps][or] = 1;
				okMove = 1;
				//printf("N %d\n", i);
				//cnt++;
			}
		}
		//printf("Stack size: %d\n", stackSize(positions));
		if (playPossible(game, SOUTH, orientation, position)){
			playMove(game, SOUTH, &or , &ps, orientation, position);
			if (visited[ps][or] == -1) {
				//moves[moveCounter++] = 'S';
				push(positions, ps);
				push(cameFrom, NORTH);
				push(orientations, or );
				push(level, currLevel + 1);
				//printf("level = %d\n", currLevel + 1);
				visited[ps][or ] = 1;
				okMove = 1;
				//printf("S %d\n", i);
				//cnt++;
			}
		}
		//printf("Stack size: %d\n", stackSize(positions));
		if (playPossible(game, EAST, orientation, position)) {
			playMove(game, EAST, &or , &ps, orientation, position);
			if (visited[ps][or] == -1) {
				//moves[moveCounter++] = 'D';
				push(positions, ps);
				push(cameFrom, WEST);
				push(orientations, or );
				push(level, currLevel + 1);
				//printf("level = %d\n", currLevel + 1);
				visited[ps][or] = 1;
				okMove = 1;
				//printf("E %d\n", i);
				//cnt++;
			}
		}
		//printf("Stack size: %d\n", stackSize(positions));
		if (playPossible(game, WEST, orientation, position)) {
			playMove(game, WEST, &or , &ps, orientation, position);
			if (visited[ps][or] == -1) {
				//moves[moveCounter++] = 'A';
				push(positions, ps);
				push(cameFrom, EAST);
				push(orientations, or );
				push(level, currLevel + 1);
				//printf("level = %d\n", currLevel + 1);
				visited[ps][or] = 1;
				okMove = 1;
				//printf("W %d\n", i);
				//cnt++;
			}
		}
		i++;
		//printf("\nlevel = %d\n", currLevel);
		//printf("Stack size: %d\n", stackSize(positions));
		//printf("\n");


		//Slobodno uncomentuj ovo radi sve kako treba i napravi deleteStack da bude lepse
		/*
		free(positions);
		free(orientations);
		free(level);
		free(cameFrom);
		*/
	}

	printf(" There is no path between S and T!\n");
	return;
}