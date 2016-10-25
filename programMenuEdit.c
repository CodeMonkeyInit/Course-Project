//
//  programMenuEdit.c
//  courseWork
//
//  Created by Денис Кулиев on 13.10.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#include "programMenuEdit.h"

int currentChoice;
int currentField;
struct MachineTime *currentChoicePointer;
bool somethingDeleted;

int choicesNumber;

void toogleChoice(int choice,int type)
{
    
    mvwchgat(table, choice + TABLE_HEAD_SIZE, 1, TABLE_CHOICE_WIDTH, type, 2, NULL);
    wmove(table, 0, 0);
}

void moveCursorDown()
{
    if ( currentChoice >= choicesNumber)
    {
        currentChoice = choicesNumber;
    }
    else
    {
        toogleChoice(currentChoice,A_NORMAL);
        currentChoicePointer = currentChoicePointer -> next;
        currentChoice++;
    }
}

void moveCursorUp()
{
    if (currentChoice <= 0)
    {
        currentChoice = 0;
    }
    else
    {
        toogleChoice(currentChoice,A_NORMAL);
        currentChoicePointer = currentChoicePointer -> previous;
        currentChoice--;
    }
}

bool deleteSelected()
{
    int currentChoicesNumber;
    if ( start == end )
    {
        start = end = NULL;
    }
    else if (currentChoicePointer == start)
    {
        start = start -> next;
    }

    switch ( deleteRecord(&currentChoicePointer) )
    {
        case ENDING:
            currentChoice--;
            break;
        case EMPTY:
            updateTable();
            return EXIT;
        default:
            break;
    }
    end = getTableEnd(start, LINES - 6 , GET_NORMAL);
    currentChoicesNumber = (int) getRecordCount(start, end) - 1;
    if ( currentChoicesNumber != choicesNumber )
    {
        choicesNumber = currentChoicesNumber;
        somethingDeleted = true;
    }
    updateTable();
    return CONTINUE;
}

bool editKeypressHandler(int key)
{
    switch (key)
    {
        case KEY_DOWN:
            moveCursorDown();
            break;
        case KEY_UP:
            moveCursorUp();
            break;
        case KEY_MAC_ENTER:
            editRecord();
            break;
        case MAC_BACKSPACE:
            return deleteSelected();
            break;
        case KEY_ESC:
            return EXIT;
            break;
        default:
            break;
    }
    return CONTINUE;
}

void editStruct(int linesAvailable)
{
    currentChoice = 0;
    currentChoicePointer = start;
    choicesNumber = (int) getRecordCount(start, end) - 1;
    somethingDeleted = false;
    
    do
    {
        if (controlsLocked)
        {
            break;
        }
        if (somethingDeleted)
        {
            wclear(table);
            somethingDeleted = false;
        }
        printTable(HELP_EDIT_MODE);
        toogleChoice(currentChoice, A_REVERSE);
        wrefresh(table);
    } while ( editKeypressHandler( getch() ) != EXIT );
    
    toogleChoice(currentChoice, A_NORMAL);
}
