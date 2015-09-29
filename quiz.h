#ifndef QUIZ_H
#define QUIZ_H

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

/* struct definitions */

typedef struct {
    char** options;
    size_t count;
    size_t capacity;
} PROMPT;

typedef struct {
    PROMPT** ques;
    size_t count;
    size_t capacity;
} QUIZ;

int do_quiz(QUIZ* quiz);

void show_prompt(const PROMPT* prompt);

void make_quiz(QUIZ* quiz, FILE* file, const char* delim);
void make_prompt(PROMPT* prompt, const char* str, const char* delim);

void free_quiz(QUIZ* quiz);
void free_prompt(PROMPT* quiz);

#endif

