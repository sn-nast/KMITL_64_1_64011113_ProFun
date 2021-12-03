#include "Map.h"
#include "main.h"
#include "Buffer.h"
#include "Object.h"

Map playMap[3]; 
time_t Second = time(NULL);
tm* currentTime = localtime(&Second);
unsigned int lastTime = 0;
bool timeUp = false;
bool winStatus = false;
bool timeChange = false;
SHORT summaryLastLine = 0; 

void setupMap(Map* m, int n_map) {
	m->GameTime_Minute = 5;
	m->GameTime_Second = 0;

	m->maxBombPowerX = 0;
	m->maxBombPowerY = 0;

	m->CountDrop_Life = 0;
	m->CountDrop_newBomb = 0;
	m->CountDrop_Potion = 0;
	m->CountDrop_Deathless = 0;

	int randColorWall[10];
	for (int i = 0; i < typeWall; i++) {
		randColorWall[i] = rand() % (13 + 1 - 1) + 1;
	}

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
			m->WarningLost[pY][pX] = false;
			m->OwnerBomb[pY][pX] = NO_OWNER_BOMB;
			putBuffer(pX, pY, Ob->Format, Ob->Attribute);
		}
	}
}

void countDownGameTime(Map* m) {
	gotoxy(MAP_WIDTH, 1);
	setcolor(15, 0);
	printf("Time "); 
	timeChange = false;
	lastTime = currentTime->tm_sec;
	Second = time(NULL);
	currentTime = localtime(&Second);
	if (lastTime != currentTime->tm_sec) {
		timeChange = true;
	}
	printf("%02d:%02d", m->GameTime_Minute, m->GameTime_Second);
	if (timeChange == true) {
		if (m->GameTime_Second == 0) {
			if (m->GameTime_Minute != 0) {
				m->GameTime_Second = 59;
				m->GameTime_Minute--;
			}
			else {
				playStatus = false;
				endGameStatus = true;
				timeUp = true;
				countLost++;
			}
			return;
		}
		m->GameTime_Second--;
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
			{"||MMM$$$      %%%===MMMMMM   MMM      MMM+++%%%||"},
			{"||MMM$$$      %%%===MMMMMM   MMM      MMM+++%%%||"},
			{"||MMM$$$      %%%===MMMMMM   MMM      MMM+++%%%||"},
			{"||===$$$+++   +++===$$$+++$$$%%%$$$   ++++++===||"},
			{"||===$$$+++   +++===$$$+++$$$%%%$$$   ++++++===||"},
			{"||===$$$+++   +++===$$$+++$$$%%%$$$   ++++++===||"},
			{"||   MMM===MMM         ===            MMM      ||"},
			{"||   MMM===MMM         ===            MMM      ||"},
			{"||   MMM===MMM         ===            MMM      ||"},
			{"||%%%++++++MMM+++   %%%   %%%%%%+++   $$$+++   ||"},
			{"||%%%++++++MMM+++   %%%   %%%%%%+++   $$$+++   ||"},
			{"||%%%++++++MMM+++   %%%   %%%%%%+++   $$$+++   ||"},
			{"||%%%   MMM======MMM|||||||||MMM%%%MMM      MMM||"},
			{"||%%%   MMM======MMM|$$$$$  |MMM%%%MMM      MMM||"},
			{"||%%%   MMM======MMM|$$$$$  |MMM%%%MMM      MMM||"},
			{"||MMM&&&&&&   $$$   |  $$$$$|   $$$===++++++%%%||"},
			{"||MMM&&&&&&   $$$   |  $$$$$|   $$$===++++++%%%||"},
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
			{"||      ===######&&&   $$$   $$$   ###===      ||"},
			{"||      ===######&&&   $$$   $$$   ###===      ||"},
			{"||      ===######&&&   $$$   $$$   ###===      ||"},
			{"||   $$$###   $$$$$$   ======$$$$$$###===$$$   ||"},
			{"||   $$$###   $$$$$$   ======$$$$$$###===$$$   ||"},
			{"||   $$$###   $$$$$$   ======$$$$$$###===$$$   ||"},
			{"||######$$$===$$$   ===&&&###   $$$###&&&===   ||"},
			{"||######$$$===$$$   ===&&&###   $$$###&&&===   ||"},
			{"||######$$$===$$$   ===&&&###   $$$###&&&===   ||"},
			{"||&&&===$$$===      $$$###&&&###   ###$$$###$$$||"},
			{"||&&&===$$$===      $$$###&&&###   ###$$$###$$$||"},
			{"||&&&===$$$===      $$$###&&&###   ###$$$###$$$||"},
			{"||###===      $$$      ===######$$$   ===######||"},
			{"||###===      $$$      ===######$$$   ===######||"},
			{"||###===      $$$      ===######$$$   ===######||"},
			{"||&&&&&&###$$$   ===|||||||||   ###$$$   $$$$$$||"},
			{"||&&&&&&###$$$   ===|& # # &|   ###$$$   $$$$$$||"},
			{"||&&&&&&###$$$   ===| &# #& |   ###$$$   $$$$$$||"},
			{"||      ###      &&&|##& &##|&&&   =========###||"},
			{"||      ###      &&&|#  $  #|&&&   =========###||"},
			{"||      ###      &&&|##& &##|&&&   =========###||"},
			{"||&&&&&&###$$$   ===| &# #& |   ###$$$###$$$$$$||"},
			{"||&&&&&&###$$$   ===|& # # &|   ###$$$###$$$$$$||"},
			{"||&&&&&&###$$$   ===|||||||||   ###$$$###$$$$$$||"},
			{"||###      ===$$$   ===###   ###$$$   ######   ||"},
			{"||###      ===$$$   ===###   ###$$$   ######   ||"},
			{"||###      ===$$$   ===###   ###$$$   ######   ||"},
			{"||&&&   $$$===      $$$###&&&###      $$$   $$$||"},
			{"||&&&   $$$===      $$$###&&&###      $$$   $$$||"},
			{"||&&&   $$$===      $$$###&&&###      $$$   $$$||"},
			{"||======$$$   $$$      &&&   ###$$$===&&&###===||"},
			{"||======$$$   $$$      &&&   ###$$$===&&&###===||"},
			{"||======$$$   $$$      &&&   ###$$$===&&&###===||"},
			{"||   $$$===###$$$$$$         $$$$$$===###$$$   ||"},
			{"||   $$$===###$$$$$$         $$$$$$===###$$$   ||"},
			{"||   $$$===###$$$$$$         $$$$$$===###$$$   ||"},
			{"||      ###   ###&&&   $$$   $$$   ======      ||"},
			{"||      ###   ###&&&   $$$   $$$   ======      ||"},
			{"||      ###   ###&&&   $$$   $$$   ======      ||"},
			{"|||||||||||||||||||||||||||||||||||||||||||||||||"}
		};
		return map[pos.Y][pos.X];
	}
	else if (n == 3) {
		char map[MAP_HEIGHT][MAP_WIDTH] = {
			{"|||||||||||||||||||||||||||||||||||||||||||||||||"},
			{"||      UUU$$$$$$MMMMMM   UUUMMM***$$$         ||"},
			{"||      UUU$$$$$$MMMMMM   UUUMMM***$$$         ||"},
			{"||      UUU$$$$$$MMMMMM   UUUMMM***$$$         ||"},
			{"||   ***%%%UUU   MMM$$$$$$***UUU%%%UUUMMM***   ||"},
			{"||   ***%%%UUU   MMM$$$$$$***UUU%%%UUUMMM***   ||"},
			{"||   ***%%%UUU   MMM$$$$$$***UUU%%%UUUMMM***   ||"},
			{"||UUU***%%%***   ***$$$UUU***$$$   ***UUU$$$UUU||"},
			{"||UUU***%%%***   ***$$$UUU***$$$   ***UUU$$$UUU||"},
			{"||UUU***%%%***   ***$$$UUU***$$$   ***UUU$$$UUU||"},
			{"||UUU   MMMMMM%%%$$$   %%%MMM$$$   MMMMMM%%%UUU||"},
			{"||UUU   MMMMMM%%%$$$   %%%MMM$$$   MMMMMM%%%UUU||"},
			{"||UUU   MMMMMM%%%$$$   %%%MMM$$$   MMMMMM%%%UUU||"},
			{"||MMM$$$%%%$$$         ***MMMUUUUUU***MMM***%%%||"},
			{"||MMM$$$%%%$$$         ***MMMUUUUUU***MMM***%%%||"},
			{"||MMM$$$%%%$$$         ***MMMUUUUUU***MMM***%%%||"},
			{"||MMM%%%UUU$$$MMM***|||||||||***   ***%%%MMM   ||"},
			{"||MMM%%%UUU$$$MMM***|&&&&&&&|***   ***%%%MMM   ||"},
			{"||MMM%%%UUU$$$MMM***|&***  &|***   ***%%%MMM   ||"},
			{"||$$$***%%%   MMM   |&  ***&|UUUMMMUUU%%%$$$$$$||"},
			{"||$$$***%%%   MMM   |&***  &|UUUMMMUUU%%%$$$$$$||"},
			{"||$$$***%%%   MMM   |&  ***&|UUUMMMUUU%%%$$$$$$||"},
			{"||MMM   %%%$$$%%%$$$|&***  &|$$$%%%***UUU%%%MMM||"},
			{"||MMM   %%%$$$%%%$$$|&&&&&&&|$$$%%%***UUU%%%MMM||"},
			{"||MMM   %%%$$$%%%$$$|||||||||$$$%%%***UUU%%%MMM||"},
			{"||%%%$$$MMM$$$MMM%%%UUU$$$   UUUMMM$$$%%%$$$   ||"},
			{"||%%%$$$MMM$$$MMM%%%UUU$$$   UUUMMM$$$%%%$$$   ||"},
			{"||%%%$$$MMM$$$MMM%%%UUU$$$   UUUMMM$$$%%%$$$   ||"},
			{"||UUU%%%%%%      $$$UUUUUU   ***MMMMMM      MMM||"},
			{"||UUU%%%%%%      $$$UUUUUU   ***MMMMMM      MMM||"},
			{"||UUU%%%%%%      $$$UUUUUU   ***MMMMMM      MMM||"},
			{"||   ***%%%$$$%%%$$$***UUU$$$***UUU***UUU***   ||"},
			{"||   ***%%%$$$%%%$$$***UUU$$$***UUU***UUU***   ||"},
			{"||   ***%%%$$$%%%$$$***UUU$$$***UUU***UUU***   ||"},
			{"||   $$$      MMMUUU***$$$***      UUU%%%***   ||"},
			{"||   $$$      MMMUUU***$$$***      UUU%%%***   ||"},
			{"||   $$$      MMMUUU***$$$***      UUU%%%***   ||"},
			{"||      %%%***$$$%%%      MMMUUU$$$***MMM      ||"},
			{"||      %%%***$$$%%%      MMMUUU$$$***MMM      ||"},
			{"||      %%%***$$$%%%      MMMUUU$$$***MMM      ||"},
			{"|||||||||||||||||||||||||||||||||||||||||||||||||"}
		};
		return map[pos.Y][pos.X];
	}
}

void changeStateMap(Map* m) {
	for (short pY = 0; pY < MAP_HEIGHT; pY++) {
		for (short pX = 0; pX < MAP_WIDTH; pX++) {
			_Object* Ob = &m->Object[pY][pX];
			char Format = Ob->Format;
			int Attribute = Ob->Attribute;
			if (m->State[pY][pX] == Bomb_burst.NormalState) {
				if (m->LastState[pY][pX] != Space.NormalState &&
					m->LastState[pY][pX] != Bomb_Nm.NormalState &&
					m->LastState[pY][pX] != CAN_KEEP &&
					m->LastState[pY][pX] != Bomb_burst.NormalState) {
					dropObject(m, { pX, pY }); }
				else {
					m->LastState[pY][pX] = m->State[pY][pX];
					m->State[pY][pX] = Space.NormalState;
					m->Object[pY][pX] = { Space.Format, Space.Attribute };
				}
				Format = Ob->Format;
				Attribute = Ob->Attribute;
			}
			if (m->State[pY][pX] == CAN_KEEP) {
				if (m->Time[pY][pX] > 0 && timeChange == true) { m->Time[pY][pX]--; }
				else if (m->Time[pY][pX] == 0) {
					m->LastState[pY][pX] = m->State[pY][pX];
					m->State[pY][pX] = Space.NormalState;
					m->Object[pY][pX] = { Space.Format, Space.Attribute };
					Format = Ob->Format;
					Attribute = Ob->Attribute;
				}
				if (m->Time[pY][pX] < 4) {
					m->WarningLost[pY][pX] = !m->WarningLost[pY][pX];
					if (m->WarningLost[pY][pX] == true) {
						Format = ' ';
						Attribute = NORMAL_ATTRIBUTE;
					}
				}
			}
			putBuffer(pX, pY, Format, Attribute);
		}
	}
}

void summary(Player* p, COORD pos) {
	COORD tempPos = pos;
	pos.X += 4;
	setcolor(15, 0);
	gotoxy(pos.X, pos.Y++);
	printf("%-7s : ", "Player");
	printf("%s", p->Name);

	setcolor(15, 0);
	gotoxy(pos.X, pos.Y++);
	printf_s("%-7s : ", "Power");
	for (int n = 0; n < p->Bomb.PowerX; n++) {
		setcolor(newBomb.Attribute, newBomb.Attribute);
		printf("%c", '+');
		setcolor(15, 0);
		printf("%c", ' ');
	}

	setcolor(15, 0);
	gotoxy(pos.X, pos.Y++);
	printf_s("%-7s : ", "Life", p->Life);
	if ((p->Call != playerMe.Call && p->Bot.Alive == true) ||
		p->Call == playerMe.Call) {
		for (int n = 0; n < p->Life; n++) {
			setcolor(Life.Attribute, 0);
			printf("%c ", Life.Format);
		}
	}

	setcolor(15, 0);
	gotoxy(pos.X, pos.Y++);
	printf_s("%-7s : ", "Bomb");
	for (int n = 0; n < p->Bomb.Amount; n++) {
		setcolor(newBomb.Attribute, 0);
		printf("%c ", newBomb.Format);
	}

	setcolor(15, 0);
	gotoxy(pos.X, pos.Y++);
	printf("---------------------");
	gotoxy(pos.X, pos.Y++);
	printf_s("%-7s : %d", "Point", p->Point);
	gotoxy(pos.X, pos.Y++);
	printf("---------------------");

	for (int y = tempPos.Y; y < pos.Y; y++) {
		for (int x = tempPos.X; x < tempPos.X + 2; x++) {
			setcolor(p->Attribute % 256, 0);
			gotoxy(x, y);
			printf(" ");
		}
	}

}
