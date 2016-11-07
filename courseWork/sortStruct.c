//
//  sortStruct.c
//  courseWork
//
//  Created by Денис Кулиев on 24.10.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#include "sortStruct.h"
#include "machineTimeStruct.h"

bool sortByCafedraCode(struct MachineTime *a, struct MachineTime *b)
{
    return (strcmp(a -> cafedraCode, b -> cafedraCode) > 0);
    
}

bool sortByCafedraName(struct MachineTime *a, struct MachineTime *b)
{
    return (strcmp(a -> cafedraName, b -> cafedraName) > 0);
}

bool sortByTimePlanned (struct MachineTime *a, struct MachineTime *b)
{
    return ( (a -> timeSpent.plan) > (b -> timeSpent.plan) );
    
}

bool sortByTimeSpent (struct MachineTime *a, struct MachineTime *b)
{
    return ( (a -> timeSpent.realLife) > (b -> timeSpent.realLife) );
    
}

bool sortByDifference (struct MachineTime *a, struct MachineTime *b)
{
    int differenceA = abs( (a -> timeSpent.plan) - (a -> timeSpent.realLife) );
    int differenceB = abs( (b -> timeSpent.plan) - (b -> timeSpent.realLife) );
    
    return differenceA > differenceB;
}

bool sortByCafedraCodeDescending(struct MachineTime *a, struct MachineTime *b)
{
    return (strcmp(a -> cafedraCode, b -> cafedraCode) < 0);
    
}

bool sortByCafedraNameDescending(struct MachineTime *a, struct MachineTime *b)
{
    return (strcmp(a -> cafedraName, b -> cafedraName) < 0);
}

bool sortByTimePlannedDescending (struct MachineTime *a, struct MachineTime *b)
{
    return ( (a -> timeSpent.plan) < (b -> timeSpent.plan) );
    
}

bool sortByTimeSpentDescending (struct MachineTime *a, struct MachineTime *b)
{
    return ( (a -> timeSpent.realLife) < (b -> timeSpent.realLife) );
    
}

bool sortByDifferenceDescending (struct MachineTime *a, struct MachineTime *b)
{
    int differenceA = abs( (a -> timeSpent.plan) - (a -> timeSpent.realLife) );
    int differenceB = abs( (b -> timeSpent.plan) - (b -> timeSpent.realLife) );
    
    return differenceA < differenceB;
}



void swapElements(struct MachineTime *current, struct MachineTime *next)
{
    bool updateBegining = false,updateEnding = false;
    if (NULL != current -> previous)
    {
        current -> previous -> next = next;
    }
    else
    {
        updateBegining = true;
    }
    
    if (NULL != next -> next)
    {
        next -> next -> previous = current;
    }
    else
    {
        updateEnding = true;
    }
    
    current -> next = next -> next;
    next -> previous = current -> previous;
    
    next -> next = current;
    current -> previous = next;
    
    if (updateBegining)
    {
        machineTimeBegining = next;
    }
    if (updateEnding)
    {
        machineTimeEnding = current;
    }
}

void sortStruct(bool (*sortFunction)(struct MachineTime *, struct MachineTime *))
{
    struct MachineTime *temp = machineTimeBegining;
    if (machineTimeEnding == machineTimeBegining)
    {
        return;
    }
    while (NULL != temp)
    {
        if (NULL == temp -> next)
        {
            break;
        }
        if ( sortFunction(temp, temp -> next) )
        {
            swapElements(temp, temp -> next);
            temp = machineTimeBegining;
            continue;
        }
        temp = temp -> next;
    }
}
