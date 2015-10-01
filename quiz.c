#include "beck.h"
#include "quiz.h"

static void quiz_add(QUIZ* quiz, PROMPT* prompt)
{
    if (quiz->count == quiz->capacity) {
        quiz->capacity *= 2;
        quiz->ques = erealloc(quiz->ques, quiz->capacity * sizeof*(quiz->ques));
    }
    quiz->ques[quiz->count++] = prompt;
}

static void prompt_add(PROMPT* prompt, char* str)
{
    if (prompt->count == prompt->capacity) {
        prompt->capacity *= 2;
        prompt->options = erealloc(prompt->options, prompt->capacity * sizeof*prompt->options);
    }
    prompt->options[prompt->count++] = str;
}

static size_t find_end(const char* str)
{
    size_t end = strlen(str) - 1;
    while(isspace(str[end])) {
        --end;
    }
    return end;
}

int do_quiz(QUIZ* quiz)
{
    int curr  = 0,
        total = 0;
    while(curr < quiz->count) {
        int choice, charchoice;
        printf("Question %i:\n", (curr + 1));
        show_prompt(quiz->ques[curr]);
        fputs("Answer: ", stdout);
        charchoice = get_single();
        fputs("\n", stdout);
        choice = charchoice - '0';
        if (choice >= 0 && choice < quiz->ques[curr]->count) {
            ++curr;
            total += choice;
        }
    }
    return total;
}

void show_prompt(const PROMPT* prompt)
{
    int i = 0;
    for(; i < prompt->count; ++i) {
        printf("%i  %s\n", i, prompt->options[i]);
    }
}

void make_quiz(QUIZ* quiz, FILE* file, const char* delim)
{
    static const int INITIAL_CAPACITY = 25;

    char full[1024]; /* buffer to hold a line of text */
    char* prompt_mem; /* pointer to memory allocated for prompts */
    int num_prompts = 0; /* the number of prompts */
    int curr = 0;

    /* count the lines of the file to determine number of prompts */
    while(fgets(full, ARRSIZE(full), file) != NULL) {
        ++num_prompts;
    }

    fseek(file, SEEK_SET, 0); /* reset the stream */

    prompt_mem = emalloc(num_prompts * sizeof(PROMPT)); /* allocate memory for prompts in a contiguous block */

    /* initialize QUIZ struct */
    quiz->ques = emalloc(INITIAL_CAPACITY * sizeof*(quiz->ques)); /* allocate memory for prompt array */
    quiz->capacity = INITIAL_CAPACITY;
    quiz->count = 0;

    while(fgets(full, ARRSIZE(full), file) != NULL) {
        PROMPT* prompt = (PROMPT*)(prompt_mem + (curr++ * sizeof*prompt)); /* find memory for prompt */
        make_prompt(prompt, full, delim);
        quiz_add(quiz, prompt);
    }
}

void make_prompt(PROMPT* prompt, const char* str, const char* delim)
{
    static const int INITIAL_CAPACITY = 4;

    char* opt;
    size_t count = find_end(str); /* find the end of the string */
    char* promptstr = emalloc((count + 1) * sizeof*promptstr); /* allocate memory for the string to tokenize */

    strncpy(promptstr, str, count); /* copy the string to be tokenized string */
    promptstr[count] = '\0';

    /* initialize the PROMPT struct */
    prompt->count = 0;
    prompt->capacity = INITIAL_CAPACITY;
    prompt->options = emalloc(INITIAL_CAPACITY * sizeof*(prompt->options)); /* allocate memory for tokenized options array */

    /* tokenize the prompt string */
    opt = strtok(promptstr, delim);
    while(opt != NULL){
        prompt_add(prompt, opt);
        opt = strtok(NULL, delim);
    }
}

void free_quiz(QUIZ* quiz)
{
    size_t i = 0;
    for(; i < quiz->count; ++i) {
        free(quiz->ques[i]->options);
    }
    free(quiz->ques[0]); /* memory for prompt was allocated contiguously, only need to free the start */
    free(quiz->ques);
}
