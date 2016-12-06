#ifndef programMenuSearch_h
#define programMenuSearch_h

#include <stdio.h>
#include "programMenuTableExtras.h"
#include "machineTime.h"

void printSearchResults(char *pattern);
int deleteSearchResult(MTsearch **record);
void editSearchResults();

#endif /* programMenuSearch_h */
