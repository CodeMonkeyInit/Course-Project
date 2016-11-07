//
//  sortStruct.h
//  courseWork
//
//  Created by Денис Кулиев on 24.10.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#ifndef sortStruct_h
#define sortStruct_h

#include <stdio.h>
#include "machineTime.h"

bool sortByCafedraCode (struct MachineTime *a, struct MachineTime *b);
bool sortByCafedraName (struct MachineTime *a, struct MachineTime *b);
bool sortByTimePlanned (struct MachineTime *a, struct MachineTime *b);
bool sortByTimeSpent (struct MachineTime *a, struct MachineTime *b);
bool sortByDifference (struct MachineTime *a, struct MachineTime *b);
bool sortByCafedraCodeDescending (struct MachineTime *a, struct MachineTime *b);
bool sortByCafedraNameDescending (struct MachineTime *a, struct MachineTime *b);
bool sortByTimePlannedDescending (struct MachineTime *a, struct MachineTime *b);
bool sortByTimeSpentDescending (struct MachineTime *a, struct MachineTime *b);
bool sortByDifferenceDescending (struct MachineTime *a, struct MachineTime *b);
void sortStruct(bool (*sortFunction)(struct MachineTime *, struct MachineTime *));

#endif /* sortStruct_h */
