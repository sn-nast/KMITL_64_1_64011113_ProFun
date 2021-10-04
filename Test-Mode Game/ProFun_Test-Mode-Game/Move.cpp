#include "Move.h"
#include "main.h"
#include "Buffer.h"

void playerMove(Player stPlayer) {
	Player* pt = &stPlayer;
	int Len = pt->lenght;
	for (int i = 0; i < Len; i++) {
		putBuffer((pt->position.X) + i, pt->position.Y, pt->format[i] , pt->attribute);
	}
	// Direction arrow
	if (((pt->position.X) != (pt->last_position.X)) || ((pt->position.Y) != (pt->last_position.Y))){
		if ((pt->position.X) > (pt->last_position.X))		{ putBuffer((pt->position.X) + Len	  , pt->position.Y, RIGHT_ARROW_1, pt->attribute); }
		else if ((pt->position.X) < (pt->last_position.X))	{ putBuffer((pt->position.X) - Len / 2, pt->position.Y, LEFT_ARROW_1, pt->attribute); }
		else if ((pt->position.Y) > (pt->last_position.Y))	{ putBuffer((pt->position.X) + Len / 2, pt->position.Y + (pt->height + 1), DOWN_ARROW_2, pt->attribute); }
		else if ((pt->position.Y) < (pt->last_position.Y))	{ putBuffer((pt->position.X) + Len / 2, pt->position.Y - (pt->height + 1), UP_ARROW_2, pt->attribute); }
	} 
}