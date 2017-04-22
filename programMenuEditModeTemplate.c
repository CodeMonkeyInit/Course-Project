#include "programMenuEditTemplate.h"

bool somethingChanged;

//получить отступ по оси X для текущего поля
int getOffsetX()
{
    switch (currentField)
    {
        case CAFEDRA_CODE:
            
            return CAFEDRA_CODE_TABLE_OFFSET;
        
        case CAFEDRA_NAME:
            
            return CAFEDRA_NAME_TABLE_OFFSET;
            
        case TABLE_TIME_PLANNED:
            
            return TIME_PLANNED_TABLE_OFFSET;
        
        case TABLE_TIME_USED:
            
            return TIME_USED_TABLE_OFFSET;
            
        default:
            break;
    }
    return -1;
}

// ввод времени
int getTimeFromUser(WINDOW *win , int offsetY, int offsetX, bool *success)
{
    int time;
    mvwprintw(win,offsetY,offsetX, "%8s", " ");
    wmove(win, offsetY, offsetX);
    if ( INPUT_ABORTED == windowGetInput(win, "%8d", &time) )
    {
        
        *success = false;
        return INPUT_ABORTED;
    }
    else
    {
        *success = true;
        return time;
    }
}

void toogleChoiceField(WINDOW *win, int field, int type)
{
    switch (field)
    {
        case CAFEDRA_CODE:
            mvwchgat(win,
                     currentChoice + TABLE_HEAD_SIZE,
                     CAFEDRA_CODE_TABLE_OFFSET,
                     CAFEDRA_CODE_LENGTH , type,
                     MAIN_THEME_COLOR_PAIR,
                     NULL);
            break;
        case CAFEDRA_NAME:
            mvwchgat(win,
                     currentChoice + TABLE_HEAD_SIZE,
                     CAFEDRA_NAME_TABLE_OFFSET,
                     CAFEDRA_NAME_FORMAT_LENGTH , type,
                     MAIN_THEME_COLOR_PAIR,
                     NULL);
            break;
        case TABLE_TIME_PLANNED:
            mvwchgat(win,
                     currentChoice + TABLE_HEAD_SIZE,
                     TIME_PLANNED_TABLE_OFFSET,
                     TIME_LENGTH , type,
                     MAIN_THEME_COLOR_PAIR,
                     NULL);
            break;
        case TABLE_TIME_USED:
            mvwchgat(win,
                     currentChoice + TABLE_HEAD_SIZE,
                     TIME_USED_TABLE_OFFSET,
                     TIME_LENGTH , type,
                     MAIN_THEME_COLOR_PAIR,
                     NULL);
            break;
        default:
            break;
    }
    wmove(win, 0, 0);
}

void timeInput(WINDOW *win, int offsetY, int offsetX, struct MachineTime *edit)
{
    bool timeInputSuccess;
    
    int time = getTimeFromUser(win, offsetY, offsetX, &timeInputSuccess);
    
    if (timeInputSuccess)
    {
        somethingChanged = true;
        unsavedChangesExist = true;
        
        if (TABLE_TIME_USED == currentField)
        {
            edit -> timeSpent.realLife = time;
        }
        else if (TABLE_TIME_PLANNED == currentField)
        {
            edit -> timeSpent.plan = time;
        }
    }
}

void textInput(WINDOW *win, int offsetY, int offsetX, struct MachineTime *edit, char *printFormat, char *inputFormat)
{
    const int TEMP_STRING_MAX_SIZE = 81;
    char tempString[TEMP_STRING_MAX_SIZE];
    wmove(win, offsetY, offsetX);
    wprintw(win, printFormat, " ");
    wmove(win, offsetY, offsetX);
    
    if ( INPUT_ABORTED != windowGetInput(win, inputFormat, tempString) )
    {
        // если строка не многобайтовая(не содержит русских символов
        if ( (CAFEDRA_CODE == currentField) && !isUnicodeMultibyteString(tempString) )
        {
            strcpy(edit -> cafedraCode, tempString);
            somethingChanged = true;
            unsavedChangesExist = true;
        }
        else if ( CAFEDRA_NAME == currentField )
        {
            char *tempFormatString = formatUtf8String(tempString, CAFEDRA_NAME_FORMAT_LENGTH);
            strcpy(edit -> cafedraName, tempFormatString);
            free(tempFormatString);
            somethingChanged = true;
            unsavedChangesExist = true;
        }
    }
}

void editMode(WINDOW *win, struct MachineTime *edit)
{
    const int MAX_FORMAT_SIZE = 10;
    
    char inputFormat[MAX_FORMAT_SIZE];
    char *printFormat = inputFormat;
    
    bool digitInput = false;
    bool printFormatWasAllocked = false;
    
    int offsetY = currentChoice + TABLE_HEAD_SIZE;
    int offsetX = getOffsetX();
    
    wattron( win, COLOR_PAIR(MAIN_THEME_COLOR_PAIR) );
    curs_set(1);
    
    switch (currentField)
    {
        case CAFEDRA_CODE:
            
            printFormatWasAllocked = true;
            printFormat = malloc(sizeof(char) * MAX_FORMAT_SIZE);
            strcpy(printFormat, "%11s");
            strcpy(inputFormat, "%5s");
            break;
            
        case CAFEDRA_NAME:
            
            strcpy(inputFormat, "%20s");
            break;
        
        case TABLE_TIME_USED:
        case TABLE_TIME_PLANNED:
            
            digitInput = true;
            
        default:
            break;
    }
    
    if (digitInput)
    {
        timeInput(win, offsetY, offsetX, edit);
    }
    else
    {
        textInput(win, offsetY, offsetX, edit, printFormat, inputFormat);
    }
    
    if (printFormatWasAllocked)
    {
        free(printFormat);
    }
    
    curs_set(0);
    somethingChanged = true;
    wattroff( win, COLOR_PAIR(MAIN_THEME_COLOR_PAIR) );
    wrefresh(win);
}

bool editRecordKeypressHandler(WINDOW *win, EditArguments arguments)
{
    int key = getch();
    toogleChoiceField(win, currentField, A_NORMAL);
    
    switch (key)
    {
        case KEY_DOWN:
            
            moveCursorDown(win, arguments.getNextItem);
            break;
            
        case KEY_UP:
            
            moveCursorUp(win, arguments.getPreviousItem);
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
            editMode( win, arguments.getCurrentChoiceRecord(currentChoicePointer) );
            somethingChanged = true;
            break;
        case MAC_BACKSPACE:
            somethingDeleted = true;
            return arguments.deleteSelectedItem();
            break;
        case KEY_ESC:
            return EXIT;
        default:
            break;
    }
    
    toogleChoiceField(win, currentField, A_REVERSE);
    wrefresh(win);
    return CONTINUE;
}

void editRecord(WINDOW *win, EditArguments arguments)
{
    somethingDeleted = somethingChanged = false;
    currentField = 0;
    
    toogleChoice(win, currentChoice, A_NORMAL);
    toogleChoiceField(win, currentField, A_REVERSE);
    wrefresh(win);
    
    while ( EXIT != editRecordKeypressHandler(win, arguments) )
    {
        if (somethingDeleted)
        {
            wclear(win);
            somethingDeleted = false;
            somethingChanged = true;
        }
        
        if (somethingChanged)
        {
            arguments.printTable(HELP_EDIT_MODE);
            toogleChoiceField(win, currentField, A_REVERSE);
            wrefresh(win);
            somethingChanged = false;
        }
    }
}
