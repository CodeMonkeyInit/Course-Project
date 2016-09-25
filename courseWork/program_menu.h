//
//  program_menu.h
//  courseWork
//
//  Created by Денис Кулиев on 15.09.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#ifndef program_menu_h
#define program_menu_h

#include <ncurses.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include <unistd.h>
#include <stdlib.h>

#define KEY_MAC_ENTER 10
#define MENU_WIDTH 30
#define MENU_HEIGHT 20
#define MENU_HIGHLIGHT_LENGTH 26
#define DIALOG_WIDTH 50
#define DIALOG_HEIGHT 10
#define FUNCTION_EXIT 5

void refreshIfNeeded();
void stub(int choice);
void init_menu();
void print_exit();
void call_function(int function);
void render_menu();
void choose_menu();

#endif /* program_menu_h */
