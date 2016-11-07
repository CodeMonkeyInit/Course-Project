//
//  searchSort.c
//  courseWork
//
//  Created by Денис Кулиев on 07.11.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#include "searchInStruct.h"

int recordsFound;
bool searchSuccesfull;

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
    char timePlanned[10], timeUsed[10];
    char *substring;
    
    substring = strstr(record -> cafedraCode, pattern);
    if (NULL == substring)
    {
        positions.cafedraCode = SUBSTRING_NOT_FOUND;
    }
    else
    {
        positions.cafedraCode = (int) (substring - record -> cafedraCode);
    }
    
    substring = strstr(record -> cafedraName, pattern);
    if (NULL == substring)
    {
        positions.cafedraName = SUBSTRING_NOT_FOUND;
    }
    else
    {
        positions.cafedraName = (int) (substring - record -> cafedraName);
    }
    sprintf(timePlanned, "%d", record -> timeSpent.plan);
    sprintf(timeUsed, "%d", record -> timeSpent.realLife);
    
    substring = strstr(timePlanned, pattern);
    if (NULL == substring)
    {
        positions.timePlanned = SUBSTRING_NOT_FOUND;
    }
    else
    {
        positions.timePlanned = (int) (substring - timePlanned);
    }
    
    substring = strstr(timeUsed, pattern);
    if (NULL == substring)
    {
        positions.timeSpent = SUBSTRING_NOT_FOUND;
    }
    else
    {
        positions.timeSpent = (int) (substring - timeUsed);
    }
    
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
