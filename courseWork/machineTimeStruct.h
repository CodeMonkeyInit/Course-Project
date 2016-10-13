//
//  machineTimeStruct.h
//  courseWork
//
//  Created by Денис Кулиев on 13.10.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#ifndef machineTimeStruct_h
#define machineTimeStruct_h

struct TimeSpent
{
    int plan;
    int realLife;
};

struct MachineTime
{
    char cafedraCode[6];
    char cafedraName[40];
    struct TimeSpent timeSpent;
    struct MachineTime *previous;
    struct MachineTime *next;
};

extern struct MachineTime *machineTimeBegining,*machineTimeEnding;

#endif /* machineTimeStruct_h */
