//
//  IMachineTime.h
//  courseWork
//
//  Created by Денис Кулиев on 12.10.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#ifndef IMachineTime_h
#define IMachineTime_h

#include "machineTime.h"
#include "programMenu.h"
#include <stdbool.h>
#include <locale.h>
#include <sys/syslimits.h>

#define TABLE_START_OFFSET 351
#define saveStruct(path) saveFile(path)
#define DEFAULT_PATH "/Users/deniskuliev/Library/Developer/Xcode/DerivedData/courseWork-csjasbpzgqmfwtcyokgaikxvneev/Build/Products/Debug/data.table"

extern char path[PATH_MAX];

int loadStruct(char * path);
void startProgram();
void saveFilePathToSettingsFile();

#endif /* IMachineTime_h */
