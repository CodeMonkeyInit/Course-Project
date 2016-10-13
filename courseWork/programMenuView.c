//
//  programMenuView.c
//  courseWork
//
//  Created by Денис Кулиев on 13.10.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#include "programMenu.h"


void printTable()
{
    int linesAvailable = LINES - 6;
    struct MachineTime *start = getMachineTimeStartingPointer();
    struct MachineTime *end = getTableEnd(start, linesAvailable);
    
    char *tableString = recordsToTable(start, end);
    
    do
    {
        WINDOW *table;
        
        int offsetX = (COLS - TABLE_WIDTH) / 2,
        offsetY = ( LINES - (linesAvailable + 6) ) / 2 ;
        
        table = newwin(LINES,
                       TABLE_WIDTH,
                       offsetY,
                       offsetX);
        refreshIfNeeded();
        
        wattron(table,COLOR_PAIR(2));
        
        print_help(HELP_TABLE);
        
        wprintw(table, "%s", TABLE_HEAD);
        wprintw(table, "%s", tableString);
        wprintw(table, "%s", TABLE_BOTTOM);
        
        wattroff(table, COLOR_PAIR(2));
        
        wrefresh(table);
        delwin(table);
        
    } while ( !keyWasPressed(KEY_ESC) );
    
    clear();
    refresh();
}
