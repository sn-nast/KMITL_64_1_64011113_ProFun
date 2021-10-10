#include "Move.h"
#include "main.h"
#include "Buffer.h"
#include "Map.h"
#include "Object.h"

void playerMove(Player* p, Map* m) {
	int Len = p->Lenght;
	COORD* pos = &p->Position;
	for (int i = 0; i < Len; i++) {
		putBuffer((p->Position.X) + i, p->Position.Y, p->Format[i], p->Attribute);
	}
	// Direction arrow
	short Arrow;
	//if ((p->Direction.X != Space.Format) || (p->Direction.Y != Space.Format)) {
		p->Last_Direction = p->Direction;

		if ((p->Position.X) > (p->Last_position.X)) {
			p->Direction.X = p->Position.X + Len;
			p->Direction.Y = p->Position.Y;

			Arrow = RIGHT_ARROW_1;
		}
		else if ((p->Position.X) < (p->Last_position.X)) {
			p->Direction.X = p->Position.X - 1;
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
		else { return; }
		COORD pos_D = { p->Direction.X, p->Direction.Y };
		putBuffer(pos_D.X, pos_D.Y, Arrow, p->Attribute);
	//}
		keepObject(p, m);
}

