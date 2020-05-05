#pragma once

#include "graph.h"

typedef enum {VERTICAL, HORIZONTAL_EW, HORIZONTAL_NS} Orientation;

typedef enum { GAME_LOST, GAME_WIN, STILL_PLAYING } State;

typedef struct
{
	Graph field;				// mapa
	State state;				// stanje igre
	Orientation orientation;	// polozaj kvadra u prostoru

	int position;				// pozicija kvadra 
								// VERTICAL - polje na kome stoji
								// HORIZONTAL_EW - levo polje
								// HORIZONTAL_NS - gornje polje
} Game;