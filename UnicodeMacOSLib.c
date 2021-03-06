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
    // Получение размера блока на диске
    struct stat fileSystem;
    stat("/", &fileSystem);
    return fileSystem.st_blksize;
}

int getUtf8Index(char* utfString, int charIndex)
{
    int utfIndex, i;
    
    for (utfIndex = 0, i = 0; i < charIndex; utfString++, i++)
    {
        if ( isUTF8charBeginning(*utfString) )
        {
            utfIndex++;
        }
    }
    
    return utfIndex;
}

bool isDigitOnly(char *string)
{
    while('\0' != *string)
    {
        if ( !isdigit(*string++) )
        {
            return false;
        }
    }
    
    return true;
}

bool isUnicodeMultibyteString(const char *string)
{
    return utf8len(string) != strlen(string);
}

bool isUTF8charBeginning(char c)
{
    //проверка не равны ли первые два бита кода 0b10 т.к все многобайтовые utf-8 коды которые начинаются с 0b10 являются продолжениями символов
    if ( (c & 0xC0) != 0x80 )
    {
        return true;
    }
    else
    {
        return false;
    }
}

size_t utf8len(const char *s)
{
    size_t length = 0;
    for (; *s != '\0'; s++)
    {
        if ( isUTF8charBeginning(*s) )
        {
            length++;
        }
    }
    return length;
}

// добавляет пробелы впереди слова для имитации форматирования
char *formatUtf8String(char *utf8string, const size_t formatLength)
{
    char *formatedString;
    size_t utf8StringLength = utf8len(utf8string);
    
    long spacesNumber = labs( (long)formatLength - (long)utf8StringLength );
    
    size_t charLength = strlen(utf8string);
    size_t formatStringSize = charLength * 4  + spacesNumber + 1;
    
    formatedString =(char*) malloc(sizeof(char) * formatStringSize);
    
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
