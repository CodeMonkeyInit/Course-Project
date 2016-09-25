//
//  program_menu.c
//  courseWork
//
//  Created by Денис Кулиев on 15.09.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#include "program_menu.h"

char *choices[] = {
    "Ввод",
    "Вывод",
    "Choice 3",
    "Choice 4",
    "Выход",
};
const int choices_count = 5;

bool colorAvailable;

int _nCols,
    _nRows;

void refreshIfNeeded()
{
    if ( (_nCols != COLS) || (_nRows != LINES) )
    {
        _nCols = COLS;
        _nRows = LINES;
        clear();
        refresh();
    }
}

void stub(int choice)
{
    WINDOW *dialog;
    int offsetX = (COLS - DIALOG_WIDTH) / 2,
        offsetY = (LINES - DIALOG_HEIGHT) / 2;
    
    dialog = newwin(DIALOG_HEIGHT,
                    DIALOG_WIDTH,
                    offsetY,
                    offsetX);
    _nCols = COLS;
    _nRows = LINES;
    
    box(dialog, 0, 0);
    mvwprintw(dialog, 3, 3, "Вы выбрали %s", choices[choice]);
    wbkgd(dialog, COLOR_PAIR(1));
    wrefresh(dialog);
    sleep(1);
    delwin(dialog);
    
    clear();
    refresh();
}

void init_menu()
{
    setlocale(LC_ALL, "");
    
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    cbreak();
    curs_set(0);

    colorAvailable = has_colors();
    
    if(colorAvailable)
    {
        start_color();
        init_pair(1,COLOR_GREEN, COLOR_BLACK);
        init_pair(2,COLOR_WHITE,COLOR_RED);
    }
    refresh();
}

void print_exit()
{
    attron(COLOR_PAIR(1));
    mvprintw(LINES - 1, 0, "F1 - для того чтобы выйти, стрелочки для навигации и enter для потверждения");
    attroff(COLOR_PAIR(1));
}

void call_function(int function)
{
    switch (function)
    {
        case FUNCTION_EXIT:
            clear();
            refresh();
            exit(0);
            break;
        case 0:case 1:case 2:case 3:case 4:
            stub(function - 1);
            break;
        default:
            break;
    }
    
}

void render_menu(int highlight)
{
    refreshIfNeeded();
    
    WINDOW *menu;
    print_exit();
    
    int offsetX = (COLS - MENU_WIDTH) / 2;
    int offsetY = (LINES - MENU_HEIGHT) / 2;
    
    
    menu = newwin(MENU_HEIGHT,
                  MENU_WIDTH,
                  offsetY,
                  offsetX);
    box(menu, 0, 0);
    
    wbkgd(menu, COLOR_PAIR(2));
    //bkgd(COLOR_PAIR(2));
    
    wmove(menu, 7, 0);
    
    for (int i = 0; i < choices_count; i++)
    {
        int choice_lenght  = (int) strlen(choices[i]);
        
        int x = 5,
            y = getcury(menu);
        
        mvwprintw(menu, y + 1, x + 4, "%d: ", i + 1);
        wrefresh(menu);
    
        for (int j = 0; j < choice_lenght; j++)
        {
            wprintw(menu, "%c", choices[i][j]);
        }
        
        if (highlight == i)
        {
            mvwchgat(menu, y + 1, 2, MENU_HIGHLIGHT_LENGTH, A_REVERSE, 0, NULL);
        }
    }
    wrefresh(menu);
    
    delwin(menu);
    
    choose_menu(getch(), highlight);
    
}

void choose_menu(int key, int highlight)
{
    usleep(13);
    switch (key)
    {
        case KEY_DOWN:
            highlight++;
            if (highlight > choices_count - 1)
            {
                highlight = 0;
            }
            break;
        case KEY_UP:
            highlight--;
            if (highlight < 0)
            {
                highlight = choices_count - 1;
            }
            break;
        case KEY_F(1):
            clear();
            refresh();
            return;
            break;
        case KEY_MAC_ENTER:
            call_function(highlight + 1);
            break;
        default:
            break;
    }
    render_menu(highlight);
}
