#ifndef QUIZ_H
#define QUIZ_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define ARRSIZE(x) (sizeof(x)/sizeof(x[0]))

typedef struct {
    size_t count;
    size_t capacity;
    char** options;
} PROMPT; /* holds information for an individual question prompt */

typedef struct {
    size_t count;
    size_t capacity;
    PROMPT* ques;
} QUIZ; /* hold information for the entire quiz */

int do_quiz(QUIZ* quiz);

void show_prompt(const PROMPT* prompt);

void init_quiz(QUIZ* quiz, FILE* file, const char* delim);
void init_prompt(PROMPT* prompt, const char* str, const char* delim);

void close_quiz(QUIZ* quiz);

#endif /* QUIZ_H */
