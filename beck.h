#ifndef _BECK_H
#define _BECK_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/* directory separators */
#if defined _WIN32 || _MSDOS
#define SEPARATOR "\\"
#else
#define SEPARATOR "/"
#endif

#if __STDC_VERSION__ >= 199901L
#include <stdbool.h>
#endif

#ifdef _WIN32
/* Windows headers */
#define WIN32_MEAN_AND_LEAN
#include <Windows.h> /* for GetModuleFileName() */
#elif defined __linux__
/* Linux headers */
#include <unistd.h> /* for readlink() */
#endif

#ifndef __bool_true_false_are_defined
typedef enum {
	false = 0, true
} bool;
#endif

#ifndef MAX_PATH
#define MAX_PATH 256 /* TODO: determine actual max path on linux */
#endif

#define PROMPT_DELIM "|"

int get_single(void);

void print_suggestion(int total);
bool should_begin(void);

FILE* open_beck(const char* arg0);
FILE* open_log(const char* arg0);
size_t GetResourcePath(const char* filename, size_t name_size, char* buff, size_t buff_size, const char* arg0);
size_t GetExecPath(const char* arg0, char* buff, size_t buff_size);

void exit_error(const char* msg);

void* emalloc(size_t count);
void* erealloc(void* ptr, size_t count);

#endif /* BECK_H */

