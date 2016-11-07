//
//  programMenuSortChooseType.c
//  courseWork
//
//  Created by Денис Кулиев on 07.11.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#include "programMenuSortChooseType.h"

const char *sortTypeChoices[] =
{
    "СОРТИРОВКА",
    "По возростанию",
    "По убыванию"
};
const int sortTypeChoicesCount = 3;

bool sort;

void sortTypeCallFunction(int function)
{
    sort = (bool) function;
    emergencyExit = true;
}

void printTypeSortMenu(int field)
{
    MENU arguments;
    initMenuParameters(&arguments, sortTypeChoices, sortTypeChoicesCount, sortTypeCallFunction);
    
    render_menu(arguments);
    
    switch (field)
    {
        case BY_CAFEDRA_CODE:
            if (ASCENDING == sort)
            {
                sortStruct(sortByCafedraCode);
            }
            else
            {
                sortStruct(sortByCafedraCodeDescending);
            }
            printMessage("Отсортированно по коду кафедры");
            break;
        case BY_CAFEDRA_NAME:
            if (ASCENDING == sort)
            {
                sortStruct(sortByCafedraName);
            }
            else
            {
                sortStruct(sortByCafedraNameDescending);
            }
            printMessage("Отсортированно по названию кафедры");
            break;
        case BY_TIME_PLANNED:
            if (ASCENDING == sort)
            {
                sortStruct(sortByTimePlanned);
            }
            else
            {
                sortStruct(sortByTimePlannedDescending);
            }
            printMessage("Отсортированно запланированным часам");
            break;
        case BY_TIME_SPENT:
            if (ASCENDING == sort)
            {
                sortStruct(sortByTimeSpent);
            }
            else
            {
                sortStruct(sortByTimeSpentDescending);
            }
            printMessage("Отсортированно по использованным часам");
            break;
        case BY_DIFFERENCE:
            if (ASCENDING == sort)
            {
                sortStruct(sortByDifference);
            }
            else
            {
                sortStruct(sortByDifferenceDescending);
            }
            printMessage("Отсортированно по отклонению");
            break;
        default:
            printMessage("WTF!?");
            break;
    }

}
