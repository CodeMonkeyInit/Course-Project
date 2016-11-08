//
//  programMenuView.c
//  courseWork
//
//  Created by Денис Кулиев on 13.10.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#include "programMenuTableExtras.h"

int linesAvailable;

WINDOW *table;

struct MachineTime *start,
                   *end;
char *tableString;
long currentPage;
bool refreshTable;
bool controlsLocked;

void printTable(int helpType)
{
    printHelp(helpType);
    wattron(table,COLOR_PAIR(2));
    
    wprintw(table, "%s", MENU_TABLE_HEAD);
    wprintw(table, "%s", tableString);
    wprintw(table, "%s", TABLE_BOTTOM);
    wattroff(table, COLOR_PAIR(2));
}

void loadNextPage()
{
    struct MachineTime *temp;
    
    if (NULL == end -> next)
    {
        refreshTable = false;
        return;
    }
    
    temp = end -> next;
    temp = getTableEnd(temp, linesAvailable, GET_NORMAL);
    
    free(tableString);
    tableString = recordsToTable(end -> next, temp);
    if ( tableString != NULL )
    {
        refreshTable = true;
        start = end -> next;
        end = temp;
        currentPage++;
    }
    else
    {
        refreshTable = false;
        tableString = recordsToTable(start, end);
    }
}

void loadPreviousPage()
{
    if (currentPage <= 0 )
    {
        refreshTable = false;
        return;
    }
    else
    {
        currentPage--;
        refreshTable = true;
        start = start -> previous;
        end = start;
        start = getTableEnd(end, linesAvailable, GET_REVERSE);
        
        free(tableString);
        tableString = recordsToTable(start, end);
    }
}

bool keypressHandler(int key)
{
    if (controlsLocked)
    {
        if (NULL != machineTimeBegining)
        {
            start = machineTimeBegining;
            end = getTableEnd(start, linesAvailable, GET_NORMAL);
            currentPage = 0;
            controlsLocked = false;
            updateTable();
            refreshTable = true;
        }
        if (KEY_ESC == key)
        {
            return EXIT;
        }
    }
    else
    {
        switch (key)
        {
            case KEY_DOWN:
                loadNextPage();
                break;
            case KEY_UP:
                loadPreviousPage();
                break;
            case KEY_MAC_ENTER:
                editStruct();
                refreshTable = true;
                clear();
                refresh();
                break;
            case KEY_ESC:
                return EXIT;
                break;
            default:
                break;
        }
    }
    return CONTINUE;
}

void updateTable()
{
    if ( (NULL != tableString) && (EMPTY_TABLE != tableString) )
    {
        free(tableString);
    }
    
    tableString = recordsToTable(start, end);
    if (NULL == tableString)
    {
        tableString  = EMPTY_TABLE;
        controlsLocked = true;
    }
}

void printStruct()
{
    controlsLocked = false;
    
    linesAvailable = LINES - SPACES_OTHER_THAN_TABLE;
    
    currentPage = 0;
    
    int offsetX = (COLS - TABLE_WIDTH) / 2,
        offsetY = ( LINES - (linesAvailable + SPACES_OTHER_THAN_TABLE) ) / 2 ;
    
    table = newwin(LINES,
                   TABLE_WIDTH,
                   offsetY,
                   offsetX);
    tableString = NULL;
    start = getMachineTimeStartingPointer();
    end = getTableEnd(start, linesAvailable, GET_NORMAL);
    updateTable();
    
    refreshTable = true;
    
    do
    {
        if (refreshTable)
        {
            printTable(HELP_TABLE);
            windowRefreshAndClear(table);
            refreshTable = false;
        }
    } while ( EXIT != keypressHandler( getch() ) );
    
    if (EMPTY_TABLE != tableString)
    {
        free(tableString);
    }
    
    wclear(table);
    delwin(table);
    
    clear();
    refresh();
}
