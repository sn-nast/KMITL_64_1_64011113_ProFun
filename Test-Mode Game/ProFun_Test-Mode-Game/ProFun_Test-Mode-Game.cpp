#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<string.h>
#include"Addition-Feature.h"
#include"Buffer.h"
#include"Move.cpp"


struct player {
	char format[6];
	COORD position;
};
player Me;

int main() {
	strcpy_s(Me.format, "[O]");
	printf("%s", Me.format);
	playStatus = FALSE;
}
