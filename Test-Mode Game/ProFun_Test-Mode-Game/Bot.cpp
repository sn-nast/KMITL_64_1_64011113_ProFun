#include "Bot.h"
#include "main.h"
#include "Move.h"
#include "Buffer.h"
#include "Control.h"
#include "Bomb.h"
#include "Map.h" 
#include "Object.h"

void setupBot(Player* p) {
	strcpy_s(p->Format, "O");
	strcpy_s(p->Name, "BOT NO.1");
	p->Lenght = strlen(p->Format);
	p->Height = 1;
	p->Attribute = 7;
	p->SpeedX = 1;
	p->Bomb.Amount = 10;
	setupBomb(p);
}

void setOfBot(Player* p, Map* m) {
	dropBombBot(p, m);
	setOfBomb(p, m);
	playerMove(p, m);
}

void moveBot(Player* p, Map* m) {
	p->Last_position.X = p->Position.X;
	p->Last_position.Y = p->Position.Y;
	bool canMove = true;
	int Direction;
	while (canMove) {
		Direction = rand() % (4 + 1 - 1) + 1;
		checkControl(Direction, p, m);
		if (p->Position.X != p->Last_position.X ||
			p->Position.Y != p->Last_position.Y) {
			canMove = false;
		}
	}
}

void dropBombBot(Player* p, Map* m) {
	COORD* pos = &p->Position;
	int drop = rand();
	int size = p->Bomb.Amount;
	int i = 0;
	if (drop % 5 == 0) {
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