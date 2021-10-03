#include "Move.h"
#include "main.h"
#include "Buffer.h"

void movePlayer(COORD pos, char format[20], int atb) {
	for (int i = 0; i < strlen(format); i++) {
		putBuffer(pos.X, pos.Y, format[i], atb);
	}
}

void deleteLastMove() {
	;
}

void drawME() {
	;
}
