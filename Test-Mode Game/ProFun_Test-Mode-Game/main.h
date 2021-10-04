#pragma once 

#include <Windows.h>
#include <stdio.h>
#include <string.h>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT; 
extern const int NORMAL_ATTIBUTE;
 

extern HANDLE wHnd;
extern HANDLE rHnd;
extern DWORD fdwMode;
extern CHAR_INFO consoleBuffer[];
extern COORD bufferSize;
extern COORD characterPos;
extern SMALL_RECT windowSize;


extern bool playStatus;
extern DWORD numEvents;
extern DWORD numEventsRead;

const short RIGHT_ARROW_1 = 16;
const short LEFT_ARROW_1 = 17;
const short UP_ARROW_1 = 30;
const short DOWN_ARROW_1 = 31;

const short RIGHT_ARROW_2 = 26;
const short LEFT_ARROW_2 = 27;
const short UP_ARROW_2 = 24;
const short DOWN_ARROW_2 = 25;

struct Player {
	char format[5];
	unsigned int lenght;
	unsigned int height;
	COORD position;
	COORD last_position;
	int attribute;
};

typedef struct {
	char format[6];
	COORD position;
	COORD last_position;
	int attribute;
}newStuctForm;
