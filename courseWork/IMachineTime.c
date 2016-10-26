//
//  IMachineTime.c
//  courseWork
//
//  Created by Денис Кулиев on 12.10.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#include "IMachineTime.h"
#include "sortStruct.h"


void startMenu()
{
    setlocale(LC_ALL, "");
    
    init_menu();
    render_menu(0);
}


int loadStructTable(FILE **machineTimeFile)
{
    char *buffer;
    buffer = loadToBuffer(*machineTimeFile);
    
    return parseBuffer(buffer, TABLE_START_OFFSET);
}

int loadStruct(const char *path, short type)
{
    FILE *machineTimeFile = NULL;
    
    if ( loadFile(&machineTimeFile, path, MACHINE_FILE_HEADER) == FILE_LOADED)
    {
        if (TABLE_TYPE_FILE == type)
        {
            return loadStructTable(&machineTimeFile);
        }
        else if (BINARY_TYPE_FILE == type)
        {
            return loadBinary(&machineTimeFile);
        }
        else
        {
            return UNKNOWN_FILE_TYPE;
        }
    }
    else
    {
        return FILE_NOT_OPEN;
    }
}

void startProgram()
{
    loadStruct("/Users/deniskuliev/Library/Developer/Xcode/DerivedData/courseWork-csjasbpzgqmfwtcyokgaikxvneev/Build/Products/Debug/data.bin", BINARY_TYPE_FILE);
    sortStruct(sortByCafedraCode);
    startMenu();
    saveStruct("/Users/deniskuliev/Library/Developer/Xcode/DerivedData/courseWork-csjasbpzgqmfwtcyokgaikxvneev/Build/Products/Debug/data.test", TABLE_TYPE_FILE);
    
}



