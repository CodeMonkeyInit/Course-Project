//
//  programMenuAdd.c
//  courseWork
//
//  Created by Денис Кулиев on 04.11.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#include "programMenuAdd.h"

int currentChoiceAdd;
WINDOW *add;
int addLines;
int addCols;
char **recordStrings;

const char *fields[] =
{
    "Код кафедры:",
    "Название Кафедры:",
    "Времени запланированно:",
    "Времени использованно:"
};

void recordStringsAllock()
{
    recordStrings = malloc(sizeof(char *) * 4);
    for (int i = 0; i < FIELD_COUNT; i++)
    {
        recordStrings[i] = calloc(81, sizeof(char));
    }
    return;
}

bool noEmptyFields()
{
    for (int i = 0; i < FIELD_COUNT; i++)
    {
        if ( !strcmp(recordStrings[i], "") )
        {
            currentChoiceAdd = i;
            return false;
        }
    }
    return true;
}

void toogleAddChoice(int type, int size)
{
    int offsetX = 0;
    if (NORMAL_CHOICE_SIZE == size)
    {
        offsetX = size;
    }
    mvwchgat(add,
             addLines / 4 + currentChoiceAdd,
             addCols / 4 + offsetX,
             size,
             type,
             2,
             NULL);
}

void inputData()
{
    char formatString[10];
    bool strictInput = false;
    echo();
    curs_set(1);
    switch (currentChoiceAdd)
    {
        case CAFEDRA_CODE_CHOICE:
            //баг с русскими сиволами
            strcpy(formatString, "%6s");
            strictInput = true;
            break;
        case CAFEDRA_NAME_CHOICE:
            strcpy(formatString, "%20s");
            break;
        case TIME_PLANNED_CHOICE: case TIME_USED_CHOICE:
            strcpy(formatString, "%9s");
            break;
        default:
            return;
            break;
    }
    mvwprintw(add,
              addLines / 4 + currentChoiceAdd,
              addCols / 4 + NORMAL_CHOICE_SIZE,
              formatString, " ");
    wmove(add, addLines / 4 + currentChoiceAdd, addCols / 4 + NORMAL_CHOICE_SIZE);
    
    if ( INPUT_ABORTED == windowGetInput(add, formatString, recordStrings[currentChoiceAdd]) || strictInput )
    {
        if ( isUnicodeMultibyteString(recordStrings[currentChoiceAdd]) )
        {
            strcpy(recordStrings[currentChoiceAdd], "");
        }
        mvwprintw(add,
                  addLines / 4 + currentChoiceAdd ,
                  addCols / 4 + NORMAL_CHOICE_SIZE,
                  formatString,
                  recordStrings[currentChoiceAdd]);
    }
    noecho();
    curs_set(0);
}

int addKeypressHandler(int key)
{
    if (FIELD_COUNT == currentChoiceAdd)
    {
        toogleAddChoice(A_NORMAL, ADD_BUTTON_SIZE);
    }
    else
    {
        toogleAddChoice(A_NORMAL, NORMAL_CHOICE_SIZE);
    }
    
    switch (key)
    {
        case KEY_UP:
            if (currentChoiceAdd > 0)
            {
                currentChoiceAdd--;
            }
            else
            {
                return CONTINUE;
            }
            break;
        case KEY_DOWN:
            if (currentChoiceAdd < FIELD_COUNT)
            {
                currentChoiceAdd++;
                if (currentChoiceAdd == FIELD_COUNT)
                {
                    toogleAddChoice(A_REVERSE, ADD_BUTTON_SIZE);
                }
            }
            else
            {
                return CONTINUE;
            }
            break;
        case KEY_MAC_ENTER:
            if (FIELD_COUNT == currentChoiceAdd)
            {
                if ( noEmptyFields() )
                {
                    return ADD_RECORD;
                }
                break;
            }
            inputData();
            break;
        case KEY_ESC:
            return EXIT;
            break;
        default:
            break;
    }
    toogleAddChoice(A_REVERSE, NORMAL_CHOICE_SIZE);
    wrefresh(add);
    return CONTINUE;
}

void addNewMTRecord()
{
    bool exit = false;
    addLines = LINES;
    addCols  = COLS;
    add = newwin(addLines, addCols, 0, 0);
    currentChoiceAdd = 0;
    
    recordStringsAllock();
    
    wbkgd(add, COLOR_PAIR(2));
    
    for (int i = 0; i < FIELD_COUNT; i++)
    {
        wmove(add, addLines / 4 + i, addCols / 4);
        wprintw(add, "%s\n", fields[i]);
    }
    wmove(add, addLines / 4 + FIELD_COUNT, addCols / 4);
    wprintw(add, "%s\n", "                    ДОБАВИТЬ                         ");
    
    toogleAddChoice(A_REVERSE, NORMAL_CHOICE_SIZE);
    box(add, 0, 0);
    printHelp(ADD_HELP);
    wrefresh(add);
    while (!exit)
    {
        int result = addKeypressHandler( getch() );
        
        if (EXIT == result)
        {
            exit = true;
        }
        else if (ADD_RECORD == result)
        {
            struct MachineTime *newRecord = createRecord(recordStrings);
            addRecord(newRecord);
            printMessage("Запись Успешно Добавлена!");
            exit = true;
        }
    }
    windowRefreshAndClear(add);
    clear();
    refresh();
    delwin(add);
    
    
    freeArrayOfStrings(recordStrings, FIELD_COUNT);
    
}
