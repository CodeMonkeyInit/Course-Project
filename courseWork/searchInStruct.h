//
//  searchSort.h
//  courseWork
//
//  Created by Денис Кулиев on 07.11.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#ifndef searchSort_h
#define searchSort_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "searchStruct.h"

#define SUBSTRING_NOT_FOUND -1
#define SEARCH_FAILED -1

int getRecordsFound();
MTsearch *searchInStruct(char *pattern);

#endif /* searchSort_h */
