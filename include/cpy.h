#ifndef CPY_H
#define CPY_H

#ifdef __clang__
#pragma clang system_header
#endif

#include <ctype.h>
#include <float.h>
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#ifdef _WIN32
#include <Windows.h>
#include <io.h>
#else
#include <dirent.h>
#include <unistd.h>
#endif

#include "cpy_core.h"
#include "cpy_file.h"
#include "cpy_list.h"
#include "cpy_print.h"
#include "cpy_string.h"
#include "cpy_types.h"

#endif
