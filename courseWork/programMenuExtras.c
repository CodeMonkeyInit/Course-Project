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

void printHelp(int type)
{
    attron(COLOR_PAIR(1));
    switch (type)
    {
        case HELP_MENU:
            mvprintw(LINES - 1, 0, "ESC - чтобы выйти без сохранения, ↑↓ для навигации ↲ для потверждения выбора");
            break;
        case HELP_TABLE:
            mvprintw(LINES - 1, 0, "ESC чтобы вернутся в меню, ↑↓ смена страниц  ↲ режим редактирования");
            break;
        case HELP_EDIT_MODE:
            mvprintw(LINES - 1, 0, "ESC чтобы вернутся, ↑↓ движение вверх/вниз ↲ редактировать ← удалить запись");
            break;
        case MESSAGE_HELP:
            mvprintw(LINES - 1, 0, "Нажмите ↲ , чтобы продолжить");
            break;
        case ADD_HELP:
            attron(COLOR_PAIR(2));
            mvprintw(LINES - 2, 1, "ESC - чтобы выйти, ↑↓ для навигации ↲ для потверждения");
            attroff(COLOR_PAIR(2));
            break;
        default:
            mvprintw(LINES - 1, 0, "Нажмите ↲ , чтобы продолжить help to be written...");
            break;
    }
    
    attroff(COLOR_PAIR(1));
}

void printMessage(char *message)
{
    clear();
    refresh();
    
    do
    {
        WINDOW *dialog;
        int offsetX = (COLS - DIALOG_WIDTH) / 2,
        offsetY = (LINES - DIALOG_HEIGHT) / 2;
        int buttonOffsetX = getStringMiddlePostition(OK_BUTTON, DIALOG_WIDTH),
            buttonOffsetY = DIALOG_HEIGHT - 3;
        refreshIfNeeded();
        
        printHelp(MESSAGE_HELP);
        
        dialog = newwin(DIALOG_HEIGHT,
                        DIALOG_WIDTH,
                        offsetY,
                        offsetX);
        
        box(dialog, 0, 0);
        wbkgd(dialog, COLOR_PAIR(2));
        mvwprintw(dialog, 3, 3, "%s", message);
        mvwprintw(dialog, buttonOffsetY, buttonOffsetX, "%s", OK_BUTTON);
        mvwchgat(dialog, buttonOffsetY, buttonOffsetX - 2 , utf8len(OK_BUTTON) + 4 , A_REVERSE, 2, NULL);
        
        windowRefreshAndClear(dialog);
        delwin(dialog);
    } while ( !keyWasPressed(KEY_MAC_ENTER) );
    
    clear();
    refresh();
}


