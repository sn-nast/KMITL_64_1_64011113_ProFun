#include "Map.h"
#include "main.h"
#include "Buffer.h"
#include "Object.h"

void setupMap(Map* m, int n_map) {
	for (short pY = 0; pY < MAP_HEIGHT; pY++) {
		for (short pX = 0; pX < MAP_WIDTH; pX++) {
			_Object* Ob = &m->Object[pY][pX];
			Ob->Format = planMap(n_map, { pX, pY });
			if (Ob->Format == Space.Format){
				Ob->Attribute = Space.Attribute;
				m->State[pY][pX] = Space.NormalState;
			}
			for (int i = 0; i < typeWall; i++) {
				if (Ob->Format == Wall[i].Format) {
					Ob->Attribute = Wall[i].Attribute;
					m->State[pY][pX] = Wall[i].NormalState;
					break;
				}
			}
			putBuffer(pX, pY, Ob->Format, Ob->Attribute);
		}
	}
}

char planMap(int n, COORD pos) {
	if (n == 1) {
		char map[MAP_HEIGHT][MAP_WIDTH] = {
			{"|||||||||||||||||||||||||||||||||||||||||||||||||"},
			{"||      %%%   %%%======      MMM%%%   ===      ||"},
			{"||      %%%   %%%======      MMM%%%   ===      ||"},
			{"||      %%%   %%%======      MMM%%%   ===      ||"},
			{"||   +++   +++$$$   +++   +++MMM$$$$$$MMM$$$   ||"},
			{"||   +++   +++$$$   +++   +++MMM$$$$$$MMM$$$   ||"},
			{"||   +++   +++$$$   +++   +++MMM$$$$$$MMM$$$   ||"},
			{"||MMM$$$      %%%   MMMMMM   MMM      MMM+++%%%||"},
			{"||MMM$$$      %%%   MMMMMM   MMM      MMM+++%%%||"},
			{"||MMM$$$      %%%   MMMMMM   MMM      MMM+++%%%||"},
			{"||===$$$+++   +++   $$$+++$$$%%%$$$   ++++++===||"},
			{"||===$$$+++   +++   $$$+++$$$%%%$$$   ++++++===||"},
			{"||===$$$+++   +++   $$$+++$$$%%%$$$   ++++++===||"},
			{"||   MMM===MMM         ===            MMM      ||"},
			{"||   MMM===MMM         ===            MMM      ||"},
			{"||   MMM===MMM         ===            MMM      ||"},
			{"||%%%++++++MMM+++   %%%   %%%%%%+++   $$$+++   ||"},
			{"||%%%++++++MMM+++   %%%   %%%%%%+++   $$$+++   ||"},
			{"||%%%++++++MMM+++   %%%   %%%%%%+++   $$$+++   ||"},
			{"||%%%   MMM======MMM|||||||||MMM%%%MMM      MMM||"},
			{"||%%%   MMM======MMM|$$$$   |MMM%%%MMM      MMM||"},
			{"||%%%   MMM======MMM|$$$$   |MMM%%%MMM      MMM||"},
			{"||MMM&&&&&&   $$$   |   $$$$|   $$$===++++++%%%||"},
			{"||MMM&&&&&&   $$$   |   $$$$|   $$$===++++++%%%||"},
			{"||MMM&&&&&&   $$$   |||||||||   $$$===++++++%%%||"},
			{"||%%%   %%%%%%      %%%===         MMM      ===||"},
			{"||%%%   %%%%%%      %%%===         MMM      ===||"},
			{"||%%%   %%%%%%      %%%===         MMM      ===||"},
			{"||MMM++++++   $$$   $$$$$$$$$   $$$   $$$+++   ||"},
			{"||MMM++++++   $$$   $$$$$$$$$   $$$   $$$+++   ||"},
			{"||MMM++++++   $$$   $$$$$$$$$   $$$   $$$+++   ||"},
			{"||%%%+++      ===MMMMMM   ===            $$$   ||"},
			{"||%%%+++      ===MMMMMM   ===            $$$   ||"},
			{"||%%%+++      ===MMMMMM   ===            $$$   ||"},
			{"||   +++   $$$+++   +++   +++   $$$+++===+++   ||"},
			{"||   +++   $$$+++   +++   +++   $$$+++===+++   ||"},
			{"||   +++   $$$+++   +++   +++   $$$+++===+++   ||"},
			{"||         ======%%%===   ===MMM===   ===      ||"},
			{"||         ======%%%===   ===MMM===   ===      ||"},
			{"||         ======%%%===   ===MMM===   ===      ||"},
			{"|||||||||||||||||||||||||||||||||||||||||||||||||"}
		};
		return map[pos.Y][pos.X];
	}
	else if (n == 2) {
		char map[MAP_HEIGHT][MAP_WIDTH] = {
			{"|||||||||||||||||||||||||||||||||||||||||||||||||"},
			{"||         ###   &&&   $$$   $$$   ###         ||"},
			{"||         ###   &&&   $$$   $$$   ###         ||"},
			{"||         ###   &&&   $$$   $$$   ###         ||"},
			{"||   $$$&&&   $$$$$$         $$$$$$###&&&$$$   ||"},
			{"||   $$$&&&   $$$$$$         $$$$$$###&&&$$$   ||"},
			{"||   $$$&&&   $$$$$$         $$$$$$###&&&$$$   ||"},
			{"||######$$$   $$$      &&&      $$$###&&&######||"},
			{"||######$$$   $$$      &&&      $$$###&&&######||"},
			{"||######$$$   $$$      &&&      $$$###&&&######||"},
			{"||&&&   $$$         $$$###&&&      ###$$$###$$$||"},
			{"||&&&   $$$         $$$###&&&      ###$$$###$$$||"},
			{"||&&&   $$$         $$$###&&&      ###$$$###$$$||"},
			{"||###         $$$               $$$            ||"},
			{"||###         $$$               $$$            ||"},
			{"||###         $$$               $$$            ||"},
			{"||&&&&&&   $$$   ===|       |   ###$$$   $$$$$$||"},
			{"||&&&&&&   $$$   ===|       |   ###$$$   $$$$$$||"},
			{"||&&&&&&   $$$   ===|       |   ###$$$   $$$$$$||"},
			{"||               &&&|       |&&&         +++###||"},
			{"||               &&&|       |&&&         +++###||"},
			{"||               &&&|       |&&&         +++###||"},
			{"||&&&&&&   $$$   ===|       |   ###$$$   $$$$$$||"},
			{"||&&&&&&   $$$   ===|       |   ###$$$   $$$$$$||"},
			{"||&&&&&&   $$$   ===|       |   ###$$$   $$$$$$||"},
			{"||###         $$$               $$$      ###   ||"},
			{"||###         $$$               $$$      ###   ||"},
			{"||###         $$$               $$$      ###   ||"},
			{"||&&&   $$$         $$$###&&&         $$$   $$$||"},
			{"||&&&   $$$         $$$###&&&         $$$   $$$||"},
			{"||&&&   $$$         $$$###&&&         $$$   $$$||"},
			{"||      $$$   $$$      &&&      $$$   &&&      ||"},
			{"||      $$$   $$$      &&&      $$$   &&&      ||"},
			{"||      $$$   $$$      &&&      $$$   &&&      ||"},
			{"||   $$$&&&   $$$$$$         $$$$$$   &&&$$$   ||"},
			{"||   $$$&&&   $$$$$$         $$$$$$   &&&$$$   ||"},
			{"||   $$$&&&   $$$$$$         $$$$$$   &&&$$$   ||"},
			{"||               &&&   $$$   $$$               ||"},
			{"||               &&&   $$$   $$$               ||"},
			{"||               &&&   $$$   $$$               ||"},
			{"|||||||||||||||||||||||||||||||||||||||||||||||||"}
		};
		return map[pos.Y][pos.X];
	}
}

void changeStateMap(Map* m) {
	for (short pY = 0; pY < MAP_HEIGHT; pY++) {
		for (short pX = 0; pX < MAP_WIDTH; pX++) {
			if (m->State[pY][pX] == Bomb_burst.NormalState) {
				if (m->LastState[pY][pX] != Space.NormalState &&
					m->LastState[pY][pX] != Bomb_Nm.NormalState &&
					m->LastState[pY][pX] != CAN_KEEP) {
					dropObject(m, { pX, pY }); }
				else {
					m->State[pY][pX] = Space.NormalState;
					m->Object[pY][pX] = { Space.Format, Space.Attribute };
				}
			}
			if (m->State[pY][pX] == CAN_KEEP) {
				if (m->Time[pY][pX] > 0) { m->Time[pY][pX]--; }
				else if (m->Time[pY][pX] == 0) {
					m->LastState[pY][pX] = m->State[pY][pX];
					m->State[pY][pX] = Space.NormalState;
					m->Object[pY][pX] = { Space.Format, Space.Attribute };
				}
			}
			_Object* Ob = &m->Object[pY][pX];
			putBuffer(pX, pY, Ob->Format, Ob->Attribute);
		}
	}
}

void Summary(Player* p, COORD pos) {
	setcolor(7, 0);
	gotoxy(pos.X, pos.Y + 1);
	printf("Player \t: %s", p->Format);
	gotoxy(pos.X, pos.Y + 2);
	printf_s("Power\t: %d", p->Bomb.PowerX);
	//char text[20] = "Player name";
	//char* c = text;
	//for (int n = 0; n < strlen(text); n++) {
	//	putBuffer(pos.X + n, pos.Y, *(c + n), NORMAL_ATTIBUTE);
	//}
	//char number[10];
	//convertToChar(p->Position.X, number);
	//for (int n = 0; n < strlen(number); n++) {
	//	putBuffer(pos.X + n, pos.Y + 1, number[n], NORMAL_ATTIBUTE);
	//	//if (number[n + 1] == '\0') { break; }
	//}

	gotoxy(pos.X, pos.Y + 2);
	printf_s("Power\t: %d", p->Bomb.PowerX);
	gotoxy(pos.X, pos.Y + 3);
	printf_s("Life\t\t: %d", p->Life);
	gotoxy(pos.X, pos.Y + 4);
	printf_s("Max Bomb\t: %d", p->Bomb.Amount);
	gotoxy(pos.X, pos.Y + 5);
	printf_s("Position\t: (%d,%d)", p->Position.X, p->Position.Y);
	gotoxy(pos.X, pos.Y + 6);
	printf_s("Point\t\t: %d", p->Point);
	gotoxy(pos.X, pos.Y + 7);
	printf_s("Bot count\t\t: %d", p->Bot.CountDirectionNow);
	gotoxy(pos.X, pos.Y + 8);
	printf_s("Bot Dir\t\t: %d", p->Bot.DirectionNow);
	gotoxy(pos.X, pos.Y + 9);
	printf_s("Drop\t\t: %d", p->Bomb.Drop);
}
