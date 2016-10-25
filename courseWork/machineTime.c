#include "machineTimeStruct.h"
#include "machineTime.h"

struct MachineTime *machineTimeBegining = NULL,*machineTimeEnding = NULL;

void addRecord(struct MachineTime *record)
{
    if(NULL == machineTimeBegining)
    {
        machineTimeEnding = machineTimeBegining = record;
    }
    else
    {
        record -> previous = machineTimeEnding;
        machineTimeEnding -> next = record;
        machineTimeEnding = machineTimeEnding -> next;
    }
    return;
}

struct MachineTime *createRecord(char **recordStrings)
{
    // TODO free mem
    struct MachineTime *newRecord = (struct MachineTime*) malloc(sizeof(struct MachineTime));

    strcpy(newRecord -> cafedraCode, recordStrings[CAFEDRA_CODE]);
    strcpy(newRecord -> cafedraName, recordStrings[CAFEDRA_NAME]);
    
    newRecord -> timeSpent.plan = atoi(recordStrings[TIME_PLANNED]);
    newRecord -> timeSpent.realLife = atoi(recordStrings[TIME_USED]);
    
    newRecord -> next = NULL;
    newRecord -> previous = NULL;
    
    return newRecord;
}

int deleteRecord(struct MachineTime **record)
{
    struct MachineTime *deleting = *record,
                       *previous = deleting -> previous,
                       *next = deleting -> next;
    int position;
    
    if ( (NULL == previous) && (NULL == next)  )
    {
        machineTimeEnding = machineTimeBegining = *record = NULL;
        position = EMPTY;
    }
    else if (NULL == next)
    {
        machineTimeEnding = *record = previous;
        (*record) -> next = NULL;
        position = ENDING;
    }
    else if (NULL == previous)
    {
        machineTimeBegining = *record = next;
        (*record) -> previous = NULL;
        position = BEGINING;
    }
    else
    {
        *record = next;
        (*record) -> previous = deleting -> previous;
        previous -> next = *record;
        position = MIDDLE;
    }
    free(deleting);
    return position;
}
