#include "programMenu.h"

const char *sortTypeChoices[] =
{
    "СОРТИРОВКА",
    "По возростанию",
    "По убыванию"
};
const int sortTypeChoicesCount = 3;

int sort;

void sortTypeCallFunction(int function)
{
    sort = function;
    exitMenu = true;
}

void sortAscending(int field)
{
    switch (field)
    {
        case BY_CAFEDRA_CODE:
            sortStruct(sortByCafedraCode);
            break;
        case BY_CAFEDRA_NAME:
            sortStruct(sortByCafedraName);
            break;
        case BY_TIME_PLANNED:
            sortStruct(sortByTimePlanned);
            break;
        case BY_TIME_SPENT:
            sortStruct(sortByTimeSpent);
            break;
        case BY_DIFFERENCE:
            sortStruct(sortByDifference);
            break;
        default:
            printMessage("WTF!?");
            break;
    }
    printMessage("Отсортировано по возрастанию");
}

void sortDescending(int field)
{
    switch (field)
    {
        case BY_CAFEDRA_CODE:
            sortStruct(sortByCafedraCodeDescending);
            break;
        case BY_CAFEDRA_NAME:
            sortStruct(sortByCafedraNameDescending);
            break;
        case BY_TIME_PLANNED:
            sortStruct(sortByTimePlannedDescending);
            break;
        case BY_TIME_SPENT:
            sortStruct(sortByTimeSpentDescending);
            break;
        case BY_DIFFERENCE:
            sortStruct(sortByDifferenceDescending);
            break;
        default:
            printMessage("WTF!?");
            break;
    }
    printMessage("Отсортировано по убыванию");
}

void printTypeSortMenu(int field)
{
    sort = SORT_ABORTED;
    MENU arguments;
    initMenuParameters(&arguments, sortTypeChoices, sortTypeChoicesCount, sortTypeCallFunction);
    
    render_menu(arguments);
    if (ASCENDING == sort)
    {
        sortAscending(field);
    }
    else if (DESCENDING == sort)
    {
        sortDescending(field);
    }
}
