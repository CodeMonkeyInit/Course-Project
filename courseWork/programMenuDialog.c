//
//  programMenuDialog.c
//  courseWork
//
//  Created by Денис Кулиев on 07.11.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#include "programMenu.h"

const int inputFieldOffsetX = 1;
const int inputFieldOffsetY = DIALOG_HEIGHT - 5;

char *userInput;

void getUserInput(WINDOW *win, int offsetY, int offsetX, bool *inputSuccess)
{
    char format[10];
    sprintf(format, "%%%ds", DIALOG_WIDTH - 2);
    
    curs_set(1);
    echo();
    mvwprintw(win, offsetY, offsetX, format, " ");
    wmove(win, offsetY, offsetX);
    if ( INPUT_ABORTED != windowGetInput(win, format, userInput) )
    {
        *inputSuccess = true;
    }
    else
    {
        *inputSuccess = false;
        wmove(win, inputFieldOffsetY, inputFieldOffsetX);
        wprintw(win, "%50s", userInput);
    }
    curs_set(0);
    noecho();
}

bool dialogKeypressHandeler(WINDOW *dialog, bool *inputSuccess, int *currentChoice)
{
    int key = getch();
    
    switch (key)
    {
        case KEY_UP:case KEY_DOWN:
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
            inputSuccess = false;
            return EXIT;
            break;
        default:
            break;
    }
    return CONTINUE;
}

bool getUserInputDialog(char *message, char *response)
{
    WINDOW *dialog;
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
        
        printHelp(DIALOG_HELP);
        
        box(dialog, 0, 0);
        wbkgd(dialog, COLOR_PAIR(2));
        mvwprintw(dialog, 3, 3, "%s", message);
        mvwprintw(dialog, buttonOffsetY, buttonOffsetX, "%s", OK_BUTTON);
        if (currentChoice == CHOICE_OK_BUTTON)
        {
            mvwchgat(dialog, buttonOffsetY, buttonOffsetX - 2 , utf8len(OK_BUTTON) + 4 , A_REVERSE, 2, NULL);
        }
        else
        {
            mvwchgat(dialog, inputFieldOffsetY, inputFieldOffsetX , DIALOG_WIDTH - 2 , A_REVERSE, 2, NULL);
        }
        
        wrefresh(dialog);
        refresh();
    } while ( EXIT != dialogKeypressHandeler(dialog ,&inputSuccess, &currentChoice) );
    
    if (inputSuccess)
    {
        strcpy(response, userInput);
    }
    free(userInput);
    
    wclear(dialog);
    delwin(dialog);
    clear();
    refresh();
    return inputSuccess;
}
