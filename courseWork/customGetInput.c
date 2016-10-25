//
//  customGetInput.c
//  courseWork
//
//  Created by Денис Кулиев on 24.10.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#include "customGetInput.h"

void deleteBackspace(WINDOW *win)
{
    int currentX = getcurx(win);
    int currentY = getcury(win);
    mvwprintw(win,currentY, currentX - BACKSPACE_AND_CHARACTER, "   ");
    wrefresh(win);
    wmove(win, currentY, currentX - BACKSPACE_AND_CHARACTER);
}

int getString(WINDOW *win, int length,char *string)
{
    if (length == 0)
    {
        length = 0xFFFFFFF;
    }
    
    int i;
    int key;
    int utfLength = length * 2;
    int utfCurrentLength = 0;
    
    char *tempString = (char *) calloc(utfLength + 1, sizeof(char) );
    
    for(i = 0; i < utfLength ; i++)
    {
        key = wgetch(win);
        tempString[i] = key;
        if (KEY_MAC_ENTER == key)
        {
            break;
        }
        else if ( KEY_ESC == key)
        {
            return INPUT_ABORTED;
        }
        else if ( MAC_BACKSPACE == key )
        {
            i -= 2;
            // i+1 to capture deleting symbol
            while ( !isUTF8charBeginning(tempString[i + 1]) )
            {
                i--;
            }
            deleteBackspace(win);
            continue;
        }
        if ( isUTF8charBeginning(key) )
        {
            utfCurrentLength++;
            if (utfCurrentLength > length)
            {
                break;
            }
        }
    }
    tempString[i] = '\0';
    strcpy(string, tempString);
    free(tempString);
    
    return 0;
}

int getNumeric(WINDOW *win, int *numberToRead ,int length)
{
    char temp[length * 4];
    if ( INPUT_ABORTED == getString(win, length, temp) )
    {
        return INPUT_ABORTED;
    }
    else
    {
        *numberToRead = atoi(temp);
    }
    return 0;
}

int getType(char c)
{
    switch (c)
    {
        case 'd':
            return INT_TYPE;
            break;
        case 's':
            return STRING_TYPE;
        case 'c':
            return CHAR_TYPE;
        default:
            return WRONG_TYPE;
            break;
    }
}

int parseFormat(const char *format, int *argument)
{
    int formatLength = (int) strlen(format);
    int i = 0;
    
    if (formatLength < 2)
    {
        return WRONG_FORMAT;
    }
    
    
    if ('%' == format[i])
    {
        char lengthString[4];
        int j;
        // inc i to skip '%'
        for (j = 0, i++; isdigit(format[i]) ; j++,i++)
        {
            lengthString[j] = format[i];
        }
        
        if (1 != i)
        {
            lengthString [++j] = '\0';
            argument[ARGUMENT_LENGTH] = atoi(lengthString);
        }
        else
        {
            argument[ARGUMENT_LENGTH] = UNKNOWN_LENGTH;
        }
        
        argument[ARGUMENT_TYPE] = getType(format[i]);
        
        if (argument[ARGUMENT_TYPE] == WRONG_TYPE)
        {
            return WRONG_FORMAT;
        }
    }
    else
    {
        return WRONG_FORMAT;
    }
    
    return 0;
}

int windowGetInput(WINDOW *win,char *format,...)
{
    int argument[2];
    
    va_list variableArguments;
    va_start(variableArguments, format);
    
    int inputResult;
    
    if ( WRONG_FORMAT == parseFormat(format, argument) )
    {
        return WRONG_FORMAT;
    }
    else
    {
        char *inputString;
        int *inputInt;
        switch (argument[ARGUMENT_TYPE])
        {
            case STRING_TYPE:
                inputString = va_arg(variableArguments, char*);
                inputResult = getString(win, argument[ARGUMENT_LENGTH], inputString);
                break;
            case INT_TYPE:
                inputInt = va_arg(variableArguments, int*);
                inputResult = getNumeric(win, inputInt, argument[ARGUMENT_LENGTH]);
                break;
            default:
                break;
        }
    }
    va_end(variableArguments);
    
    return inputResult;
}
