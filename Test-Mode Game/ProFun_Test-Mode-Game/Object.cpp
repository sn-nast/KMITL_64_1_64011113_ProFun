#include "Object.h"
#include "main.h"
#include "Map.h"

_Object
	Space = { ' ', NORMAL_ATTRIBUTE, MAP_SPACE, NO_POINT},
	Wall[10] = {
		{ '#', 9,	CAN_DESTROYED,	WALL_POINT },
		{ '|', 10,	CANt_DESTROYED,	NO_POINT},
		{ '&', 11,	CANt_DESTROYED,	NO_POINT },
		{ '$', 10,	CANt_DESTROYED,	NO_POINT },
		{ '+', 11,	CANt_DESTROYED,	NO_POINT },
		{ '%', 6,	CAN_DESTROYED,	WALL_POINT },
		{ '=', 8,	CAN_DESTROYED,	WALL_POINT },
		{ '*', 1,	CANt_DESTROYED,	NO_POINT},
		{ 'M', 12,  CAN_DESTROYED,  WALL_POINT},
		{ 'U', 8,	CAN_DESTROYED, WALL_POINT}
	},
	Bomb_Nm		= {'@', 7,	BOMB_SHOW,	NO_POINT},
	Bomb_burst	= {'X', 4,	BOMB_BURST,	NO_POINT },
	Life		= { 3, 6,	CAN_KEEP,	ITEM_POINT_NORMAL },
	Potion		= { 'P', 100, CAN_KEEP,	ITEM_POINT_NORMAL},
	newBomb		= { 15, 12, CAN_KEEP,	ITEM_POINT_NORMAL },
	Deathless	= { 4, 13, CAN_KEEP, ITEM_POINT_SPECIAL}
;

const int typeWall = sizeof(Wall) / sizeof(Wall[0]);

void dropObject(Map* m, COORD pos) {
	int* objRand = &m->ObjRand[pos.Y][pos.X];
	_Object* obj = &m->Object[pos.Y][pos.X];
	unsigned int* sta = &m->State[pos.Y][pos.X];
	m->LastState[pos.Y][pos.X] = *sta;
	int* time = &m->Time[pos.Y][pos.X];
	switch (*objRand % 5) {
		case 1: {
			*sta = Life.NormalState;
			*obj = { Life.Format, Life.Attribute, Life.NormalState };
			if (levelPlayer < 2)		{ *time = 60;}
			else if (levelPlayer >= 2)	{ *time = 15; }
			break; 
		}
		case 2: {
			*sta = Potion.NormalState;
			*obj = { Potion.Format, Potion.Attribute, Potion.NormalState }; 
			if (levelPlayer < 2) { *time = 60; }
			else if (levelPlayer >= 2) { *time = 30; }
			break;
		}
		case 3: {
			*sta = newBomb.NormalState;
			*obj = { newBomb.Format, newBomb.Attribute, newBomb.NormalState };
			if (levelPlayer < 2) { *time = 60; }
			else if (levelPlayer >= 2) { *time = 30; }
			break; 
		}
		case 4: {
			*sta = Deathless.NormalState;
			*obj = { Deathless.Format, Deathless.Attribute, Deathless.NormalState };
			if (levelPlayer < 2) { *time = 60; }
			else if (levelPlayer >= 2) { *time = 15; }
			break; 
		}
		default: {
				*sta = Space.NormalState;
				*obj = { Space.Format, Space.Attribute, Space.NormalState };
				*time = 0;
			break;
		}
	}
}

void keepObject(Player* p, Map* m) {
	unsigned int Len = p->Lenght;
	COORD* posP = &p->Position;
	COORD posOb = *posP;
	if (m->State[posOb.Y][posOb.X] == CAN_KEEP) {
		char Format = m->Object[posOb.Y][posOb.X].Format;
		if (Format == Life.Format) {
			p->Point += Life.Point;
			p->Life++;
		}
		else if (Format == Potion.Format) {
			p->Point += Potion.Point;
			p->Bomb.PowerX++;
			p->Bomb.PowerY++;
		}
		else if (Format == newBomb.Format) {
			p->Point += newBomb.Point;
			p->Bomb.Amount++;
		}
		else if (Format == Deathless.Format) {
			p->Point += Deathless.Point;
			p->DeathlessTime = 20;
		}
		int Len = p->Lenght;
		int Hei = p->Height;
		for (int H = 0; H < Hei; H++) {
			for (int L = 0; L < Len; L++) {
				removeObject(m, { (SHORT)(posOb.X + L), (SHORT)(posOb.Y + H)});
			}
		}
	}
}

void removeObject(Map* m, COORD pos) {
	m->State[pos.Y][pos.X] = Space.NormalState;
	m->Object[pos.Y][pos.X] = { Space.Format, Space.Attribute };
}

void countDownObject(Player* p) {
	if (timeChange == true && p->DeathlessTime > 0) {
		p->DeathlessTime--;
	}
}

void countDownObjectAllPlayer() {
	countDownObject(&playerMe);
	for (int n = 0; n < amountBot; n++) {
		countDownObject(&playerBot[n]);
	}
}

void checkCountDrop(Map* m, int* randNextObj, bool mainPlayer) {
	int checkRandObj = *randNextObj % 5;
	bool mustNewStatus = false;
	int countMustChange = 0;
	struct _Obj {
		bool mustNewObj = false;
		int numRand = 0;
		unsigned int maxDrop = 0;
		unsigned int refCheck = 0;
	};
	_Obj Obj[4];
	Obj[0] = { false, 1 , 3, m->CountDrop_Life };
	Obj[1] = { false, 2 , 15, m->CountDrop_Potion };
	Obj[2] = { false, 3 , 12, m->CountDrop_newBomb };
	Obj[3] = { false, 4 , 15, m->CountDrop_Deathless};

	int amountObject = sizeof(Obj) / sizeof(Obj[0]);
	for (int n = 0; n < amountObject; n++) {
		if (Obj[n].refCheck >= Obj[n].maxDrop) { 
			Obj[n].mustNewObj = true; 
			mustNewStatus = true;
		}
	}
	// Life drop
	if (mainPlayer == true) {
		if (levelPlayer == 1) {
			if ((playerMe.Point > 10000 && Obj[0].refCheck < 1) ||
				(m->GameTime_Minute == 3 && Obj[0].refCheck < 2)) {
				Obj[0].mustNewObj = false;
			}
			else {
				Obj[0].mustNewObj = true;
				mustNewStatus = true;
			}
		}
		else if (levelPlayer == 2) {
			if ((playerMe.Point > 25000 && Obj[0].refCheck < 1) ||
				(m->GameTime_Minute == 3 && Obj[0].refCheck < 2)) {
				Obj[0].mustNewObj = false;
			}
			else {
				Obj[0].mustNewObj = true;
				mustNewStatus = true;
			}
		}
		else if (m->GameTime_Minute == 2 && m->GameTime_Second < 15) {
			Obj[0].mustNewObj = false;
		}
	}
	else {
		Obj[0].mustNewObj = true;
		mustNewStatus = true;
	}

	if (levelPlayer == 1) {
		for (int n = 5; n > 0; n--) {
			if (m->GameTime_Minute == n & m->GameTime_Second < 20	&&
				Obj[3].refCheck < n * 5	) {
				Obj[3].mustNewObj = false;
				break;
			}
			else {
				Obj[3].mustNewObj = true;
				mustNewStatus = true;
			}
		}
	}
	else if (levelPlayer == 2) {
		for (int n = 5; n > 0; n--) {
			if (m->GameTime_Minute == n & m->GameTime_Second < 20 &&
				Obj[3].refCheck < n * 3) {
				Obj[3].mustNewObj = false;
				break;
			}
			else {
				Obj[3].mustNewObj = true;
				mustNewStatus = true;
			}
		}
	}

	for (int n = 0; n < amountObject; n++) {
		if (Obj[n].mustNewObj == true) {
			countMustChange++;
		}
	}

	while (mustNewStatus) {
		checkRandObj = rand() % 5;
		int countCheck = 0;
		for (int n = 0; n < amountObject; n++) {
			if (Obj[n].mustNewObj == true && checkRandObj != Obj[n].numRand) {
				countCheck++;
			}
		}
		if (countCheck == countMustChange) { mustNewStatus = false; }
	}
	if (checkRandObj == 1) {
		int n = 0; 
	}
	*randNextObj = checkRandObj;
}