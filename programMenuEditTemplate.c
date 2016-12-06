#include "programMenuEditTemplate.h"

int currentChoice;
int currentField;
int choicesNumber;
void *currentChoicePointer;
bool somethingDeleted;

EditArguments initEditStructArguments(void *(*getNextItem)(void*),
                                      void *(*getPreviousItem)(void*),
                                      bool (*deleteSelectedItem)(),
                                      void (*printTable)(int),
                                      struct MachineTime *(*getCurrentChoiceRecord)(void*),
                                      int choicesNumber,
                                      void *start)
{
    EditArguments arguments;
    
    arguments.getPreviousItem        = getPreviousItem;
    arguments.getNextItem            = getNextItem;
    arguments.deleteSelectedItem     = deleteSelectedItem;
    arguments.printTable             = printTable;
    arguments.getCurrentChoiceRecord = getCurrentChoiceRecord;
    arguments.choicesNumber          = choicesNumber;
    arguments.start                  = start;
    
    return arguments;
}

void toogleChoice(WINDOW *win, int choice,int type)
{
    mvwchgat(win, choice + TABLE_HEAD_SIZE, 1, TABLE_CHOICE_WIDTH, type, MAIN_THEME_COLOR_PAIR, NULL);
    wmove(table, 0, 0);
}

void moveCursorDown(WINDOW *win,void *(*getNextItem)(void *))
{
    if (currentChoice >= choicesNumber)
    {
        currentChoice = choicesNumber;
    }
    else
    {
        toogleChoice(win, currentChoice, A_NORMAL);
        currentChoicePointer = getNextItem(currentChoicePointer);
        currentChoice++;
    }
}

void moveCursorUp(WINDOW *win, void *(*getPreviousItem)(void *))
{
    if (currentChoice <= 0)
    {
        currentChoice = 0;
    }
    else
    {
        toogleChoice(win, currentChoice, A_NORMAL);
        currentChoicePointer = getPreviousItem(currentChoicePointer);
        currentChoice--;
    }
}

bool editKeypressHandler(WINDOW *win, EditArguments arguments)
{
    int key = getch();
    
    switch (key)
    {
        case KEY_DOWN:
            moveCursorDown(win, arguments.getNextItem);
            break;
        case KEY_UP:
            moveCursorUp(win, arguments.getPreviousItem);
            break;
        case KEY_MAC_ENTER:
            editRecord(win, arguments);
            break;
        case MAC_BACKSPACE:
            return arguments.deleteSelectedItem();
            break;
        case KEY_ESC:
            return EXIT;
            break;
        default:
            break;
    }
    return CONTINUE;
}

void editStruct(WINDOW *win, EditArguments arguments)
{
    currentChoice = 0;
    currentChoicePointer = arguments.start;
    choicesNumber = arguments.choicesNumber;
    somethingDeleted = false;
    
    do
    {
        if (controlsLocked)
        {
            break;
        }
        
        if (somethingDeleted)
        {
            wclear(win);
            somethingDeleted = false;
        }
        
        arguments.printTable(HELP_EDIT_MODE);
        toogleChoice(win, currentChoice, A_REVERSE);
        wrefresh(win);
    } while ( EXIT != editKeypressHandler(win, arguments) );
    
    toogleChoice(win, currentChoice, A_NORMAL);
}
