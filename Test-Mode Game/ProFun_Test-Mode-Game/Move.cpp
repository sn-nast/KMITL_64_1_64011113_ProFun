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
	int randColorInDeathless = rand ();
	for (int H = 0; H < Hei; H++) {
		for (int L = 0; L < Len; L++) {
			int color = p->Attribute;
			if (p->DeathlessTime > 0) {
				if ((H < Hei / 2 && L < Len / 2) ||
					(H > Hei / 2 && L < Len / 2) ||
					(H < Hei / 2 && L > Len / 2) ||
					(H > Hei / 2 && L > Len / 2)
					) {
					color = randColorInDeathless;
				}
				//if (H == Hei / 2 && L == Len / 2) { color = p->Attribute; }
				//else { 
			}
			if (H == Hei / 2 && L == Len / 2) { continue; }
			putBuffer(p->Position.X + L, p->Position.Y + H, p->Format[0], color);
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
	putBuffer(posD.X + dirX/2, posD.Y + dirY/2, Arrow, p->Dir_atb);
	keepObject(p, m);
}