#ifndef CPY_H
#define CPY_H

#ifdef __clang__
#pragma clang system_header
#endif

// TODO add sc_log.h
// TODO build some good cmd software
// TODO in cpy_core.h, change new() and type()? maybe no need.
// TODO improve examples, with common data types
// TODO improve examples, with common cmd programs/software
// TODO add/fix list functions
// TODO add strings functions and rename
// TODO add cpy_global_cleanup(), idea from curl
// TODO add hashmap, too future
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
