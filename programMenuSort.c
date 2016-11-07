//
//  programMenuSort.c
//  courseWork
//
//  Created by Денис Кулиев on 06.11.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#include "programMenuSort.h"

const char *sortChoices[] =
{
    "СОРТИРОВКА",
    "По коду кафедры",
    "По названию кафедры",
    "По запланированным часам",
    "По использованным часам",
    "По отклонению"
};
const int sortChoicesCount = 6;

void sortCallFunction(int function)
{
    printTypeSortMenu(function);
}

void printSortMenu()
{
    MENU arguments;
    initMenuParameters(&arguments, sortChoices, sortChoicesCount, sortCallFunction);
    
    render_menu(arguments);
}
