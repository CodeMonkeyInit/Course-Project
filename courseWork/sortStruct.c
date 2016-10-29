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
    if ( strcmp(a -> cafedraCode, b -> cafedraCode) > 0 )
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool sortByCafedraName(struct MachineTime *a, struct MachineTime *b)
{
    if ( strcmp(a -> cafedraName, b -> cafedraName) > 0 )
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool sortByTimePlanned (struct MachineTime *a, struct MachineTime *b)
{
    if ( a -> timeSpent.plan > b -> timeSpent.plan)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool sortByTimeSpent (struct MachineTime *a, struct MachineTime *b)
{
    if ( a -> timeSpent.realLife > b -> timeSpent.realLife)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool sortByDifference (struct MachineTime *a, struct MachineTime *b)
{
    int differenceA = abs( (a -> timeSpent.plan) - (b -> timeSpent.realLife) );
    int differenceB = abs( (a -> timeSpent.plan) - (b -> timeSpent.realLife) );
    
    if (differenceA > differenceB)
    {
        return true;
    }
    else
    {
        return false;
    }
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
