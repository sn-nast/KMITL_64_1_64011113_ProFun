#include"main.h"
#include"Buffer.h"
#include"Bomb.h"
#include"Object.h"

void setupBomb(Player* p) {
	int Amount = p->Bomb.Amount;
	int size = sizeof(p->Bomb.State) / sizeof(p->Bomb.State[0]);
	p->Bomb.Amount = 1;
	p->Bomb.NewDrop = 0;
	p->Bomb.Time = 20;
	p->Bomb.PowerX = 1;
	p->Bomb.PowerY = 1;
	p->Bomb.CountBombDropNow = 0;
	for (int i = 0; i < size; i++) {
		p->Bomb.State[i] = 0;
		p->Bomb.CountDn[i] = p->Bomb.Time;
	}
}

void setOfBomb(Player* p, Map* m) {
	dropBomb(p, m);
	showBomb(p, m);
	statusBomb(p, m);
}

void dropBomb(Player* p, Map* m) {
	COORD pos_P = p->Position;
	COORD posL_P = p->Last_Position;

	int Drop = p->Bomb.NewDrop;
	int Len = p->Lenght;
	int Hei = p->Height;
	int size = sizeof(p->Bomb.State) / sizeof(p->Bomb.State[0]);

	// Check amonunt bomb
	for (int i = 0; i < Drop; i++) {
		for (int c = 0; c < size; c++) {
			if (p->Bomb.State[c] == BOMB_CAN_PUT) {
				p->Bomb.State[c] = BOMB_ALREADY_PUT;
				p->Bomb.CountDn[c] = p->Bomb.Time;
				break;
			}
		}
	}

	// Check postion bomb 
	for (int c = 0; c < size; c++) {
		if (p->Bomb.State[c] == BOMB_ALREADY_PUT) {
			p->Bomb.Position[c].X = pos_P.X;
			p->Bomb.Position[c].Y = pos_P.Y;
			p->Bomb.State[c] = BOMB_COUNTING;
			p->Bomb.NewDrop--;
			p->Bomb.CountBombDropNow++;
			break;
		}
	}
}

void statusBomb(Player* p, Map* m) {
	int size = sizeof(p->Bomb.State) / sizeof(p->Bomb.State[0]);
	int Len = p->Lenght;
	int Hei = p->Height;
	for (int c = 0; c < size; c++) {
		COORD pos_B = { p->Bomb.Position[c].X, p->Bomb.Position[c].Y };
		if (p->Bomb.State[c] == BOMB_COUNTING) {
			if (p->Bomb.CountDn[c] == 0) {
				p->Bomb.State[c] = BOMB_CAN_PUT;
				p->Bomb.CountDn[c] = p->Bomb.Time;
				burstBomb(p, c, m);
				p->Bomb.CountBombDropNow--;
				continue;
			}
			p->Bomb.CountDn[c]--;
			for (int H = 0; H < Hei; H++) {
				for (int L = 0; L < Len; L++) {
					// Change state map
					m->LastState[pos_B.Y + H][pos_B.X + L] = m->State[pos_B.Y + H][pos_B.X + L];
					m->State[pos_B.Y + H][pos_B.X + L] = Bomb_Nm.NormalState;
					m->OwnerBomb[pos_B.Y + H][pos_B.X + L] = p->Call;
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
	int pX = p->Bomb.PowerX, pY = p->Bomb.PowerY;
	int Len = p->Lenght, Hei = p->Height;
	int countWallDetroyed = 0;
	int nextObj[4] = { 0, 0, 0, 0 };
	int countNextObj[4] = {0, 0, 0, 0};
	// rand obj each direction
	for (int i = 0; i < sizeof(nextObj)/sizeof(nextObj[0]); i++) {
		nextObj[i] = rand();
		bool mainPlayer = false;
		if (p->Call == playerMe.Call) {
			mainPlayer = true;
		}
		checkCountDrop(m, &nextObj[i], mainPlayer);
	}

	// Burst
	for (int H = 0; H < Hei; H++) {
		// Left burst
		int count1 = 0;
		// include middle burst (start from Len)
		for (int c1 = Len - 1; c1 >= -(pX * Len); c1--) {
			// Check wall can destroyed
			if (m->State[pos.Y + H][pos.X + c1] == CANt_DESTROYED) { break; }
			putBuffer(pos.X + c1, pos.Y + H, Bomb_burst.Format, Bomb_burst.Attribute);
			// Change state map
			m->LastState[pos.Y + H][pos.X + c1] = m->State[pos.Y + H][pos.X + c1];
			m->State[pos.Y + H][pos.X + c1] = Bomb_burst.NormalState;
			m->OwnerBomb[pos.Y + H][pos.X + c1] = p->Call;

			if (m->LastState[pos.Y + H][pos.X + c1] == CAN_DESTROYED) {
				countWallDetroyed++;
				count1++;
				m->ObjRand[pos.Y + H][pos.X + c1] = nextObj[0];
				countNextObj[0]++;
				if (count1 == Len) { break; }
			}
		}
		// Right burst
		int count2 = 0;
		for (int c1 = Len; c1 < (pX * Len) + Len; c1++) {
			// Check wall can destroyed
			if (m->State[pos.Y + H][pos.X + c1] == CANt_DESTROYED) { break; }
			putBuffer(pos.X + c1, pos.Y + H, Bomb_burst.Format, Bomb_burst.Attribute);
			// Change state map
			m->LastState[pos.Y + H][pos.X + c1] = m->State[pos.Y + H][pos.X + c1];
			m->State[pos.Y + H][pos.X + c1] = Bomb_burst.NormalState;
			m->OwnerBomb[pos.Y + H][pos.X + c1] = p->Call;

			if (m->LastState[pos.Y + H][pos.X + c1] == CAN_DESTROYED) {
				countWallDetroyed++;
				count2++;
				m->ObjRand[pos.Y + H][pos.X + c1] = nextObj[1];
				countNextObj[1]++;
				if (count2 == Len) { break; }
			}
		}
	}

	for (int L = 0; L < Len; L++) {
		// Up burst
		int count1 = 0;
		for (int c2 = -1; c2 >= -(pY * Hei); c2--) {
			// Check wall can destroyed
			if (m->State[pos.Y + c2][pos.X + L] == CANt_DESTROYED) { break; }
			putBuffer(pos.X + L, pos.Y + c2, Bomb_burst.Format, Bomb_burst.Attribute);
			// Change state map
			m->LastState[pos.Y + c2][pos.X + L] = m->State[pos.Y + c2][pos.X + L];
			m->State[pos.Y + c2][pos.X + L] = Bomb_burst.NormalState;
			m->OwnerBomb[pos.Y + c2][pos.X + L] = p->Call;

			if (m->LastState[pos.Y + c2][pos.X + L] == CAN_DESTROYED) {
				countWallDetroyed++;
				count1++;
				m->ObjRand[pos.Y + c2][pos.X + L] = nextObj[2];
				countNextObj[2]++;
				if (count1 == Hei) { break; }
			}
		}
		// Down burst
		int count2 = 0;
		for (int c2 = Hei; c2 < (pY * Hei) + Hei; c2++) {
			// Check wall can destroyed
			if (m->State[pos.Y + c2][pos.X + L] == CANt_DESTROYED) { break; }
			putBuffer(pos.X + L, pos.Y + c2, Bomb_burst.Format, Bomb_burst.Attribute);
			// Change state map
			m->LastState[pos.Y + c2][pos.X + L] = m->State[pos.Y + c2][pos.X + L];
			m->State[pos.Y + c2][pos.X + L] = Bomb_burst.NormalState;
			m->OwnerBomb[pos.Y + c2][pos.X + L] = p->Call;

			if (m->LastState[pos.Y + c2][pos.X + L] == CAN_DESTROYED) {
				countWallDetroyed++;
				count2++;
				m->ObjRand[pos.Y + c2][pos.X + L] = nextObj[3];
				countNextObj[3]++;
				if (count2 == Hei) { break; }
			}
		}
	}
	p->Point += (countWallDetroyed / (Len * Hei)) * WALL_POINT;
	for (int n = 0; n < 4; n++) {
		int checkRand = nextObj[n] % 5;
		if (checkRand == 1) {
			m->CountDrop_Life += (countNextObj[n] / (Len * Hei));
		}
		else if (checkRand == 2) {
			m->CountDrop_Potion += (countNextObj[n] / (Len * Hei));
		}
		else if (checkRand == 3) {
			m->CountDrop_newBomb += (countNextObj[n] / (Len * Hei));
		}
		else if (checkRand == 4) {
			m->CountDrop_Deathless += (countNextObj[n] / (Len * Hei));
		}
	}
}

void checkBomb(Player* p, Map* m) {
	// Check maximum bomb power (for bot moving)
	if (p->Bomb.PowerX > m->maxBombPowerX) { m->maxBombPowerX = p->Bomb.PowerX; }
	if (p->Bomb.PowerY > m->maxBombPowerY) { m->maxBombPowerY = p->Bomb.PowerY; }

	// Check Life and Burst
	COORD* posP = &p->Position;
	if (m->State[posP->Y][posP->X] == Bomb_burst.NormalState) {
		bool reLife = false;
		if (p->DeathlessTime == 0) { 
			p->Last_Position = *posP;
			reLife = true;
			p->Life--; 
		}
		else { p->DeathlessTime = 0; }
		if (p->Life == 0) {
			p->Bot.Alive = false;
		}

		// Check owner bomb
		unsigned int* mOwner = &m->OwnerBomb[posP->Y][posP->X];
		if (*mOwner != p->Call) {
			if (*mOwner == playerMe.Call) { playerMe.Point += KILL_POINT; }
			else if (*mOwner == playerBot[0].Call) { playerBot[0].Point += KILL_POINT; }
			else if (*mOwner == playerBot[1].Call) { playerBot[1].Point += KILL_POINT; }
			else if (*mOwner == playerBot[2].Call) { playerBot[2].Point += KILL_POINT; }
		}
			if (reLife == true) { *posP = p->StartPositon; }
	}
}