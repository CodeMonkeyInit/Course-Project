#ifndef program_menu_h
#define program_menu_h

#include <ncurses.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include "machineTime.h"
#include "macKeys.h"
#include "programMenuConstants.h"
#include "programMenuAdd.h"

void windowRefreshAndClear(WINDOW *window);
bool refreshIfNeeded();
bool keyWasPressed(int key);
void printMessage(char *messageString);
void init_menu();
void printHelp(int type);
void call_function(int function);
void render_menu();
void choose_menu();
void printStruct();

#endif /* program_menu_h */
