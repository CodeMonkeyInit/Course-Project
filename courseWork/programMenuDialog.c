#include "programMenu.h"

const int inputFieldOffsetX = 3;
const int inputFieldOffsetY = DIALOG_HEIGHT - 5;

char *userInput;

void getUserInput(WINDOW *win, int offsetY, int offsetX, bool *inputSuccess)
{
    char format[10];
    
    wattron(win, A_REVERSE | A_BOLD | COLOR_PAIR(ACTIVE_INPUT_COLOR_PAIR));
    
    sprintf(format , "%%-%ds", INPUT_FIELD_LENGTH);
    mvwprintw(win, offsetY, offsetX, format, " ");
    
    curs_set(1);
    wmove(win, offsetY, offsetX + 1);
    sprintf(format , "%%-%ds", TEXT_FIELD_LENGTH);
    
    if ( INPUT_ABORTED != windowGetInput(win, format, userInput) )
    {
        *inputSuccess = true;
    }
    else
    {
        *inputSuccess = false;
        wmove(win, inputFieldOffsetY, inputFieldOffsetX);
        wprintw(win, format, userInput);
        
        mvwchgat(win, inputFieldOffsetY, inputFieldOffsetX , INPUT_FIELD_LENGTH , A_REVERSE, MAIN_THEME_COLOR_PAIR, NULL);
        wrefresh(win);
    }
    
    wattroff(win, A_REVERSE | A_BOLD | COLOR_PAIR(ACTIVE_INPUT_COLOR_PAIR));
    
    curs_set(0);
}

bool dialogKeypressHandeler(WINDOW *dialog, bool *inputSuccess, int *currentChoice)
{
    int key = getch();
    
    switch (key)
    {
        case KEY_UP:
        case KEY_DOWN:
            
            if (CHOICE_OK_BUTTON == *currentChoice)
            {
                *currentChoice = CHOICE_INPUT_FIELD;
            }
            else
            {
                *currentChoice = CHOICE_OK_BUTTON;
            }
            break;
            
        case KEY_MAC_ENTER:
            
            if ( (*currentChoice) == CHOICE_INPUT_FIELD )
            {
                getUserInput(dialog, inputFieldOffsetY, inputFieldOffsetX, inputSuccess);
            }
            else
            {
                *inputSuccess = true;
                return EXIT;
            }
            break;
        case KEY_ESC:
            *inputSuccess = false;
            return EXIT;
            break;
        default:
            break;
    }
    return CONTINUE;
}

bool getUserInputDialog(char *message, char *response)
{
    WINDOW *dialog = NULL;
    int offsetX = (COLS - DIALOG_WIDTH) / 2;
    int offsetY = (LINES - DIALOG_HEIGHT) / 2;
    bool inputSuccess = false;
    int currentChoice = CHOICE_INPUT_FIELD;
    clear();
    refresh();
    
    dialog = newwin(DIALOG_HEIGHT,
                    DIALOG_WIDTH,
                    offsetY,
                    offsetX);
    
    userInput = calloc( (DIALOG_WIDTH - 2) * 4, sizeof(char) );
    
    do
    {
        if ( refreshIfNeeded() )
        {
            offsetX = (COLS - DIALOG_WIDTH) / 2;
            offsetY = (LINES - DIALOG_HEIGHT) / 2;
            mvwin(dialog, offsetY, offsetX);
            
        }
        
        int buttonOffsetX = getStringMiddlePostition(OK_BUTTON, DIALOG_WIDTH);
        int buttonOffsetY = DIALOG_HEIGHT - 3;
        
        printHelp(stdscr, DIALOG_HELP);
        
        wbkgd(dialog, COLOR_PAIR(2));
        mvwprintw(dialog, 3, 3, "%s", message);
        mvwprintw(dialog, buttonOffsetY, buttonOffsetX, "%s", OK_BUTTON);
        if (currentChoice == CHOICE_OK_BUTTON)
        {
            mvwchgat(dialog, buttonOffsetY, buttonOffsetX - 2 , utf8len(OK_BUTTON) + 4 , A_REVERSE, MAIN_THEME_COLOR_PAIR, NULL);
        }
        else
        {
            mvwchgat(dialog, inputFieldOffsetY, inputFieldOffsetX , DIALOG_WIDTH - 6 , A_REVERSE, MAIN_THEME_COLOR_PAIR, NULL);
        }
        
        wrefresh(dialog);
        refresh();
    } while ( EXIT != dialogKeypressHandeler(dialog ,&inputSuccess, &currentChoice) );
    
    if (inputSuccess)
    {
        strcpy(response, userInput);
    }
    free(userInput);
    delwin(dialog);
    clear();
    return inputSuccess;
}
