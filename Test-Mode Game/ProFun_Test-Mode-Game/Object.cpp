#include "Object.h"
#include "main.h"
#include "Map.h"

void dropObject(Map* m, COORD pos) {
	int objRand = rand() % 5;
	_Object* obj = &m->Object[pos.Y][pos.X];
	unsigned int* sta = &m->State[pos.Y][pos.X];
	switch (objRand)
	{
	case 1: {
		*sta = Life.NormalState;
		*obj = { Life.Format, Life.Attribute, Life.NormalState };
		break; 
	}
	case 2: {
		*sta = Potion.NormalState;
		*obj = { Potion.Format, Potion.Attribute, Potion.NormalState }; 
		break; 
	}
	//case 3: {
	//	*sta = Life.NormalState;
	//	*obj = { Life.Format, Life.Attribute, Life.NormalState };
	//	break; }
	//case 4: {
	//	*sta = Life.NormalState;
	//	*obj = { Life.Format, Life.Attribute, Life.NormalState };
	//	break; }
	default: {
			*sta = Space.NormalState;
			*obj = { Space.Format, Space.Attribute, Space.NormalState };
		break;
	}
	}
}