//
//  IMachineTime.c
//  courseWork
//
//  Created by Денис Кулиев on 12.10.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#include "IMachineTime.h"
#include <libproc.h>

char path[PATH_MAX];

void setExecutablePathAsWorkDir()
{
    char executablePath[PATH_MAX];
    pid_t pid = getpid();
    if ( 0 < proc_pidpath ( pid, executablePath, sizeof(executablePath) ) )
    {
        //to delete executable name from path
        for (long i = strlen(executablePath) - 1; i > 0; i-- )
        {
            if (executablePath[i] == '/')
            {
                executablePath[i] = '\0';
                break;
            }
            
        }
        chdir(executablePath);
    }
}

void startMenu()
{
    MENU parameters;
    initMenuParameters(&parameters, menuChoices , MENU_CHOICES_COUNT, call_function);
    setlocale(LC_ALL, "");
    
    init_menu();
    
    if ( FILE_LOADED != loadStruct(path) )
    {
        openFileMenu();
    }
    render_menu(parameters);
}

int loadStructTable(FILE **machineTimeFile)
{
    char *buffer;
    buffer = loadToBuffer(*machineTimeFile);
    
    return parseBuffer(buffer, TABLE_START_OFFSET);
}

int loadStruct(char *path)
{
    FILE *machineTimeFile = NULL;
    int type = getFileType(path);
    
    
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
            strcat(path, ".bin");
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
    //TODO lastPath ini
    setExecutablePathAsWorkDir();
    startMenu();
    freeStructMem();
}
