#include "machineTime.h"

int recordsFound;
bool searchSuccesfull;

void updateSubstringPositionString(char *format ,char *pattern,char *whereToFind , int *position)
{
    const int HAYSTACK_MAX_SIZE = 81;
    char *tempHaystackString, *substring;
    bool tempStringAllocked = false;
    
    if ( strcmp(format, "%s") )
    {
        tempHaystackString = malloc(sizeof(char) * HAYSTACK_MAX_SIZE);
        tempStringAllocked = true;
        sprintf(tempHaystackString, format, whereToFind);
    }
    else
    {
        tempHaystackString = whereToFind;
    }
    
    substring = strstr(tempHaystackString, pattern);
    
    if (NULL == substring)
    {
        *position = SUBSTRING_NOT_FOUND;
    }
    else
    {
        int tempPosition = (int) (substring - tempHaystackString);
        *position = getUtf8Index(tempHaystackString, tempPosition);
    }
    
    if (tempStringAllocked)
    {
        free(tempHaystackString);
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
