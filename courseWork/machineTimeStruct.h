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
    char cafedraName[81];
    struct TimeSpent timeSpent;
    struct MachineTime *previous;
    struct MachineTime *next;
};

extern struct MachineTime *machineTimeBegining,*machineTimeEnding;

#endif /* machineTimeStruct_h */
