#include "Bot.h"
#include "main.h"
#include "Move.h"
#include "Buffer.h"
#include "Control.h"
#include "Bomb.h"
#include "Map.h" 
#include "Object.h"

void setupBot(Player* p) {
	strcpy_s(p->Format, "[O]");
	p->Lenght = strlen(p->Format);
	p->Height = 1;
	p->Attribute = 7;
	p->SpeedX = 1;
	setupBomb(p);
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

//void dropBomb