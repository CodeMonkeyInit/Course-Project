#include "programMenu.h"
#include <sys/syslimits.h>

void openFileMenu()
{
    struct MachineTime *previousStructBegininng = machineTimeBegining, *previousStructEnding = machineTimeEnding;
    
    initMachineTimeStruct();
    
    if ( getUserInputDialog("Введите полный путь или имя файла (.table - таблица, .bin - сжатый)", path) )
    {
        if ( FILE_LOADED == loadStruct(path) )
        {
            freeStructMem(previousStructBegininng);
            printMessage("Файл загружен успешно!");
        }
        else
        {
            machineTimeBegining = previousStructBegininng;
            machineTimeEnding   = previousStructEnding;
            
            printMessage("Файл будет создан/перезаписан");
        }
    }
}
