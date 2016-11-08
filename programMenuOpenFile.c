//
//  OpenFile.c
//  courseWork
//
//  Created by Денис Кулиев on 08.11.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#include "programMenu.h"
#include <sys/syslimits.h>

void openFileMenu()
{
    if ( getUserInputDialog("Введите путь у файлу", path) )
    {
        if ( FILE_LOADED == loadStruct(path) )
        {
            printMessage("Файл загружен успешно!");
        }
        else
        {
            printMessage("Файл будет создан/перезаписан");
        }
    }
}
