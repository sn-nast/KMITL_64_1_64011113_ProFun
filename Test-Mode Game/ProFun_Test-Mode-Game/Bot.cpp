#include "Bot.h"
#include "main.h"
#include "Move.h"
#include "Buffer.h"
#include "Control.h"
#include "Bomb.h"
#include "Map.h" 
#include "Object.h"

void setupBot(Player* p) {
	strcpy_s(p->Format, "N");
	strcpy_s(p->Name, "BOT NO.1");
	//p->Attribute = 7;
	p->Lenght = 3;
	p->Height = 3;
	p->SpeedX = 3;
	p->SpeedY = 3;
	p->Bomb.Amount = 1;
	p->Bomb.PowerX = 1;
	p->Bomb.PowerY = 1;
	p->Bot.CountDirectionNow = 0;
	setupBomb(p);
}

void setOfBot(Player* p, Map* m) {
	setOfBomb(p, m);
	playerMove(p, m);
}

void moveBot(Player* p, Map* m) {
	// ptr about Bot Direction
	unsigned int* Direction = &p->Bot.DirectionNow;
	unsigned int* LastDirection = &p->Bot.LastDirectionNow;
	unsigned int* C_Direction = &p->Bot.CountDirectionNow;
	// Bomb bot
	COORD nearestBomb[3] = { {0, 0}, {0, 0}, {0, 0} };
	double distance[3] = { 0, 0, 0 };
	int haveBomb = 0;
	COORD* pos = &p->Position;
	int Len = p->Lenght;
	int Hei = p->Height;

	struct _Direction {
		int CountCheckSide = 0;
		int Direction;
		int propertyX;
		int propertyY;
		int CountCanMove;
	};
	_Direction allDirection[4] = {
		{ 0, LEFT , -Len , 0,	0},
		{ 0, RIGHT, Len  , 0,	0},
		{ 0, DOWN , 0    , Hei,	0},
		{ 0, UP	  , 0    , -Hei,0}
	};
	// Check bomb
	for (short pY = 0; pY < MAP_HEIGHT; pY++) {
		for (short pX = 0; pX < MAP_WIDTH; pX++) {
			if (m->State[pY][pX] == Bomb_Nm.NormalState &&
				m->State[pY][pX + (Len - 1)] == Bomb_Nm.NormalState &&
				m->State[pY + (Hei - 1)][pX] == Bomb_Nm.NormalState
				) {
				int deltaX = pX - pos->X;
				int deltaY = pY - pos->Y;
				distance[2] = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
				nearestBomb[2] = { pX, pY };
				if (distance[0] == 0) {
					distance[0] = distance[2];
					nearestBomb[0] = nearestBomb[2];
				}
				else if (distance[2] < distance[1]) {
					if (distance[2] < distance[0]) {
						double temp = distance[1];
						distance[1] = distance[0];
						distance[0] = distance[2];
						distance[2] = temp;
						COORD tempC = nearestBomb[1];
						nearestBomb[1] = nearestBomb[0];
						nearestBomb[0] = nearestBomb[2];
						nearestBomb[2] = tempC;
					}
					else {
						distance[0] = distance[1];
						distance[1] = distance[2];
						nearestBomb[0] = nearestBomb[1];
						nearestBomb[1] = nearestBomb[2];
					}
				}
				haveBomb++;
			}
		}
	}
	int dirX = 0, dirY = 0;

	// ------------------------------------ //
	// Random move
	const int PASS = 1, cantPASS = 0;
	int CheckSide[4] = { PASS, PASS, PASS, PASS };
	int canMoveAmount[4] = { 0, 0, 0, 0 };
	bool haveBomb1 = false;
	// Check side can move
	if (checkStateControl(m->State[pos->Y][pos->X - Len]) == cantPASS) { CheckSide[0] = cantPASS; }
	if (checkStateControl(m->State[pos->Y][pos->X + Len]) == cantPASS) { CheckSide[1] = cantPASS; }
	if (checkStateControl(m->State[pos->Y + Hei][pos->X]) == cantPASS) { CheckSide[2] = cantPASS; }
	if (checkStateControl(m->State[pos->Y - Hei][pos->X]) == cantPASS) { CheckSide[3] = cantPASS; }
	int size = sizeof(CheckSide) / sizeof(CheckSide[0]);
	// Count lenght can move
	for (int n = 0; n < size; n++) {
		if ((n == LEFT - 1 || n == RIGHT - 1) && CheckSide[n] == PASS) {
			for (int Mw = allDirection[n].propertyX; abs(Mw) < MAP_WIDTH; Mw += allDirection[n].propertyX) {
				if (checkStateControl(m->State[pos->Y][pos->X + Mw]) == PASS) {
					allDirection[n].CountCanMove++;
				}
				else { break; }
			}
		}
		else if ((n == DOWN - 1 || n == UP - 1) && CheckSide[n] == PASS) {
			for (int Mh = allDirection[n].propertyY; abs(Mh) < MAP_WIDTH; Mh += allDirection[n].propertyY) {
				if (checkStateControl(m->State[pos->Y + Mh][pos->X]) == PASS) {
					allDirection[n].CountCanMove++;
				}
				else { break; }
			}
		}
	}
	// Random select move
	// no bomb and Count dir = 0
	bool ShouldChangeDir = false;
	while (*C_Direction == 0 && haveBomb1 == false) {
		for (int n = 0; n < size; n++) {
			int randToMove = rand() % 4;
			unsigned int* CountMoveDir = &p->Bot.CountMoveThisDirection[n];
			if (CheckSide[n] == PASS && randToMove <= 2) {
				unsigned int temp = *LastDirection;
				*C_Direction = allDirection[n].CountCanMove;
				*LastDirection = *Direction;
				*Direction = allDirection[n].Direction;
				//ShouldChangeDir = false;
				break;
			}
			// absolutely can't move
			if (n == size - 1) { return; }
		}
	}

	// Same direction should change new
	unsigned int* CountMoveDir = &p->Bot.CountMoveThisDirection[*Direction - 1];
	if (*CountMoveDir >= 3) {
		*CountMoveDir = 0;
		// if can change direction, should change
		for (int n = 0; n < size; n++) {
			int randToMove = rand() % 4;
			unsigned int* CountMoveDir = &p->Bot.CountMoveThisDirection[n];
			// can pass and not same direction 
			if ((CheckSide[n] == cantPASS) || (*Direction == allDirection[n].Direction)) { continue; }
			// L, R -> U, D
			if ((*Direction == LEFT || *Direction == RIGHT) &&
				(n == DOWN - 1 || n == UP - 1) &&
				randToMove <= 2) {
				*C_Direction = allDirection[n].CountCanMove;
				*LastDirection = *Direction;
				*Direction = allDirection[n].Direction;
				break;
			}
			// U, D -> L, R
			else if ((*Direction == DOWN || *Direction == UP) &&
				(n == LEFT - 1 || n == RIGHT - 1) &&
				randToMove <= 2) {
				*C_Direction = allDirection[n].CountCanMove;
				*LastDirection = *Direction;
				*Direction = allDirection[n].Direction;
				break;
			}
			// absolutely can't change direction
			if (n == size - 1) { return; }
		}
	}
	// Move bot
	checkControl(*Direction, p, m);
	(*C_Direction)--;
	(*CountMoveDir)++;
}

void dropBombBot(Player* p, Map* m) {
	COORD* pos = &p->Position;
	bool* drop = &p->Bot.CanDropBomb;
	int size = p->Bomb.Amount;
	int Hei = p->Height;
	int Len = p->Lenght;
	int check = 0;
	for (int H = -Hei; H <= Hei; H += Hei) {
		for (int L = -Len; L <= Len; L += Len) {
			if (checkStateControl(m->State[pos->Y + H][pos->X + L]) == 1){
				check++;
			}
		}
	}
	if (p->Bomb.Drop == 0) { *drop = true; }
	if (*drop == true && check > 0) {
		int i = 0;
		if (p->Bomb.Drop < size) {
			for (int c = 0; c < size; c++) {
				if (p->Bomb.State[c] == BOMB_COUNTING) { i++; }
			}
			if (m->State[pos->Y][pos->X] == Bomb_Nm.NormalState) {
				return;
			}
			if (p->Bomb.Drop < size - i) { 
				p->Bomb.Drop++; 
				*drop = false;
			}
		}
	}
}
