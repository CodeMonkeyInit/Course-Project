//
//  programMenuExtras.c
//  courseWork
//
//  Created by Денис Кулиев on 13.10.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//
#include "programMenuChoices.h"
#include "programMenu.h"

int _nCols,
    _nRows;

void stub(int choice)
{
    clear();
    refresh();
    
    do
    {
        WINDOW *dialog;
        int offsetX = (COLS - DIALOG_WIDTH) / 2,
        offsetY = (LINES - DIALOG_HEIGHT) / 2;
        refreshIfNeeded();
        
        print_help(HELP_MENU);
        
        dialog = newwin(DIALOG_HEIGHT,
                        DIALOG_WIDTH,
                        offsetY,
                        offsetX);
        
        box(dialog, 0, 0);
        mvwprintw(dialog, 3, 3, "Вы выбрали %s", choices[choice]);
        wbkgd(dialog, COLOR_PAIR(1));
        wrefresh(dialog);
        delwin(dialog);
    } while ( !keyWasPressed(KEY_MAC_ENTER) );
    
    clear();
    refresh();
    
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
        default:
            break;
    }
    
    attroff(COLOR_PAIR(1));
}


