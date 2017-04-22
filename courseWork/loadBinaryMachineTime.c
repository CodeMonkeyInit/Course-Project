#include "machineTime.h"
#include <ncurses.h>
int loadBinary(FILE **binaryFile)
{
    const int CHAR_MAX_LENGTH = 81;
    
    char **temp = malloc(sizeof(char*) * RECORD_ENTRIES);
    
    for (int i = 0; i < RECORD_ENTRIES; i++)
    {
        temp[i] = malloc(sizeof(char) * CHAR_MAX_LENGTH);
    }
    
    while ( !feof(*binaryFile) )
    {
        fscanf(*binaryFile, "\n%s %s %s %s",
               temp[CAFEDRA_CODE],
               temp[CAFEDRA_NAME],
               temp[TIME_PLANNED],
               temp[TIME_USED]
               );
        char *tempString = formatUtf8String(temp[CAFEDRA_NAME], CAFEDRA_NAME_FORMAT_LENGTH);
        
        free(temp[CAFEDRA_NAME]);
        
        printw("\n%s %s %s %s", temp[CAFEDRA_CODE],
               temp[CAFEDRA_NAME],
               temp[TIME_PLANNED],
               temp[TIME_USED]);
        refresh();
        temp[CAFEDRA_NAME] = tempString;
        
        addRecord( createRecord(temp) );
    }
    
    freeArrayOfStrings(temp, RECORD_ENTRIES);
    
    fclose(*binaryFile);
    
    return FILE_LOADED;
}
