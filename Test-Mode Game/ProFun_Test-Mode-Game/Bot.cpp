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
	setupBomb(p);
}

void setOfBot(Player* p, Map* m) {
	//dropBombBot(p, m);
	//setOfBomb(p, m);
	playerMove(p, m);
}

void moveBot(Player* p, Map* m) {
	p->Last_position.X = p->Position.X;
	p->Last_position.Y = p->Position.Y;
	bool canMove = true;
	unsigned int* Direction = &p->Bot.DirectionNow;
	unsigned int* C_Direction = &p->Bot.CountDirectionNow;
	while (*C_Direction - p->Bomb.PowerX < 2) { *C_Direction++; }
	while (canMove) {
		if (*C_Direction > 0) { *Direction = rand() % (4 + 1 - 1) + 1; }
		//*Direction = rand() % (4 + 1 - 1) + 1;
		checkControl(*Direction, p, m);
		if (p->Position.X != p->Last_position.X ||
			p->Position.Y != p->Last_position.Y) {
			canMove = false;
		}
		*C_Direction--;
	}
}

void dropBombBot(Player* p, Map* m) {
	COORD* pos = &p->Position;
	int drop = rand();
	int size = p->Bomb.Amount;
	int i = 0;
	if (drop % 10 == 0) {
		if (p->Bomb.Drop < size) {
			for (int c = 0; c < size; c++) {
				if (p->Bomb.State[c] == 2) { i++; }
			}
			if (m->State[pos->Y][pos->X] == Bomb_Nm.NormalState) {
				return;
			}
			if (p->Bomb.Drop < size - i) { p->Bomb.Drop++; }
		}
	}
}