#pragma once 

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT; 

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
extern INPUT_RECORD* eventBuffer;

struct Player {
	char format[6];
	COORD position;
	COORD last_position;
	int attribute;
};
