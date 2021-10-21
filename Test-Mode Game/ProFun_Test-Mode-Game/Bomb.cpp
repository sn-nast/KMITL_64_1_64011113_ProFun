#include"main.h"
#include"Buffer.h"
#include"Bomb.h"
#include"Object.h"

void setupBomb(Player* p) {
	int Amount = p->Bomb.Amount;
	int size = sizeof(p->Bomb.State) / sizeof(p->Bomb.State[0]);
	//p->Bomb.PowerX += p->Lenght / 2;
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

	// Check among bomb
	for (int i = 0; i < Drop; i++) {
		for (int c = 0; c < size; c++) {
			if (p->Bomb.State[c] == 0) {
				p->Bomb.State[c] = 1;
				p->Bomb.CountDn[c] = p->Bomb.Time;
				break;
			}
		}
	}

	// Check postion bomb 
	for (int c = 0; c < size; c++) {
		if (p->Bomb.State[c] == 1 ) {
			p->Bomb.Position[c].X = pos_P.X;
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
	int Len = p->Lenght;
	int Hei = p->Height;
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
			for (int H = 0; H < Hei; H++) {
				for (int L = 0; L < Len; L++) {
					m->State[pos_B.Y + H][pos_B.X + L] = Bomb_Nm.NormalState;
				}
			}
		}
	}
}

void showBomb(Player* p, Map* m) {
	int size = sizeof(p->Bomb.State) / sizeof(p->Bomb.State[0]);
	int Len = p->Lenght;
	int Hei = p->Height;
	for (int c = 0; c < size; c++) {
		COORD pos = { p->Bomb.Position[c].X, p->Bomb.Position[c].Y };
		if (p->Bomb.State[c] == 2) {
			for (int H = 0; H < Hei; H++) {
				for (int L = 0; L < Len; L++) {
					putBuffer(pos.X + L, pos.Y + H, Bomb_Nm.Format, Bomb_Nm.Attribute);
					m->LastState[pos.Y + H][pos.X + L] = m->State[pos.Y + H][pos.X + L];
					m->State[pos.Y + H][pos.X + L] = Bomb_Nm.NormalState;
				}
			}
		}
	}
}

void burstBomb(Player* p, int i, Map* m) {
	COORD pos = { p->Bomb.Position[i].X , p->Bomb.Position[i].Y };
	int pX = p->Bomb.PowerX;
	int pY = p->Bomb.PowerY;
	int Len = p->Lenght;
	int Hei = p->Height;

	for (int H = 0; H < Hei; H++) {
		// Left burst
		for (int c1 = 0; c1 >= -(pX * Len); c1--) {
			if (m->State[pos.Y + H][pos.X + c1] == CANt_DESTROY) { break; }
			putBuffer(pos.X + c1, pos.Y + H, Bomb_burst.Format, Bomb_burst.Attribute);
			//if (c1 == 0) { continue; }
			if (m->State[pos.Y + H][pos.X + c1] == CAN_DESTROY) {
				m->LastState[pos.Y + H][pos.X + c1] = m->State[pos.Y + H][pos.X + c1];
				m->State[pos.Y + H][pos.X + c1] = Bomb_burst.NormalState;
				p->Point += 100;
				if (H + 1 == Hei) { break; }
				//break;
			}
			m->LastState[pos.Y + H][pos.X + c1] = m->State[pos.Y + H][pos.X + c1];
			m->State[pos.Y + H][pos.X + c1] = Bomb_burst.NormalState;
		}
		// Right burst
		for (int c1 = Len; c1 < (pX * Len) + Len; c1++) {
			if (m->State[pos.Y + H][pos.X + c1] == CANt_DESTROY) { break; }
			putBuffer(pos.X + c1, pos.Y + H, Bomb_burst.Format, Bomb_burst.Attribute);
			// Check wall
			if (m->State[pos.Y + H][pos.X + c1] == CAN_DESTROY) {
				m->LastState[pos.Y + H][pos.X + c1] = m->State[pos.Y + H][pos.X + c1];
				m->State[pos.Y + H][pos.X + c1] = Bomb_burst.NormalState;
				p->Point += 100;
				if (H + 1 == Hei) { break; }
				//break;
			}
			m->LastState[pos.Y + H][pos.X + c1] = m->State[pos.Y + H][pos.X + c1];
			m->State[pos.Y + H][pos.X + c1] = Bomb_burst.NormalState;
			//}
		}
	}
	for (int L = 0; L < Len; L++) {
		// Up burst
		for (int c2 = -1; c2 >= -(pY * Hei); c2--) {
			if (m->State[pos.Y + c2][pos.X + L] == CANt_DESTROY) { break; }
			putBuffer(pos.X + L, pos.Y + c2, Bomb_burst.Format, Bomb_burst.Attribute);
			// Check wall
			if (m->State[pos.Y + c2][pos.X + L] == CAN_DESTROY) {
				m->LastState[pos.Y + c2][pos.X + L] = m->State[pos.Y + c2][pos.X + L];
				m->State[pos.Y + c2][pos.X + L] = Bomb_burst.NormalState;
				p->Point += 100;
				if (L + 1 != Len) { break; }
				//break;
			}
			m->LastState[pos.Y + c2][pos.X + L] = m->State[pos.Y + c2][pos.X + L];
			m->State[pos.Y + c2][pos.X + L] = Bomb_burst.NormalState;
		}
		// Down burst
		for (int c2 = Hei; c2 < (pY * Hei) + Hei; c2++) {
			if (m->State[pos.Y + c2][pos.X + L] == CANt_DESTROY) { break; }
			putBuffer(pos.X + L, pos.Y + c2, Bomb_burst.Format, Bomb_burst.Attribute);
			// Check wall
			if (m->State[pos.Y + c2][pos.X + L] == CAN_DESTROY) {
				m->LastState[pos.Y + c2][pos.X + L] = m->State[pos.Y + c2][pos.X + L];
				m->State[pos.Y + c2][pos.X + L] = Bomb_burst.NormalState;
				p->Point += 100;
				if (L + 1 == Len) { break; }
				//break;
			}
			m->LastState[pos.Y + c2][pos.X + L] = m->State[pos.Y + c2][pos.X + L];
			m->State[pos.Y + c2][pos.X + L] = Bomb_burst.NormalState;
		}
	}
	COORD posP = { p->Position.X , p->Position.Y };
	if (m->State[posP.Y][posP.X] == Bomb_burst.NormalState) { 
		//posP = {3, 1};
		p->Last_position = posP;
		p->Life--; 
	}
}