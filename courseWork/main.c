#include "machine_time.h"
//#include "program_menu.h"
#include <stdio.h>

int main()
{
    FILE *machineTimeFile = NULL;
    char *buffer;
    if ( loadFile(&machineTimeFile, "/Users/deniskuliev/Library/Developer/Xcode/DerivedData/courseWork-csjasbpzgqmfwtcyokgaikxvneev/Build/Products/Debug/data", MACHINE_FILE_HEADER) == FILE_LOADED)
    {
        buffer = loadToBuffer(machineTimeFile);
        //printf("%s\n", buffer);
        parseBuffer(buffer, 299);
    }
//    init_menu();
//    render_menu(0);
}
