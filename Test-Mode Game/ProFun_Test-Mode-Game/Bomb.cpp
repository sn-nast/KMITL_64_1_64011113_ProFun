#include"main.h"
#include"Buffer.h"
#include"Bomb.h"
#include"Object.h"

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
	//COORD pos_D = { p->Direction.X, p->Direction.Y };
	//COORD posL_D = p->Last_Direction;

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
			//showBomb(pos_B);
		}
	}
}

void showBomb(Player* p) {
	int size = sizeof(p->Bomb.State) / sizeof(p->Bomb.State[0]);
	for (int c = 0; c < size; c++) {
		COORD pos = { p->Bomb.Position[c].X,p->Bomb.Position[c].Y };
		if (p->Bomb.State[c] == 2) {
			putBuffer(pos.X, pos.Y, Bomb_Nm.Format, Bomb_Nm.Attribute);
		}
	}
}

void showBomb(COORD pos) {
	putBuffer(pos.X, pos.Y, Bomb_Nm.Format , Bomb_Nm.Attribute);
}

void burstBomb(Player* p, int i, Map* m) {
	COORD pos = { p->Bomb.Position[i].X , p->Bomb.Position[i].Y };
	int c = p->Bomb.Power;
	for (int c1 = 0; c1 >= -c; c1--) {
		if (m->State[pos.Y][pos.X + c1] == Wall_2.NormalState) { break; }
		putBuffer(pos.X + c1, pos.Y, Bomb_burst.Format, Bomb_burst.Attribute);
		m->LastState[pos.Y][pos.X + c1] = m->State[pos.Y][pos.X + c1];
		m->State[pos.Y][pos.X + c1] = Bomb_burst.NormalState;
		//dropObject(m, { (SHORT)(pos.X + c1), pos.Y });
		//m->Object[pos.Y][pos.X + c1] = { Space.Format, Space.Attribute };
	}
	for (int c1 = 1; c1 <= c; c1++) {
		if (m->State[pos.Y][pos.X + c1] == Wall_2.NormalState) { break; }
		putBuffer(pos.X + c1, pos.Y, Bomb_burst.Format, Bomb_burst.Attribute);
		m->LastState[pos.Y][pos.X + c1] = m->State[pos.Y][pos.X + c1];
		m->State[pos.Y][pos.X + c1] = Bomb_burst.NormalState;
	}
	for (int c2 = -1; c2 >= -c; c2--) {
		if (m->State[pos.Y + c2][pos.X] == Wall_2.NormalState) { break; }
		putBuffer(pos.X, pos.Y + c2, Bomb_burst.Format, Bomb_burst.Attribute);
		m->LastState[pos.Y + c2][pos.X] = m->State[pos.Y + c2][pos.X];
		m->State[pos.Y + c2][pos.X] = Bomb_burst.NormalState;
	}
	for (int c2 = 1; c2 <= c; c2++) {
		if (m->State[pos.Y + c2][pos.X] == Wall_2.NormalState) { break; }
		putBuffer(pos.X, pos.Y + c2, Bomb_burst.Format, Bomb_burst.Attribute);
		m->LastState[pos.Y + c2][pos.X] = m->State[pos.Y + c2][pos.X];
		m->State[pos.Y + c2][pos.X] = Bomb_burst.NormalState;
	}
	int Len = p->Lenght;
	if (m->State[p->Position.Y][p->Position.X + Len / 2] == Bomb_burst.NormalState) { p->Life--; return; }
}