//
//  programMenuExtras.c
//  courseWork
//
//  Created by Денис Кулиев on 13.10.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//
#include "programMenu.h"

int _nCols,
    _nRows;

void windowRefreshAndClear(WINDOW *window)
{
    wrefresh(window);
    wclear(window);
}

bool refreshIfNeeded()
{
    if ( (_nCols != COLS) || (_nRows != LINES) )
    {
        _nCols = COLS;
        _nRows = LINES;
        clear();
        refresh();
        
        return true;
    }
    else
    {
        return false;
    }
}

bool keyWasPressed(int key)
{
    if( key == getch() )
    {
        return  true;
    }
    else
    {
        return false;
    }
}

void print_help(int type)
{
    attron(COLOR_PAIR(1));
    switch (type)
    {
        case HELP_MENU:
            mvprintw(LINES - 1, 0, "ESC - чтобы выйти, ↑↓ для навигации ↲ для потверждения выбора");
            break;
        case HELP_TABLE:
            mvprintw(LINES - 1, 0, "ESC чтобы вернутся в меню, ↑↓ смена страниц  ↲ режим редактирования");
            break;
        case HELP_EDIT_MODE:
            mvprintw(LINES - 1, 0, "ESC чтобы вернутся, ↑↓ движение вверх/вниз ↲ редактировать ← удалить запись");
        default:
            break;
    }
    
    attroff(COLOR_PAIR(1));
}


