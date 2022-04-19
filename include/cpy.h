#ifndef CPY_H
#define CPY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include <stdbool.h>
#include <float.h>
#include <limits.h>
#ifdef _WIN32
    #include <Windows.h>
    #include <io.h>
#else
    #include <unistd.h>
    #include <dirent.h>
#endif


#include "cpy_core.h"
#include "cpy_print.h"
#include "cpy_file.h"
#include "cpy_list.h"
#include "cpy_string.h"

#endif
