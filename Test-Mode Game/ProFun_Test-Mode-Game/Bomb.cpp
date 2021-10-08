#include"main.h"
#include"Buffer.h"
#include"Bomb.h"
#include<stdio.h>

void setupBomb(Player* p) {
	int Amount = p->Bomb.Amount;
	int size = sizeof(p->Bomb.State) / sizeof(p->Bomb.State[0]);
	for (int i = 0; i < size; i++) {
		p->Bomb.State[i] = 0;
		p->Bomb.CountDn[i] = p->Bomb.Time;
	}
}

void dropBomb(Player* p, Map* m) {
	COORD pos_P = p->Position;
	COORD posL_P = p->Last_position;
	COORD pos_D = { p->Direction.X, p->Direction.Y };
	COORD posL_D = p->Last_Direction;

	int Drop = p->Bomb.Drop;
	int Len = p->Lenght;
	int Hei = p->Height;
	int size = sizeof(p->Bomb.State) / sizeof(p->Bomb.State[0]);

	for (int i = 0; i < Drop; i++) {
		for (int c = 0; c < size; c++) {
			if (p->Bomb.State[c] == 0) {
				p->Bomb.State[c] = 1;
				p->Bomb.CountDn[c] = p->Bomb.Time;
				break;
			}
		}
	}

	for (int c = 0; c < size; c++) {
		if (p->Bomb.State[c] == 1 /*&& (posL_D.X != pos_D.X || posL_D.Y != pos_D.Y)*/) {
			p->Bomb.Position[c].X = pos_D.X;
			p->Bomb.Position[c].Y = pos_D.Y;
			COORD pos_B = { p->Bomb.Position[c].X, p->Bomb.Position[c].Y };
			p->Bomb.State[c] = 2;
			p->Bomb.Drop--;
			break;
		}
	}
}

void checkBomb(Player* p, Map* m) {
	int size = sizeof(p->Bomb.State) / sizeof(p->Bomb.State[0]);
	for (int c = 0; c < size; c++) {
		COORD pos_B = { p->Bomb.Position[c].X, p->Bomb.Position[c].Y };
		if (p->Bomb.State[c] == 2) {
			if (p->Bomb.CountDn[c] == 0) {
				p->Bomb.State[c] = 0;
				p->Bomb.CountDn[c] = p->Bomb.Time;
				burstBomb(*p, c, m);
				continue;
			}
			p->Bomb.CountDn[c]--;
			showBomb(pos_B, NORMAL_BOMB);
		}
	}
}

void showBomb(Player* p) {
	int size = sizeof(p->Bomb.State) / sizeof(p->Bomb.State[0]);
	for (int c = 0; c < size; c++) {
		COORD pos = { p->Bomb.Position[c].X,p->Bomb.Position[c].Y };
		if (p->Bomb.State[c] == 2) {
			putBuffer(pos.X, pos.Y, NORMAL_BOMB, NORMAL_ATTIBUTE);
		}
	}
}
void showBomb(COORD pos, char bomb) {
	putBuffer(pos.X, pos.Y, bomb, NORMAL_ATTIBUTE);
}

void burstBomb(Player S, int i, Map* m) {
	COORD pos = { S.Bomb.Position[i].X , S.Bomb.Position[i].Y };
	int c = S.Bomb.Power;
	for (int c1 = -c; c1 <= c; c1++) {
		putBuffer(pos.X + c1, pos.Y, 'X', NORMAL_ATTIBUTE);
		m->State[pos.Y][pos.X + c1] = NOW_BOMB;
	}
	for (int c2 = -c; c2 <= c; c2++) {
		putBuffer(pos.X, pos.Y + c2, 'X', NORMAL_ATTIBUTE);
		m->State[pos.Y + c2][pos.X] = NOW_BOMB;
		m->Object[pos.Y + c2][pos.X] = { Space.Format, Space.Attribute };
	}
}