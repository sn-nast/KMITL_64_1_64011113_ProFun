#include "Move.h"
#include "main.h"
#include "Buffer.h"
#include "Map.h"

void playerMove(Player* p) {
	int Len = p->Lenght;
	short Arrow;
	for (int i = 0; i < Len; i++) {
		putBuffer((p->Position.X) + i, p->Position.Y, p->Format[i], p->Attribute);
	}
	// Direction arrow
	if (((p->Position.X) != (p->Last_position.X)) || ((p->Position.Y) != (p->Last_position.Y))) {
		p->Last_Direction = p->Direction;

		if ((p->Position.X) > (p->Last_position.X)) {
			p->Direction.X = p->Position.X + Len;
			p->Direction.Y = p->Position.Y;
			Arrow = RIGHT_ARROW_1;
		}
		else if ((p->Position.X) < (p->Last_position.X)) {
			p->Direction.X = p->Position.X - Len / 2;
			p->Direction.Y = p->Position.Y;
			Arrow = LEFT_ARROW_1;
		}
		else if ((p->Position.Y) > (p->Last_position.Y)) {
			p->Direction.X = p->Position.X + Len / 2;
			p->Direction.Y = p->Position.Y + (p->Height + 1);
			Arrow = DOWN_ARROW_2;
		}
		else if ((p->Position.Y) < (p->Last_position.Y)) {
			p->Direction.X = p->Position.X + Len / 2;
			p->Direction.Y = p->Position.Y - (p->Height + 1);
			Arrow = UP_ARROW_2;
		}
		COORD pos = { p->Direction.X, p->Direction.Y };
		putBuffer(pos.X, pos.Y, Arrow, p->Attribute);
	}
}
