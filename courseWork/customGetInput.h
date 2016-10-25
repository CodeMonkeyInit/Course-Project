//
//  customGetInput.h
//  courseWork
//
//  Created by Денис Кулиев on 24.10.16.
//  Copyright © 2016 Денис Кулиев. All rights reserved.
//

#ifndef customGetInput_h
#define customGetInput_h

#include <ncurses.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "macKeys.h"
#include "UnicodeMacOSLib.h"

#define ARGUMENT_TYPE 0
#define ARGUMENT_LENGTH 1
#define INT_TYPE 0
#define STRING_TYPE 1
#define CHAR_TYPE 2
#define WRONG_TYPE -1
#define UNKNOWN_LENGTH 0
#define WRONG_FORMAT -1
#define INPUT_ABORTED -1
#define BACKSPACE_AND_CHARACTER 3

int windowGetInput(WINDOW *win, char *format,...);

#endif /* customGetInput_h */
