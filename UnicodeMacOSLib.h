//
//  UnicodeMacOSLib.h
//  courseWork
//
//  Created by Денис Кулиев on 12.10.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#ifndef UnicodeMacOSLib_h
#define UnicodeMacOSLib_h

#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdbool.h>

int getBlockSize();
bool isUTF8charBeginning(char c);
size_t utf8len(const char *s);
bool isUnicodeMultibyteString(const char *string);
char *formatUtf8String(char *utf8string, const size_t formatLength);


#endif /* UnicodeMacOSLib_h */
