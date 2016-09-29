#include "machine_time.h"
//#include "program_menu.h"
#include <stdio.h>
#include <locale.h>


int main()
{
    setlocale(LC_ALL, "");


    
    //init_menu();
    //render_menu(0);

    FILE *machineTimeFile = NULL;
    char *buffer;
    if ( loadFile(&machineTimeFile, "/Users/deniskuliev/Library/Developer/Xcode/DerivedData/courseWork-csjasbpzgqmfwtcyokgaikxvneev/Build/Products/Debug/data", MACHINE_FILE_HEADER) == FILE_LOADED)
    {
        buffer = loadToBuffer(machineTimeFile);
        
        printf("%s", buffer);
        
        //parseBuffer(buffer, 296);
        
        //296  начало таблицы
        //299 начала нумерации
        //307 второй пункт 307
        //321 следующий пункт
    }

}
