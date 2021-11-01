#include "Move.h"
#include "main.h"
#include "Buffer.h"
#include "Map.h"
#include "Object.h"

void playerMove(Player* p, Map* m) {
	int Len = p->Lenght;
	int Hei = p->Height;
	COORD* pos = &p->Position;
	// Player format
	for (int H = 0; H < Hei; H++) {
		for (int L = 0; L < Len; L++) {
			putBuffer(p->Position.X + L, p->Position.Y + H, p->Format[0], p->Attribute);
		}
	}
	// Direction arrow
	int dirX, dirY;
	short Arrow;
	p->Last_Direction = p->Direction;
	if ((p->Position.X) > (p->Last_Position.X)) {
		p->Direction.X = p->Position.X + Len;
		p->Direction.Y = p->Position.Y;
		Arrow = RIGHT_ARROW_1;
		dirX = 0;
		dirY = Hei;
	}
	else if ((p->Position.X) < (p->Last_Position.X)) {
		p->Direction.X = p->Position.X - 1;
		p->Direction.Y = p->Position.Y;
		Arrow = LEFT_ARROW_1;
		dirX = 0;
		dirY = Hei;
	}
	else if ((p->Position.Y) > (p->Last_Position.Y)) {
		p->Direction.X = p->Position.X /*+ Len / 2*/;
		p->Direction.Y = p->Position.Y + Hei;
		Arrow = DOWN_ARROW_2;
		dirX = Len;
		dirY = 0;
	}
	else if ((p->Position.Y) < (p->Last_Position.Y)) {
		p->Direction.X = p->Position.X /*+ Len / 2*/;
		p->Direction.Y = p->Position.Y - 1;
		Arrow = UP_ARROW_2;
		dirX = Len;
		dirY = 0;
	}
	else { return; }
	COORD posD = { p->Direction.X, p->Direction.Y };
	//for (int L = 0; L < dirX; L++) {
	//	putBuffer(posD.X + L, posD.Y, Arrow, p->Dir_atb);
	//}
	//for (int H = 0; H < dirY; H++) {
	//	putBuffer(posD.X, posD.Y + H, Arrow, p->Dir_atb);
	//}
	putBuffer(posD.X + dirX/2, posD.Y + dirY/2, Arrow, p->Dir_atb);
	keepObject(p, m);
}