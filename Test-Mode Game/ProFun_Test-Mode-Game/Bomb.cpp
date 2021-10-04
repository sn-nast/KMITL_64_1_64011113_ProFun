#include"main.h"
#include"Buffer.h"
void setupBomb(Player stPlayer) {
	Player* p = &stPlayer;
	int Amount = p->Bomb.Amount;
	for (int i = 0; i < Amount && Amount < 15; i++) {
		p->Bomb.State[i] = 0;
		p->Bomb.CoundDn[i] = p->Bomb.Time;
	}
}

void dropBomb(Player stPlayer) {
	Player* p = &stPlayer;
	COORD pos_P = p->Position;	
	COORD posL_P = p->Last_position;
	int Drop = p->Bomb.Drop;
	int Len = p->Lenght;
	int Hei = p->Height;
	int remain = Drop;

	// อยากแทนถัดจาก ลูกศร ใช้ addX, addY
	for (int i = 0; i < Drop; i++) {
		//short addX = 0, addY = 0;
		if(pos_P.X > posL_P.X) { 
			p->Bomb.Position.X = pos_P.X + Len ;
			p->Bomb.Position.Y = pos_P.Y;
		} 
		else if (pos_P.X < posL_P.X) { 
			p->Bomb.Position.X = pos_P.X - Len / 2;
			p->Bomb.Position.Y = pos_P.Y;
		}
		else if (pos_P.Y > posL_P.Y) { 
			p->Bomb.Position.X = pos_P.X + Len / 2;
			p->Bomb.Position.Y = pos_P.Y + (Hei + 1);
		}
		else if (pos_P.Y < posL_P.Y) {
			p->Bomb.Position.X = pos_P.X + Len / 2;
			p->Bomb.Position.Y = pos_P.Y - (Hei + 1);
		}
		COORD pos_B = { p->Bomb.Position.X, p->Bomb.Position.Y };
		putBuffer(pos_B.X, pos_B.Y, NORMAL_BOMB, NORMAL_ATTIBUTE);
		remain--;
		p->Bomb.Drop = remain;
		for (int c = 0; c < sizeof(p->Bomb.State); c++) {
			if (p->Bomb.State[c] == 0) {
				p->Bomb.State[c] = 1;
				p->Bomb.CoundDn[c] = p->Bomb.Time;
			}
		}
	}
}

void checkBomb(Player stPlayer) {
	Player* p = &stPlayer;
	COORD pos_B = { p->Bomb.Position.X, p->Bomb.Position.Y };
	for (int c = 0; c < sizeof(p->Bomb.State); c++) {
		if (p->Bomb.State[c] == 1) {
			if (p->Bomb.CoundDn[c] == 0) {
				p->Bomb.State[c] = 0;
				p->Bomb.Amount++;
				putBuffer(pos_B.X, pos_B.Y, ' ', NORMAL_ATTIBUTE);
				break;
			}
			p->Bomb.CoundDn[c]--;
			putBuffer(pos_B.X, pos_B.Y, NORMAL_BOMB, NORMAL_ATTIBUTE);
		}
	}
}