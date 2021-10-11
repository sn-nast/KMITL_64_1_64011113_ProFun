#include"main.h"
#include"Buffer.h"
#include"Bomb.h"
#include"Object.h"

void setupBomb(Player* p) {
	int Amount = p->Bomb.Amount;
	int size = sizeof(p->Bomb.State) / sizeof(p->Bomb.State[0]);
	p->Bomb.PowerX += p->Lenght / 2;
	for (int i = 0; i < size; i++) {
		p->Bomb.State[i] = 0;
		p->Bomb.CountDn[i] = p->Bomb.Time;
	}
}

void setOfBomb(Player* p, Map* m) {
	dropBomb(p, m);
	showBomb(p, m);
	checkBomb(p, m);
}

void dropBomb(Player* p, Map* m) {
	COORD pos_P = p->Position;
	COORD posL_P = p->Last_position;

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
		if (p->Bomb.State[c] == 1 ) {
			p->Bomb.Position[c].X = pos_P.X + Len / 2;
			p->Bomb.Position[c].Y = pos_P.Y;
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
				burstBomb(p, c, m);
				continue;
			}
			p->Bomb.CountDn[c]--;
			m->State[pos_B.Y][pos_B.X] = Bomb_Nm.NormalState;
		}
	}
}

void showBomb(Player* p, Map* m) {
	int size = sizeof(p->Bomb.State) / sizeof(p->Bomb.State[0]);
	for (int c = 0; c < size; c++) {
		COORD pos = { p->Bomb.Position[c].X,p->Bomb.Position[c].Y };
		if (p->Bomb.State[c] == 2) {
			putBuffer(pos.X, pos.Y, Bomb_Nm.Format, Bomb_Nm.Attribute);
			m->LastState[pos.Y][pos.X] = m->State[pos.Y][pos.X];
			m->State[pos.Y][pos.X] = Bomb_Nm.NormalState;
		}
	}
}

void burstBomb(Player* p, int i, Map* m) {
	COORD pos = { p->Bomb.Position[i].X , p->Bomb.Position[i].Y };
	int cX = p->Bomb.PowerX;
	int cY = p->Bomb.PowerY;
	int Len = p->Lenght;
	for (int c1 = Len / 2; c1 >= -cX; c1--) {
		if (m->State[pos.Y][pos.X + c1] == CANt_DESTROY) { break; }
		putBuffer(pos.X + c1, pos.Y, Bomb_burst.Format, Bomb_burst.Attribute);
		if (c1 >= 0) { continue; }
		m->LastState[pos.Y][pos.X + c1] = m->State[pos.Y][pos.X + c1];
		m->State[pos.Y][pos.X + c1] = Bomb_burst.NormalState;
	}
	for (int c1 = Len / 2; c1 <= cX; c1++) {
		if (m->State[pos.Y][pos.X + c1] == CANt_DESTROY) { break; }
		putBuffer(pos.X + c1, pos.Y, Bomb_burst.Format, Bomb_burst.Attribute);
		if (c1 < Len - 1) { continue; }
		m->LastState[pos.Y][pos.X + c1] = m->State[pos.Y][pos.X + c1];
		m->State[pos.Y][pos.X + c1] = Bomb_burst.NormalState;
	}
	for (int c2 = -1; c2 >= -cY; c2--) {
		if (m->State[pos.Y + c2][pos.X] == CANt_DESTROY) { break; }
		putBuffer(pos.X, pos.Y + c2, Bomb_burst.Format, Bomb_burst.Attribute);
		m->LastState[pos.Y + c2][pos.X] = m->State[pos.Y + c2][pos.X];
		m->State[pos.Y + c2][pos.X] = Bomb_burst.NormalState;
	}
	for (int c2 = 1; c2 <= cY; c2++) {
		if (m->State[pos.Y + c2][pos.X] == CANt_DESTROY) { break; }
		putBuffer(pos.X, pos.Y + c2, Bomb_burst.Format, Bomb_burst.Attribute);
		m->LastState[pos.Y + c2][pos.X] = m->State[pos.Y + c2][pos.X];
		m->State[pos.Y + c2][pos.X] = Bomb_burst.NormalState;
	}
	COORD posP = { p->Position.X , p->Position.Y };
	if (m->State[posP.Y][posP.X + Len / 2] == Bomb_burst.NormalState) { p->Life--; }
}