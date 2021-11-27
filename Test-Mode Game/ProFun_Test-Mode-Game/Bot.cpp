#include "Bot.h"
#include "main.h"
#include "Move.h"
#include "Buffer.h"
#include "Control.h"
#include "Bomb.h"
#include "Map.h" 
#include "Object.h"

Player playerBot[3];
const int amountBot = sizeof(playerBot) / sizeof(playerBot[0]);
COORD startMap = { 2, 1 };
COORD endMap = { MAP_WIDTH - 4, MAP_HEIGHT - 2 };

void setupAllPlayerBot() {
	unsigned int tempColor[3] = {0, 0, 0};

	for (int n = 0; n < amountBot; n++) {
		tempColor[n] = rand() % (256 - 31) + 31;
		setupPlayerBot(&playerBot[n]);
		playerBot[n].Call = (n + 1) * 11;
	}
	if (tempColor[1] - tempColor[0] < 16) { tempColor[1] += 16; }
	if (tempColor[2] - tempColor[1] < 16) { tempColor[2] += 16; }

	for (int n = 0; n <= amountBot; n++) {
		playerBot[n].Attribute = tempColor[n];
	}

	playerBot[0].Position = { 44, 1 };
	playerBot[1].Position = { 2, 37 };
	playerBot[2].Position = { 44, 37 };

	strcpy(playerBot[0].Name, "Bot 1");
	strcpy(playerBot[1].Name, "Bot 2");
	strcpy(playerBot[2].Name, "Bot 3");

	for (int n = 0; n < amountBot; n++) {
		playerBot[n].StartPositon = playerBot[n].Position;
	}
}

void setupPlayerBot(Player* p) {
	strcpy_s(p->Format, "N");
	p->Bomb.Amount = 1;
	p->Bot.CountDirectionNow = 0;
	for (int n = 0; n < 4; n++) {
		p->Bot.CountMovedThisDirection[n] = 0;
		p->Bot.CountCantMoveThisDirection[n] = 0;
	}
	p->Bot.MaxCanDropBomb = 1;
	p->Bot.Alive = true;
	p->Bot.DirectionNow = 4;
}

void setOfAllBot(Map* m) {
	for (int n = 0; n < amountBot; n++) {
		if (playerBot[n].Bot.Alive == false) { continue; }
		setOfBomb(&playerBot[n], m);
		// Move bot (Part: draw bot)
		playerMove(&playerBot[n], m);
	}
}

void moveBot(Player* p, Map* m) {
	unsigned int timeNow = (m->GameTime_Minute * 60) + m->GameTime_Second;
	// ptr about Bot Direction
	unsigned int* Direction = &p->Bot.DirectionNow;
	unsigned int* LastDirection = &p->Bot.LastDirectionNow;
	unsigned int* C_Direction = &p->Bot.CountDirectionNow;
	// Bomb bot
	const int sizeCheckBomb = 2;
	const int sizeWantCheckBomb = 1;

	struct _nearestBomb {
		COORD posBomb = { 0, 0 };
		double distance = 0;
		COORD burstArea[4];
	};

	_nearestBomb nearestBomb[sizeCheckBomb];
	checkBombBot(p, m, &nearestBomb->posBomb, &nearestBomb->distance, sizeCheckBomb);
	bool nearMainPlayer = checkNearMainPlayer(p, m, 5, 5);
	bool downLevel = false;
	/*------------------------ Part Moveing -------------------------*/
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
	int CheckSide[4] = { cantPASS, cantPASS, cantPASS, cantPASS };
	// Check side can move
	if (checkStateControl(p, m->State[pos->Y][pos->X - Len]) == PASS && pos->X - Len >= startMap.X)		{ CheckSide[0] = PASS; }
	if (checkStateControl(p, m->State[pos->Y][pos->X + Len]) == PASS && pos->X + Len <= endMap.X)		{ CheckSide[1] = PASS; }
	if (checkStateControl(p, m->State[pos->Y + Hei][pos->X]) == PASS && pos->Y + Hei <= endMap.Y)		{ CheckSide[2] = PASS; }
	if (checkStateControl(p, m->State[pos->Y - Hei][pos->X]) == PASS && pos->Y - Hei >= startMap.Y)		{ CheckSide[3] = PASS; }
	int sizeSide = sizeof(CheckSide) / sizeof(CheckSide[0]);
	// Count lenght can move
	for (int n = 0; n < sizeSide; n++) {
		if ((n == LEFT - 1 || n == RIGHT - 1) && CheckSide[n] == PASS) {
			for (int Mw = allDirection[n].propertyX; pos->X + Mw <= endMap.X && pos->X + Mw >= startMap.X; Mw += allDirection[n].propertyX) {
				if (checkStateControl(p, m->State[pos->Y][pos->X + Mw]) == PASS) {
					allDirection[n].CountCanMove++;
				}
				else { break; }
			}
		}
		else if ((n == DOWN - 1 || n == UP - 1) && CheckSide[n] == PASS) {
			for (int Mh = allDirection[n].propertyY; pos->Y + Mh <= endMap.Y && pos->Y + Mh >= startMap.Y; Mh += allDirection[n].propertyY) {
				if (checkStateControl(p, m->State[pos->Y + Mh][pos->X]) == PASS) {
					allDirection[n].CountCanMove++;
				}
				else { break; }
			}
		}
	}
	
	// Random select move
	// no bomb and Count dir = 0
	bool haveBomb = false;
	if (*C_Direction <= 0 && haveBomb == false) {
		for (int n = 0; n < sizeSide; n++) {
			int randToMove = rand() % 4;
			unsigned int* CountMoved = &p->Bot.CountMovedThisDirection[n];
			if (CheckSide[n] == PASS) {
				unsigned int temp = *LastDirection;
				*C_Direction = allDirection[n].CountCanMove;
				*LastDirection = *Direction;
				*Direction = allDirection[n].Direction;
				p->Bot.MaxCanMove[n] = allDirection[n].CountCanMove;
				break;
			}
			// absolutely can't move
			if (n == sizeSide - 1) { haveBomb = true; }
		}
	}

	// Same direction should change new direction
	unsigned int* CountMoved = &p->Bot.CountMovedThisDirection[*Direction - 1];
	unsigned int* CountCantMove = &p->Bot.CountCantMoveThisDirection[*Direction - 1];
	int randMaxCountMoved = rand() % (8 + 1 - 3) + 3;
	int randToMove = rand() % 10;
	if (*CountMoved >= p->Bot.MaxCanMove[*Direction - 1] / 2 + 1
		/*p->Bot.MaxCanMove[*Direction - 1] >= randMaxCountMoved */) {
		*CountMoved = 0;
		// if can change direction, should change
		for (int n = 0; n < sizeSide; n++) {
			int randToMove = rand() % 4;
			// can pass and not same direction 
			if ((CheckSide[n] == cantPASS)) { continue; }
			// L, R -> U, D
			if ((*Direction == LEFT || *Direction == RIGHT) &&
				(n == DOWN - 1 || n == UP - 1)) {
				*C_Direction = allDirection[n].CountCanMove;
				*LastDirection = *Direction;
				*Direction = allDirection[n].Direction;
				p->Bot.MaxCanMove[n] = allDirection[n].CountCanMove;
				break;
			}
			// U, D -> L, R
			else if ((*Direction == DOWN || *Direction == UP) &&
				(n == LEFT - 1 || n == RIGHT - 1)) {
				*C_Direction = allDirection[n].CountCanMove;
				*LastDirection = *Direction;
				*Direction = allDirection[n].Direction;
				p->Bot.MaxCanMove[n] = allDirection[n].CountCanMove;
				break;
			}
			// absolutely can't change direction
			if (n == sizeSide - 1) { break; }
		}
	}
	
	// Check bomb
		// Check area burst
	for (int n = 0; n < sizeWantCheckBomb; n++) {
		if (nearestBomb[n].distance == 0) { continue; }
		COORD* posB = &nearestBomb[n].posBomb;
		int count = 0;
		int countWall = 0;
		int checkPowerX = 0, checkPowerY = 0;
		if (levelPlayer == 1) {
			if (m->maxBombPowerX > 3) {
				checkPowerX = m->maxBombPowerX - 3;
				checkPowerY = m->maxBombPowerY - 3;
			}
			else {
				checkPowerX = 2;
				checkPowerY = 2;
			}
		}
		else {
			checkPowerX = m->maxBombPowerX + 3;
			checkPowerY = m->maxBombPowerY + 3;
		}
		// check left side (within map width)
		for (int powX = -Len; abs(powX) <= checkPowerX * Len && posB->X + powX > 1; powX -= Len) {
			if (m->State[posB->Y][posB->X + powX] != CAN_DESTROYED) { 
				if (m->State[posB->Y][posB->X + powX] == CANt_DESTROYED) { break; }
				count++; 
			}
			else {
				count++;
				break;
			}
		}
		nearestBomb[n].burstArea[LEFT - 1] = { (SHORT)(posB->X - (count * Len)), posB->Y };
		count = 0;

		// check right side (within map width)
		for (int powX = Len; abs(powX) <= checkPowerX * Len && posB->X + powX < MAP_WIDTH - 1; powX += Len) {
			if (m->State[posB->Y][posB->X + powX] != CAN_DESTROYED) {
				if (m->State[posB->Y][posB->X + powX] == CANt_DESTROYED) { break; }
				count++;
			}
			else {
				count++;
				break;
			}
		}
		nearestBomb[n].burstArea[RIGHT - 1] = { (SHORT)(posB->X + (count * Len)), posB->Y };
		count = 0;
		// check down side (within map height)
		for (int powY = Hei; abs(powY) <= checkPowerY * Hei && posB->Y + powY < MAP_HEIGHT - 1; powY += Hei) {
			if (m->State[posB->Y + powY][posB->X] != CAN_DESTROYED) {
				if (m->State[posB->Y + powY][posB->X] == CANt_DESTROYED) { break; }
				count++;
			}
			else {
				count++;
				break;
			}
		}
		nearestBomb[n].burstArea[DOWN - 1] = { posB->X, (SHORT)(posB->Y + (count * Hei)) };
		count = 0;

		// check up side (within map height)
		for (int powY = -Hei; abs(powY) <= checkPowerY * Hei && posB->Y + powY > 0; powY -= Hei) {
			if (m->State[posB->Y + powY][posB->X] != CAN_DESTROYED) {
				if (m->State[posB->Y + powY][posB->X] == CANt_DESTROYED) { break; }
				count++;
			}
			else {
				count++;
				break;
			}
		}
		nearestBomb[n].burstArea[UP - 1] = { posB->X, (SHORT)(posB->Y - (count * Hei)) };
	}

		// within bomb power X -> should change direction
	for (int n = 0; n < sizeWantCheckBomb; n++) {
		int randDir = 5;
		// pos with bomb (drop bomb)
		if (pos->X == nearestBomb[n].posBomb.X &&
			pos->Y == nearestBomb[n].posBomb.Y) {
			int tempCount[2] = { 0,0 };
			int anotherRandDir = 5;
			for (int i = 0; i < sizeSide; i++) {
				if (allDirection[i].CountCanMove >= tempCount[1]) {
					tempCount[1] = allDirection[i].CountCanMove;
					anotherRandDir = i + 1;
					if (tempCount[1] >= tempCount[0]) {
						int temp = tempCount[0];
						int tempRandDir = randDir;
						tempCount[0] = tempCount[1];
						randDir = anotherRandDir;
						tempCount[1] = temp;
						anotherRandDir = tempRandDir;
					}
				}
			}
			bool haveNewDir = true;
			if (levelPlayer == 2 || timeNow > 4 * 60) {
				if (randDir == LEFT || randDir == RIGHT) {
					for (int i = 1; i <= tempCount[0]; i++) {
						if ((checkStateControl(p, m->State[pos->Y - 1][pos->X + (allDirection[randDir - 1].propertyX * i)]) == 1) ||
							(checkStateControl(p, m->State[pos->Y + Hei][pos->X + (allDirection[randDir - 1].propertyX * i)]) == 1)) {
							haveNewDir = false;
							break;
						}
					}
				}
				else if (randDir == DOWN || randDir == UP) {
					for (int i = 1; i <= tempCount[0]; i++) {
						if ((checkStateControl(p, m->State[pos->Y + (allDirection[randDir - 1].propertyY * i)][pos->X - 1]) == 1) ||
							(checkStateControl(p, m->State[pos->Y + (allDirection[randDir - 1].propertyY * i)][pos->X + Len]) == 1)) {
							haveNewDir = false;
							break;
						}
					}
				}
				if (haveNewDir == true) { randDir = anotherRandDir; }
			}
			haveBomb = true;
		}
		else if (pos->X >= nearestBomb[n].burstArea[LEFT - 1].X &&
			pos->X <= nearestBomb[n].burstArea[RIGHT - 1].X &&
			pos->Y == nearestBomb[n].posBomb.Y) {
			bool mustNewDir = false;
			randDir = rand() % (UP + 1 - DOWN) + DOWN;
			int tempCheck = 0;
			while (tempCheck < 2 && allDirection[randDir - 1].CountCanMove < 1) {
				if (randDir == DOWN) { randDir = UP; }
				else if (randDir == UP) { randDir = DOWN; }
				tempCheck++;
				mustNewDir = false;
				if (tempCheck == 2) { mustNewDir = true; }
			}
			if (mustNewDir == true) {
				if (pos->X >= nearestBomb[n].burstArea[LEFT - 1].X &&
					pos->X <= nearestBomb[n].posBomb.X &&
					pos->Y == nearestBomb[n].posBomb.Y) {
					randDir = LEFT;
				}
				else if (pos->X >= nearestBomb[n].posBomb.X &&
					pos->X <= nearestBomb[n].burstArea[RIGHT - 1].X &&
					pos->Y == nearestBomb[n].posBomb.Y) {
					randDir = RIGHT;
				}
			}
			haveBomb = true;
		}

		else if (pos->Y >= nearestBomb[n].burstArea[UP - 1].Y &&
			pos->Y <= nearestBomb[n].burstArea[DOWN - 1].Y &&
			pos->X == nearestBomb[n].posBomb.X) {
			bool mustNewDir = false;
			randDir = rand() % (RIGHT + 1 - LEFT) + LEFT;
			int tempCheck = 0;
			while (tempCheck < 2 && allDirection[randDir - 1].CountCanMove < 1) {
				if (randDir == LEFT && allDirection[LEFT - 1].CountCanMove < 1) { randDir = RIGHT; }
				else if (randDir == RIGHT && allDirection[RIGHT - 1].CountCanMove < 1) { randDir = LEFT; }
				tempCheck++;
				mustNewDir = false;
				if (tempCheck == 2) { mustNewDir = true; }
			}
			if (mustNewDir == true) {
				if (pos->Y >= nearestBomb[n].burstArea[UP - 1].Y &&
					pos->Y <= nearestBomb[n].posBomb.Y &&
					pos->X == nearestBomb[n].posBomb.X) {
					randDir = UP;
				}
				else if (pos->Y >= nearestBomb[n].posBomb.Y &&
					pos->Y <= nearestBomb[n].burstArea[DOWN - 1].Y &&
					pos->X == nearestBomb[n].posBomb.X) {
					randDir = DOWN;
				}
			}
			haveBomb = true;
		}

		// This direction have bomb
		else if (pos->X + allDirection[*Direction - 1].propertyX >= nearestBomb[n].burstArea[LEFT - 1].X &&
			pos->X + allDirection[*Direction - 1].propertyX <= nearestBomb[n].burstArea[RIGHT - 1].X &&
			pos->Y + allDirection[*Direction - 1].propertyY == nearestBomb[n].posBomb.Y) {
			randDir = rand() % (RIGHT + 1 - LEFT) + LEFT;
			haveBomb = true;
		}
		else if (pos->Y + allDirection[*Direction - 1].propertyY >= nearestBomb[n].burstArea[UP - 1].Y &&
			pos->Y + allDirection[*Direction - 1].propertyY <= nearestBomb[n].burstArea[DOWN - 1].Y &&
			pos->X + allDirection[*Direction - 1].propertyX == nearestBomb[n].posBomb.X) {
			randDir = rand() % (UP + 1 - DOWN) + DOWN;
			haveBomb = true;

		}

		// Use this direction
		if (randDir != 5 && haveBomb == true) {
			unsigned int temp = *LastDirection;
			*C_Direction = allDirection[randDir - 1].CountCanMove;
			*LastDirection = *Direction;
			*Direction = randDir;
			p->Bot.MaxCanMove[n] = allDirection[n].CountCanMove;

		}
	}
 
	// Move bot (Part: selected direction )
	COORD tempCheckPos = p->Position;
	int randFinalToMove = rand() % 10;
	if (haveBomb == true) { checkControl(*Direction, p, m);}
	else if (levelPlayer == 1 && randFinalToMove < 6) { checkControl(*Direction, p, m); }
	else if (levelPlayer == 2 && randFinalToMove < 8) { checkControl(*Direction, p, m); }
	if (tempCheckPos.X == p->Position.X && tempCheckPos.Y == p->Position.Y) {
		(*CountCantMove)++;
	}
	if (*C_Direction > 0){ (*C_Direction)--;}
	(*CountMoved)++;
}

void moveAllBot(Map* m) {
	for (int n = 0; n < amountBot; n++) {
		if (playerBot[n].Bot.Alive == false) { continue; }
		moveBot(&playerBot[n], m);
	}
}

void checkBombAllBot(Map* m) {
	for (int n = 0; n < amountBot; n++) {
		if (playerBot[n].Bot.Alive == false) { 
			int amountCountDownBomb = sizeof(playerBot->Bomb.CountDn) / sizeof(playerBot->Bomb.CountDn[0]);
			int checkNoCountDown = 0;
			for (int i = 0; i < amountCountDownBomb; i++) {
				if (playerBot[n].Bomb.CountDn[i] == 0) { checkNoCountDown++; }
			}
			if (checkNoCountDown == amountCountDownBomb) { continue; }
		}
		checkBomb(&playerBot[n], m);
	}
}

void summaryAllBot() {
	for (int n = 1; n <= amountBot; n++) {
		summary(&playerBot[n - 1], { MAP_WIDTH + 3, (SHORT)(summaryLastLine + (n * 10))});
	}
}

void dropBombBot(Player* p, Map* m) {
	COORD* pos = &p->Position;
	bool canDropStatus = false;
	int Hei = p->Height;
	int Len = p->Lenght;
	int check = 0;
	// Check can drop bomb
	if (m->State[pos->Y][pos->X - Len] == CAN_DESTROYED && pos->X - Len >= startMap.X) { check++; }
	if (m->State[pos->Y][pos->X + Len] == CAN_DESTROYED && pos->X + Len <= endMap.X) { check++; }
	if (m->State[pos->Y + Hei][pos->X] == CAN_DESTROYED && pos->Y + Hei <= endMap.Y) { check++; }
	if (m->State[pos->Y - Hei][pos->X] == CAN_DESTROYED && pos->Y - Hei >= startMap.Y) { check++; }
	// Drop only 1 bomb 
	int randToDrop = rand() % 5;
	COORD posAnotherPlayer[4] = { 0, 0, 0, 0 };
	double distanceAnotherPlayer[4] = { 0, 0, 0, 0 };
	int xCheck = 2, yCheck = 2;
	if (levelPlayer == 2) { xCheck = 3; yCheck = 3; }

	// check player
	if (check == 0) {
		for (int n = 0; n < 4; n++) {
			distanceAnotherPlayer[n] = findPlayerPostion(p, &posAnotherPlayer[n], n);
			if (posAnotherPlayer[n].X == pos->X && posAnotherPlayer[n].Y == pos->Y) { continue; }
			if ((posAnotherPlayer[n].X >= pos->X - (xCheck * Len) &&
				posAnotherPlayer[n].X <= pos->X + (xCheck * Len) &&
				posAnotherPlayer[n].Y == pos->Y)
				|| (posAnotherPlayer[n].Y >= pos->Y - (yCheck * Hei) &&
					posAnotherPlayer[n].Y <= pos->Y + (yCheck * Hei)&&
					posAnotherPlayer[n].X == pos->X)) {
				if (levelPlayer == 1) {
					p->Bot.MaxCanDropBomb = 1;
				}
				else if (levelPlayer == 2){ 
					if (p->Bomb.Amount / 2 < 1) {
						p->Bot.MaxCanDropBomb = 3;
					}
				}
				canDropStatus = true;
				check++;
				break;
			}
			else {
				p->Bot.MaxCanDropBomb = 1;
				canDropStatus = false;
			}
		}
	}

	if (p->Bomb.CountBombDropNow == 0) { canDropStatus = true; }
	if (canDropStatus == true && check > 0 && randToDrop < 3) {
		int i = 0;
		if (p->Bomb.CountBombDropNow < p->Bot.MaxCanDropBomb && p->Bot.MaxCanDropBomb <= p->Bomb.Amount) {
			if (m->State[pos->Y][pos->X] == Bomb_Nm.NormalState) {
				return;
			}
			p->Bomb.NewDrop++;
			p->Bot.MaxCanDropBomb = 1;
		}
	}
}

void dropBombAllBot(Map* m) {
	for (int n = 0; n < amountBot; n++) {
		if (playerBot[n].Bot.Alive == false) { continue; }
		dropBombBot(&playerBot[n], m);
	}
}

void checkBombBot(Player* p, Map* m, COORD* posBomb, double* distanceBomb, const int sizeWantCheckBomb) {
	int haveBomb = 0;
	COORD* pos = &p->Position;
	int Len = p->Lenght;
	int Hei = p->Height;

	for (int n = 0; n < sizeWantCheckBomb; n++) {
		posBomb[n].X = 0;
		posBomb[n].Y = 0;
		distanceBomb[n] = SCREEN_WIDTH;
	}

	// Check bomb all map
	for (short pY = 0; pY < MAP_HEIGHT; pY++) {
		for (short pX = 0; pX < MAP_WIDTH; pX++) {
			if (m->State[pY][pX] == Bomb_Nm.NormalState &&
				m->State[pY][pX + (Len - 1)] == Bomb_Nm.NormalState &&
				m->State[pY + (Hei - 1)][pX] == Bomb_Nm.NormalState) {
				int deltaX = pX - pos->X;
				int deltaY = pY - pos->Y;
				distanceBomb[sizeWantCheckBomb - 1] = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
				posBomb[sizeWantCheckBomb - 1].X = pX;
				posBomb[sizeWantCheckBomb - 1].Y = pY;

				for (int n = sizeWantCheckBomb - 1; n >= 0; n--) {
					for (int i = n - 1; i >= 0; i--) {
						if (distanceBomb[n] < distanceBomb[i]) {
							double tempDistance = distanceBomb[i];
							COORD tempPos;
							tempPos.X = posBomb[i].X;
							tempPos.Y = posBomb[i].Y;

							distanceBomb[i] = distanceBomb[n];
							posBomb[i].X = posBomb[n].X;
							posBomb[i].Y = posBomb[n].Y;

							distanceBomb[n] = tempDistance;
							posBomb[n].X = tempPos.X;
							posBomb[n].Y = tempPos.Y;

						}
					}
				}
				haveBomb++;
			}
		}
	}

	// if COORD (0,0) = no bomb
	for (int n = 0; n < 3; n++) {
		if (posBomb[n].X == 0 && posBomb[n].Y == 0) {
			distanceBomb[n] = SCREEN_WIDTH;
			posBomb[n] = { SCREEN_WIDTH, SCREEN_HEIGHT };
		}
	}
}

bool checkNearMainPlayer(Player* p, Map* m, int xCheck, int yCheck){
	COORD* posPM = &playerMe.Position;
	COORD* posBot = &p->Position;
	int Len = p->Lenght;
	int Hei = p->Height;
	bool check = false;
	// in area check
	if (posPM->X >= posBot->X - (xCheck * Len) && posPM->X <= posBot->X + (xCheck * Len) &&
		posPM->Y >= posBot->Y - (yCheck * Hei) && posPM->Y <= posBot->Y + (xCheck * Hei)) {
		check = true;
	}
	return check;
}

double findPlayerPostion(Player* p, COORD* posAnotherPlayer, int nPlayer) {
	COORD* pos = &p->Position;
	if (nPlayer == 0) {
		*posAnotherPlayer = playerMe.Position;
	}
	else if (nPlayer == 1) {
		*posAnotherPlayer = playerBot[0].Position;
	}
	else if (nPlayer == 2) {
		*posAnotherPlayer = playerBot[1].Position;
	}
	else if (nPlayer == 3) {
		*posAnotherPlayer = playerBot[2].Position;
	}

	int deltaX = posAnotherPlayer->X - pos->X;
	int deltaY = posAnotherPlayer->Y - pos->Y;
	double distance = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
	if (distance == 0) { distance = SCREEN_WIDTH; }
	return distance;
}