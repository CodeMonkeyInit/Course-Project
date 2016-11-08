#ifndef program_menu_h
#define program_menu_h

#include <ncurses.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include "macKeys.h"
#include "programMenuConstants.h"
#include "programMenuAdd.h"
#include "programMenuSearch.h"
#include "customGetInput.h"
#include "IMachineTime.h"
#include <stdio.h>


typedef struct _menu
{
    const char **choices;
    int  choicesCount;
    int  colorPair;
    int  highlight;
    void (*menuCallFunction)(int);
} MENU;

extern const char *menuChoices[];
extern const int MENU_CHOICES_COUNT;
extern bool exitMenu;

void initMenuParameters(MENU *parameters,
                        const char *choices[] ,
                        const int choicesCount,
                        void (*menuCallFunction)(int));
int getStringMiddlePostition(const char *string, const int width);
void windowRefreshAndClear(WINDOW *window);
bool refreshIfNeeded();
bool keyWasPressed(int key);
void printMessage(char *messageString);
bool getUserInputDialog(char *message, char *response);
void init_menu();
void printHelp(int type);
void call_function(int function);
void render_menu(MENU parameters);
void printStruct();

void openFileMenu();

void printSortMenu();

void printTypeSortMenu(int field);

#endif /* program_menu_h */
