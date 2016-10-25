//
//  UnicodeMacOSLib.c
//  courseWork
//
//  Created by Денис Кулиев on 12.10.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#include "UnicodeMacOSLib.h"

int getBlockSize()
{
    struct stat fileSystem;
    stat("/", &fileSystem);
    return fileSystem.st_blksize;
}
bool isUTF8charBeginning(char c)
{
    if ( (c & 0xC0) != 0x80 )
    {
        return true;
    }
    else
    {
        return false;
    }
}

size_t utf8len(char *s)
{
    size_t length = 0;
    for (; *s != '\0'; s++)
    {
        //проверка не равны ли первые два бита кода 0b10 т.к все многобайтовые utf-8 коды которые начинаются с 0b10 являются продолжениями символов
        if ( isUTF8charBeginning(*s) )
        {
            length++;
        }
    }
    return length;
}

char *formatUtf8String(char *utf8string, const size_t formatLength)
{
    char *formatedString;
    size_t utf8StringLength = utf8len(utf8string);
    
    size_t spacesNumber = formatLength - utf8StringLength;
    
    size_t charLength = strlen(utf8string);
    size_t formatStringSize = charLength + spacesNumber + 1;
    
    formatedString = malloc(sizeof(char) * formatStringSize);
    
    for (size_t i = 0; i < spacesNumber; i++)
    {
        formatedString[i] = ' ';
    }
    
    for (size_t i = spacesNumber, j = 0; j < charLength; j++, i++)
    {
        formatedString[i] = utf8string[j];
    }
    
    formatedString[spacesNumber + charLength] = '\0';
    
    return formatedString;
}
