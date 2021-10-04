#include"main.h"
#include"Buffer.h"
#include"Bomb.h"
#include<stdio.h>
void setupBomb(Player *p) {
	int Amount = p->Bomb.Amount;
	int size = sizeof(p->Bomb.State) / sizeof(p->Bomb.State[0]);
	for (int i = 0; i < size; i++) {
		p->Bomb.State[i] = 0;
		p->Bomb.CountDn[i] = p->Bomb.Time;
	}
}

void dropBomb(Player* p) {
	COORD pos_P = p->Position;
	COORD posL_P = p->Last_position;
	int Drop = p->Bomb.Drop;
	int Len = p->Lenght;
	int Hei = p->Height;
	int remain = Drop;
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
		//short addX = 0, addY = 0;
		if (p->Bomb.State[c] == 1 && p->Bomb.CountDn[c] == p->Bomb.Time) {
			if (pos_P.X > posL_P.X) {
				p->Bomb.Position[c].X = pos_P.X + Len;
				p->Bomb.Position[c].Y = pos_P.Y;
			}
			else if (pos_P.X < posL_P.X) {
				p->Bomb.Position[c].X = pos_P.X - Len / 2;
				p->Bomb.Position[c].Y = pos_P.Y;
			}
			else if (pos_P.Y > posL_P.Y) {
				p->Bomb.Position[c].X = pos_P.X + Len / 2;
				p->Bomb.Position[c].Y = pos_P.Y + (Hei + 1);
			}
			else if (pos_P.Y < posL_P.Y) {
				p->Bomb.Position[c].X = pos_P.X + Len / 2;
				p->Bomb.Position[c].Y = pos_P.Y - (Hei + 1);
			}
			p->Bomb.Drop--;
			COORD pos_B = { p->Bomb.Position[c].X, p->Bomb.Position[c].Y };
			putBuffer(pos_B.X, pos_B.Y, NORMAL_BOMB, NORMAL_ATTIBUTE);
			p->Bomb.CountDn[c]--;
			break;
		}
	}
}

void checkBomb(Player *p) {
	int size = sizeof(p->Bomb.State) / sizeof(p->Bomb.State[0]);
	for (int c = 0; c < size; c++) {
		COORD pos_B = { p->Bomb.Position[c].X, p->Bomb.Position[c].Y };
		if (p->Bomb.State[c] == 1 && p->Bomb.CountDn[c] != p->Bomb.Time) {
			if (p->Bomb.CountDn[c] == 0) {
				p->Bomb.State[c] = 0;
				p->Bomb.Amount++;
				putBuffer(pos_B.X, pos_B.Y, ' ', NORMAL_ATTIBUTE);
				break;
			}
			p->Bomb.CountDn[c]--;
			putBuffer(pos_B.X, pos_B.Y, NORMAL_BOMB, NORMAL_ATTIBUTE);
		}
	}
}