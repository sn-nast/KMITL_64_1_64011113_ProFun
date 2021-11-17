#include "Bot.h"
#include "main.h"
#include "Move.h"
#include "Buffer.h"
#include "Control.h"
#include "Bomb.h"
#include "Map.h" 
#include "Object.h"

Player playerBot[3];
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
	// Move bot (Part: draw bot)
	playerMove(p, m);
}

void moveBot(Player* p, Map* m) {
	// ptr about Bot Direction
	unsigned int* Direction = &p->Bot.DirectionNow;
	unsigned int* LastDirection = &p->Bot.LastDirectionNow;
	unsigned int* C_Direction = &p->Bot.CountDirectionNow;
	// Bomb bot
	const int WantCheckBomb = 3;
	struct _nearestBomb {
		COORD posBomb = { 0, 0 };
		double distance = 0;
		COORD burstArea[4];
	};

	_nearestBomb nearestBomb[WantCheckBomb], *p_nearestBomb;
	p_nearestBomb = nearestBomb;
	checkBombBot(p, m, &p_nearestBomb->posBomb, &p_nearestBomb->distance);


	//int haveBomb = 0;
	COORD* pos = &p->Position;
	int Len = p->Lenght;
	int Hei = p->Height;

	// Property each of side
	struct _Direction {
		int CountCheckSide;
		int Direction;
		int propertyX;
		int propertyY;
		int CountCanMove;
		bool CantMoveFromBomb;
	};
	_Direction allDirection[4] = {
		{ 0, LEFT , -Len , 0,	0, false},
		{ 0, RIGHT, Len  , 0,	0, false},
		{ 0, DOWN , 0    , Hei,	0, false},
		{ 0, UP	  , 0    , -Hei,0, false}
	};
	
	// ------------------------------------ //
	// Random move
	const int PASS = 1, cantPASS = 0;
	int CheckSide[4] = { PASS, PASS, PASS, PASS };
	int canMoveAmount[4] = { 0, 0, 0, 0 };
	bool haveBomb = false;
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
	while (*C_Direction == 0 && haveBomb == false) {
		for (int n = 0; n < size; n++) {
			int randToMove = rand() % 4;
			unsigned int* CountMoved = &p->Bot.CountMovedThisDirection[n];
			if (CheckSide[n] == PASS && randToMove <= 2) {
				unsigned int temp = *LastDirection;
				*C_Direction = allDirection[n].CountCanMove;
				*LastDirection = *Direction;
				*Direction = allDirection[n].Direction;
				break;
			}
			// absolutely can't move
			if (n == size - 1) { return; }
		}
	}

	// Same direction should change new direction
	unsigned int* CountMoved = &p->Bot.CountMovedThisDirection[*Direction - 1];
	if (*CountMoved >= 3) {
		*CountMoved = 0;
		// if can change direction, should change
		for (int n = 0; n < size; n++) {
			int randToMove = rand() % 4;
			unsigned int* CountMoved = &p->Bot.CountMovedThisDirection[n];
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

	// Check bomb
		// Check area burst
	for (int n = 0; n < WantCheckBomb; n++){
		COORD* posB = &nearestBomb[n].posBomb;
		int count = 0;
		// check left side
		for (int powX = -1; abs(powX)  < m->maxBombPowerX; powX--) {
			if (m->State[posB->Y][posB->X + powX] != CAN_DESTROYED) { count++; }
			else {nearestBomb[n].burstArea[LEFT - 1] = { (SHORT)(posB->X - count), posB->Y };}
		}
		count = 0;
		// check right side
		for (int powX = Len; abs(powX) < m->maxBombPowerX; powX++) {
			if (m->State[posB->Y][posB->X + powX] != CAN_DESTROYED) { count++; }
			else { nearestBomb[n].burstArea[RIGHT - 1] = { (SHORT)(posB->X + count), posB->Y }; }
		}
		count = 0;
		// check down side
		for (int powY = Hei; abs(powY) < m->maxBombPowerY; powY++) {
			if (m->State[posB->Y + powY][posB->X] != CAN_DESTROYED) { count++; }
			else { nearestBomb[n].burstArea[DOWN - 1] = { posB->X, (SHORT)(posB->Y + count)}; }
		}
		count = 0;
		// check up side
		for (int powY = -1; abs(powY) < m->maxBombPowerY; powY--) {
			if (m->State[posB->Y + powY][posB->X] != CAN_DESTROYED) { count++; }
			else { nearestBomb[n].burstArea[UP - 1] = { posB->X, (SHORT)(posB->Y - count) }; }
		}
		count = 0;
	}

	for (int n = WantCheckBomb - 1; n > 0; n--) {
		// within bomb power X -> should change direction
		int randDir = 5;
		if (pos->X >= nearestBomb[n].burstArea[LEFT - 1].X &&
			pos->X <= nearestBomb[n].burstArea[RIGHT - 1].X &&
			pos->Y == nearestBomb[n].posBomb.Y) {
			randDir = rand() % (UP + 1 - DOWN) + DOWN;
			if (randDir == DOWN && allDirection[DOWN - 1].CountCanMove < 1) { randDir = UP; }
			else if (randDir == UP && allDirection[UP - 1].CountCanMove < 1) { randDir = DOWN; }
			//// this direction don't have bomb and can move
			//unsigned int temp = *LastDirection;
			//*C_Direction = allDirection[randDir - 1].CountCanMove;
			//*LastDirection = *Direction;
			//*Direction = allDirection[randDir - 1].Direction;
		}
		// within bomb power Y -> should change direction
		if (pos->Y >= nearestBomb[n].burstArea[UP - 1].Y &&
			pos->Y <= nearestBomb[n].burstArea[DOWN - 1].Y &&
			pos->X == nearestBomb[n].posBomb.X) {
			randDir = rand() % (RIGHT + 1 - LEFT) + RIGHT;
			if (randDir == LEFT && allDirection[LEFT - 1].CountCanMove < 1) { randDir = RIGHT; }
			else if (randDir == RIGHT && allDirection[RIGHT - 1].CountCanMove < 1) { randDir = LEFT; }
		}
		// This direction have bomb
		if (pos->X + allDirection[*Direction - 1].propertyX >= nearestBomb[n].burstArea[LEFT - 1].X &&
				 pos->X + allDirection[*Direction - 1].propertyX <= nearestBomb[n].burstArea[RIGHT - 1].X) {
			randDir = rand() % (UP + 1 - DOWN) + DOWN;
			if (randDir == DOWN && allDirection[DOWN - 1].CountCanMove < 1) { randDir = UP; }
			else if (randDir == UP && allDirection[UP - 1].CountCanMove < 1) { randDir = DOWN; }
		}
		if (pos->Y + allDirection[*Direction - 1].propertyY >= nearestBomb[n].burstArea[UP - 1].Y &&
				 pos->Y + allDirection[*Direction - 1].propertyY <= nearestBomb[n].burstArea[DOWN - 1].Y) {
			randDir = rand() % (RIGHT + 1 - LEFT) + RIGHT;
			if (randDir == LEFT && allDirection[LEFT - 1].CountCanMove < 1) { randDir = RIGHT; }
			else if (randDir == RIGHT && allDirection[RIGHT - 1].CountCanMove < 1) { randDir = LEFT; }
		}
		// this direction don't have bomb and can move
		if (randDir != 5) {
			unsigned int temp = *LastDirection;
			*C_Direction = allDirection[randDir - 1].CountCanMove;
			*LastDirection = *Direction;
			*Direction = allDirection[randDir - 1].Direction;
		}
	}
 
	/*
	if (pos->X == nearestBomb[0].posBomb.X && abs(nearestBomb[0].posBomb.Y) <= m->maxBombPowerY) {
		int randDir = rand() % (UP + 1 - DOWN) + DOWN;
		if (randDir == DOWN && allDirection[randDir - 1].CountCanMove > 1) { randDir = UP; }
		else if (randDir == UP && allDirection[randDir - 1].CountCanMove > 1) { randDir = DOWN; }
		// this direction don't have bomb and can move
		if (randDir != LEFT && randDir != DOWN) {
			unsigned int temp = *LastDirection;
			*C_Direction = allDirection[randDir - 1].CountCanMove;
			*LastDirection = *Direction;
			*Direction = allDirection[randDir - 1].Direction;
		}
	}
	// within bomb power Y
	if ((abs(nearestBomb[0].posBomb.X - pos->X) <= m->maxBombPowerX) && pos->Y == nearestBomb[0].posBomb.Y) {
		int randDir = rand() % (RIGHT + 1 - LEFT) + RIGHT;
		if (randDir == LEFT && allDirection[randDir - 1].CountCanMove > 1) { randDir = RIGHT; }
		else if (randDir == RIGHT && allDirection[randDir - 1].CountCanMove > 1) { randDir = LEFT; }
		// this direction don't have bomb and can move
		if (randDir != DOWN && randDir != UP) {
			unsigned int temp = *LastDirection;
			*C_Direction = allDirection[randDir - 1].CountCanMove;
			*LastDirection = *Direction;
			*Direction = allDirection[randDir - 1].Direction;
		}
	}
	*/

	// Move bot (Part: selected direction )
	checkControl(*Direction, p, m);
	dropBombBot(p, m);
	(*C_Direction)--;
	(*CountMoved)++;
}

void dropBombBot(Player* p, Map* m) {
	COORD* pos = &p->Position;
	bool* drop = &p->Bot.CanDropBomb;
	int Amount = p->Bomb.Amount;
	int Hei = p->Height;
	int Len = p->Lenght;
	int check = 0;
	int CanDropBomb = 1;
	// Check can drop bomb
	if (m->State[pos->Y][pos->X - Len] == CAN_DESTROYED) { check++; }
	if (m->State[pos->Y][pos->X + Len] == CAN_DESTROYED) { check++; }
	if (m->State[pos->Y + Hei][pos->X] == CAN_DESTROYED) { check++; }
	if (m->State[pos->Y - Hei][pos->X] == CAN_DESTROYED) { check++; }
	// Drop only 1 bomb 
	if (p->Bomb.Drop == 0) { *drop = true; }
	if (*drop == true && check > 0) {
		int i = 0;
		if (p->Bomb.Drop < Amount) {
			for (int c = 0; c < Amount; c++) {
				if (p->Bomb.State[c] == BOMB_COUNTING) { i++; }
			}
			if (m->State[pos->Y][pos->X] == Bomb_Nm.NormalState) {
				return;
			}
			if (p->Bomb.Drop < /*Amount - i*/ CanDropBomb) { 
				p->Bomb.Drop++; 
				*drop = false;
			}
		}
	}
}

void checkBombBot(Player* p, Map* m, COORD* posBomb, double* distanceBomb) {
	int haveBomb = 0;
	COORD* pos = &p->Position;
	int Len = p->Lenght;
	int Hei = p->Height;
	//double distanceBomb[2];
	// Check bomb all map
	for (int n = 0; n < 3; n++) {
		posBomb[n].X = 0;
		posBomb[n].Y = 0;
		distanceBomb[n] = 0;
	}
	for (short pY = 0; pY < MAP_HEIGHT; pY++) {
		for (short pX = 0; pX < MAP_WIDTH; pX++) {
			if (m->State[pY][pX] == Bomb_Nm.NormalState &&
				m->State[pY][pX + (Len - 1)] == Bomb_Nm.NormalState &&
				m->State[pY + (Hei - 1)][pX] == Bomb_Nm.NormalState) {
				int deltaX = pX - pos->X;
				int deltaY = pY - pos->Y;
				//*(posBomb + 2) = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
				distanceBomb[2] = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
				posBomb[2] = { pX, pY };
				if (posBomb[0].X == 0 && posBomb[0].Y == 0) {
					posBomb[0] = posBomb[2];
					distanceBomb[0] = distanceBomb[2];
					posBomb[1] = posBomb[2];
					distanceBomb[1] = distanceBomb[2];
				}
				else if (distanceBomb[2] < distanceBomb[1]) {
					if (distanceBomb[2] < distanceBomb[0]) {
						double temp = distanceBomb[1];
						distanceBomb[1] = distanceBomb[0];
						distanceBomb[0] = distanceBomb[2];
						distanceBomb[2] = temp;
						COORD tempC = posBomb[1];
						posBomb[1] = posBomb[0];
						posBomb[0] = posBomb[2];
						posBomb[2] = tempC;
					}
					else {
						double temp = distanceBomb[1];
						distanceBomb[1] = distanceBomb[2];
						distanceBomb[2] = temp;
						COORD tempC = posBomb[1];
						posBomb[1] = posBomb[2];
						posBomb[2] = tempC;
					}
				}
				haveBomb++;
			}
		}
	}
	// if COORD (0,0) = no bomb
	for (int n = 0; n < 3; n++) {
		if (posBomb[n].X == 0 && posBomb[n].Y == 0) {
			posBomb[n] = { SCREEN_WIDTH, SCREEN_HEIGHT };
		}
	}
}

//void checkBombPowerBot(Player* p, Map* m, COORD* nearestBomb, unsigned int* Direction) {
//	COORD* pos = &p->Position;
//	int Len = p->Lenght;
//	int Hei = p->Height;
//
//	struct _Direction {
//		int CountCheckSide = 0;
//		int Direction;
//		int propertyX;
//		int propertyY;
//		int CountCanMove;
//	};
//	_Direction allDirection[4] = {
//		{ 0, LEFT , -maxBombPowerX , 0    , 0},
//		{ 0, RIGHT, maxBombPowerX  , 0	  , 0},
//		{ 0, DOWN , 0    , maxBombPowerY  , 0},
//		{ 0, UP	  , 0    , -maxBombPowerY , 0}
//	};
//}