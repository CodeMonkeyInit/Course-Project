#include "customFileFunctions.h"

int checkFileHeader(FILE *unknown, const char *refernceHeader)
{
    char fileHeader[200];
    fscanf(unknown, "%s", fileHeader);
    
    if ( strcmp(fileHeader, refernceHeader) )
    {
        return HEADERS_MISMATCH;
    }
    else
    {
        return HEADERS_MATCH;
    }
}

int loadFile(FILE **file,const char *path,const char *header)
{
    *file = fopen(path, "rb");
    
    if (*file == NULL)
    {
        return FILE_NOT_OPEN;
    }
    
    if ( checkFileHeader(*file, header) == HEADERS_MISMATCH )
    {
        fclose(*file);
        return INCORRECT_FILE;
    }
    
    return FILE_LOADED;
}

int getFileType(const char *path)
{
    if (NULL != strstr(path, ".table"))
    {
        return TABLE_TYPE_FILE;
    }
    else if (NULL != strstr(path, ".bin"))
    {
        return BINARY_TYPE_FILE;
    }
    else if (NULL != strstr(path, ".txt"))
    {
        return TEXT_TYPE_FILE;
    }
    else
    {
        return UNKNOWN_FILE_TYPE;
    }
}
