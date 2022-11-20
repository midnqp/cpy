#ifndef CPY_H
#define CPY_H

// detect memory leaks in MSVC
#if defined(_DEBUG) && defined(_MSC_VER)
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#define CPY_CRTDBG_MEMCHECK (0x01 | 0x20)
#include <crtdbg.h>
#endif

#ifdef __clang__
#pragma clang system_header
#endif

// TODO add sc_log.h
// TODO build some good cmd software
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

#endif  // CPY_H
