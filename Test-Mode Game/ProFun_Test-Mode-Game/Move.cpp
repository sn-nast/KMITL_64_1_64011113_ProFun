#include "Move.h"
#include "main.h"
#include "Buffer.h"

void playerMove(Player stPlayer) {
	Player* pt = &stPlayer;
	int Len = pt->Lenght;
	for (int i = 0; i < Len; i++) {
		putBuffer((pt->Position.X) + i, pt->Position.Y, pt->Format[i] , pt->Attribute);
	}
	// Direction arrow
	if (((pt->Position.X) != (pt->Last_position.X)) || ((pt->Position.Y) != (pt->Last_position.Y))){
		if ((pt->Position.X) > (pt->Last_position.X))		{ putBuffer((pt->Position.X) + Len	  , pt->Position.Y, RIGHT_ARROW_1, pt->Attribute); }
		else if ((pt->Position.X) < (pt->Last_position.X))	{ putBuffer((pt->Position.X) - Len / 2, pt->Position.Y, LEFT_ARROW_1, pt->Attribute); }
		else if ((pt->Position.Y) > (pt->Last_position.Y))	{ putBuffer((pt->Position.X) + Len / 2, pt->Position.Y + (pt->Height + 1), DOWN_ARROW_2, pt->Attribute); }
		else if ((pt->Position.Y) < (pt->Last_position.Y))	{ putBuffer((pt->Position.X) + Len / 2, pt->Position.Y - (pt->Height + 1), UP_ARROW_2, pt->Attribute); }
	} 
}