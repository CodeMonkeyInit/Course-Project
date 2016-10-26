//
//  programMenuEditRecord.c
//  courseWork
//
//  Created by Денис Кулиев on 15.10.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#include "programMenuEdit.h"

bool somethingChanged;

int getTimeFromUser(int offsetY, int offsetX)
{
    int time;
    mvwprintw(table,offsetY,offsetX, "%8s", " ");
    wmove(table, offsetY, offsetX);
    if ( INPUT_ABORTED == windowGetInput(table, "%8d", &time) )
    {
        return INPUT_ABORTED;
    }
    else
    {
        return time;
    }
}

void toogleChoiceField(int field, int type)
{
    switch (field)
    {
        case CAFEDRA_CODE:
            mvwchgat(table,
                     currentChoice + TABLE_HEAD_SIZE,
                     CAFEDRA_CODE_TABLE_OFFSET,
                     CAFEDRA_CODE_LENGTH , type,
                     2,
                     NULL);
            break;
        case CAFEDRA_NAME:
            mvwchgat(table,
                     currentChoice + TABLE_HEAD_SIZE,
                     CAFEDRA_NAME_TABLE_OFFSET,
                     CAFEDRA_NAME_FORMAT_LENGTH , type,
                     2,
                     NULL);
            break;
        case TABLE_TIME_PLANNED:
            mvwchgat(table,
                     currentChoice + TABLE_HEAD_SIZE,
                     TIME_PLANNED_TABLE_OFFSET,
                     TIME_LENGTH , type,
                     2,
                     NULL);
            break;
        case TABLE_TIME_USED:
            mvwchgat(table,
                     currentChoice + TABLE_HEAD_SIZE,
                     TIME_USED_TABLE_OFFSET,
                     TIME_LENGTH , type,
                     2,
                     NULL);
            break;
        default:
            break;
    }
    wmove(table, 0, 0);
}

void editMode()
{
    wattron(table,COLOR_PAIR(2));
    curs_set(1);
    echo();
    char tempString[81];
    char *tempFormatString;
    int time;
    switch (currentField)
    {
        case CAFEDRA_CODE:
            mvwprintw(table,
                      currentChoice + TABLE_HEAD_SIZE,
                      CAFEDRA_CODE_TABLE_OFFSET,
                      "%11s"," ");
            wmove(table, currentChoice + TABLE_HEAD_SIZE, CAFEDRA_CODE_TABLE_OFFSET);
            
            //if user inputs multibyte symbols such as russian abort input
            if ( INPUT_ABORTED != windowGetInput(table, "%5s", tempString)
                && (!isUnicodeMultibyteString(tempString)) )
            {
                tabToSpace(tempString);
                strcpy(currentChoicePointer -> cafedraCode, tempString);
            }
            break;
        case CAFEDRA_NAME:
            mvwprintw(table,
                      currentChoice + TABLE_HEAD_SIZE,
                      CAFEDRA_NAME_TABLE_OFFSET,
                      "%20s"," ");
            wmove(table, currentChoice + TABLE_HEAD_SIZE, CAFEDRA_NAME_TABLE_OFFSET);
            
            if ( INPUT_ABORTED != windowGetInput(table, "%20s", tempString) )
            {
                tabToSpace(tempString);
                tempFormatString = formatUtf8String(tempString, 20);
                strcpy(currentChoicePointer -> cafedraName, tempFormatString);
                free(tempFormatString);
            }
            break;
        case TABLE_TIME_PLANNED:
            time = getTimeFromUser(currentChoice + TABLE_HEAD_SIZE, TIME_PLANNED_TABLE_OFFSET);
            
            if (time != INPUT_ABORTED)
            {
                currentChoicePointer -> timeSpent.plan = time;
            }
            break;
        case TABLE_TIME_USED:
            time = getTimeFromUser(currentChoice + TABLE_HEAD_SIZE, TIME_USED_TABLE_OFFSET);
            if (time != INPUT_ABORTED)
            {
                
                currentChoicePointer -> timeSpent.realLife = time;
            }
        default:
            break;
    }
    noecho();
    somethingChanged = true;
    wattroff(table, COLOR_PAIR(2));
    wrefresh(table);
    curs_set(0);
}

bool editRecordKeypressHandler(int key)
{
    toogleChoiceField(currentField, A_NORMAL);
    switch (key)
    {
        case KEY_DOWN:
            moveCursorDown();
            break;
        case KEY_UP:
            moveCursorUp();
            break;
        case KEY_LEFT:
            if (currentField > 0 )
            {
                currentField--;
            }
            break;
        case KEY_RIGHT:
            if (currentField < FIELD_COUNT - 1)
            {
                currentField++;
            }
            break;
        case KEY_MAC_ENTER:
            editMode();
            break;
        case MAC_BACKSPACE:
            return deleteSelected();
            break;
        case KEY_ESC:
            return EXIT;
        default:
            break;
    }
    
    toogleChoiceField(currentField, A_REVERSE);
    wrefresh(table);
    return CONTINUE;
}

void editRecord()
{
    somethingChanged = false;
    somethingDeleted = false;
    currentField = 0;
    toogleChoice(currentChoice, A_NORMAL);
    toogleChoiceField(currentField, A_REVERSE);
    wrefresh(table);
    
    while (editRecordKeypressHandler( getch() ) != EXIT)
    {
        if (somethingDeleted)
        {
            wclear(table);
            somethingDeleted = false;
            somethingChanged = true;
        }
        
        if (somethingChanged)
        {
            free(tableString);
            windowRefreshAndClear(table);
            tableString = recordsToTable(start, end);
            printTable(HELP_EDIT_MODE);
            toogleChoiceField(currentField, A_REVERSE);
            wrefresh(table);
            somethingChanged = false;
        }
    }
    toogleChoice(currentChoice, A_REVERSE);
}
