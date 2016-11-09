//
//  searchSort.c
//  courseWork
//
//  Created by Денис Кулиев on 07.11.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#include "machineTime.h"

void updateSubstringPositionString(char *format ,char *pattern,char *whereToFind , int *position)
{
    char *tempString, *substring;
    bool tempStringAllocked = false;
    
    if ( strcmp(format, "%s") )
    {
        tempString = malloc(sizeof(char) * 20 );
        tempStringAllocked = true;
        sprintf(tempString, format, whereToFind);
    }
    else
    {
        tempString = whereToFind;
    }
    
    substring = strstr(tempString, pattern);
    
    if (NULL == substring)
    {
        *position = SUBSTRING_NOT_FOUND;
    }
    else
    {
        *position = (int) (substring - tempString);
    }
    
    if (tempStringAllocked)
    {
        free(tempString);
    }
    
}

void updateSubstringPositionInt(char *format ,char *pattern,const int whereToFind , int *position)
{
    char tempString[20], *substring;
    
    sprintf(tempString, format, whereToFind);
    substring = strstr(tempString, pattern);
    
    if (NULL == substring)
    {
        *position = SUBSTRING_NOT_FOUND;
    }
    else
    {
        *position = (int) (substring - tempString);
    }
    
}

int recordsFound;
bool searchSuccesfull;

void freeSearchResults(MTsearch *head)
{
    MTsearch *temp = head, *delete;
    while(temp != NULL)
    {
        delete = temp;
        temp = temp -> next;
        free(delete);
    }
}

int getRecordsFound()
{
    if (searchSuccesfull)
    {
        return recordsFound;
    }
    else
    {
        return SEARCH_FAILED;
    }
    
}

bool substringFound(SubstringPositions positions)
{
    return !( (SUBSTRING_NOT_FOUND == positions.cafedraCode) &&
              (SUBSTRING_NOT_FOUND == positions.cafedraName) &&
              (SUBSTRING_NOT_FOUND == positions.timePlanned) &&
              (SUBSTRING_NOT_FOUND == positions.timeSpent) );
}

SubstringPositions patternFound(struct MachineTime *record ,char *pattern)
{
    SubstringPositions positions;
    
    updateSubstringPositionString("%s", pattern, record -> cafedraName, &positions.cafedraName);
    updateSubstringPositionString("%11.11s", pattern, record -> cafedraCode, &positions.cafedraCode);
    updateSubstringPositionInt("%8d", pattern, record -> timeSpent.plan, &positions.timePlanned);
    updateSubstringPositionInt("%8d", pattern, record -> timeSpent.realLife, &positions.timeSpent);
    updateSubstringPositionInt("%10d", pattern, abs(record -> timeSpent.realLife - record -> timeSpent.plan), &positions.timeDifference);
    
    return positions;
}

MTsearch *searchInStruct(char *pattern)
{
    MTsearch *start , *searchTemp;
    struct MachineTime *temp = machineTimeBegining;
    
    searchSuccesfull = false;
    recordsFound = 0;
    start = searchTemp = NULL;
    while (NULL != temp)
    {
        SubstringPositions positions = patternFound(temp, pattern);
        if ( substringFound(positions) )
        {
            recordsFound++;
            if (NULL == start)
            {
                searchTemp = start = malloc( sizeof(MTsearch) );
                searchTemp -> previous = NULL;
                searchTemp -> next = NULL;
            }
            else
            {
                searchTemp -> next = malloc( sizeof(MTsearch) );
                searchTemp -> next -> previous = searchTemp;
                searchTemp = searchTemp -> next;
            }
            
            searchTemp -> data = temp;
            searchTemp -> positions = positions;
            searchTemp -> next = NULL;
        }
        temp = temp -> next;
    }
    searchSuccesfull = true;
    return start;
}
