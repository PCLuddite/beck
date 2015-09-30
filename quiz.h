#ifndef QUIZ_H
#define QUIZ_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    size_t count;
    size_t capacity;
    char** options;
} PROMPT; /* holds information for an individual question prompt */

typedef struct {
    size_t count;
    size_t capacity;
    PROMPT** ques;
} QUIZ; /* hold information for the entire quiz */

int do_quiz(QUIZ* quiz); /* displays quiz questions and returns a total */

void show_prompt(const PROMPT* prompt); /* displays a question prompt */

void make_quiz(QUIZ* quiz, FILE* file, const char* delim); /* creates a quiz from a file */
void make_prompt(PROMPT* prompt, const char* str, const char* delim); /* makes a prompt from a string */

void free_quiz(QUIZ* quiz); /* frees a quiz made by make_quiz() */

#endif /* QUIZ_H */
