#ifndef program_menu_h
#define program_menu_h

#include <ncurses.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include "machineTime.h"
#include "macKeys.h"

#define HELP_MENU 0
#define HELP_TABLE 1
#define HELP_EDIT_MODE 2
#define MENU_WIDTH 30
#define MENU_HEIGHT 20
#define MENU_HIGHLIGHT_LENGTH 26
#define DIALOG_WIDTH 50
#define DIALOG_HEIGHT 10
#define FUNCTION_EXIT 5
#define TABLE_WIDTH 69

void windowRefreshAndClear(WINDOW *window);
bool refreshIfNeeded();
bool keyWasPressed(int key);
void stub(int choice);
void init_menu();
void printHelp(int type);
void call_function(int function);
void render_menu();
void choose_menu();
void printStruct();

#endif /* program_menu_h */
