#include "beck.h"
#include "quiz.h"

int main(int argc, char* argv[])
{
    FILE* file;
    int total;
    QUIZ quiz;

#ifdef _WIN32
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 0x1f);
#endif

    if (!should_begin()) {
        goto cleanup;
    }

    file = open_beck(argv[0]);
    if (file == NULL) {
        exit_error("unable to open beck.txt");
    }

    init_quiz(&quiz, file, PROMPT_DELIM);

    fclose(file);

    total = do_quiz(&quiz);

    printf("Total: %i\n", total);
    print_suggestion(total);

    fini_quiz(&quiz);
cleanup:
    return EXIT_SUCCESS;
}

/*
 * displays the quiz instructions and prompts the user to begin
 * returns true when the user says "yes" to the prompt, false when "no"
 */
bool should_begin(void)
{
    int yn;
    puts("Beck's Depression Inventory\n");
    puts("This quiz can help determine your level of depression.");
    puts("There are 20 questions. Enter the number corresponding to how");
    puts("you felt over the last two weeks. If you feel in between two answers,");
    puts("enter the larger number.");
    do {
        fputs("Continue? [Y/N] ", stdout);
        yn = toupper(get_single());
        fputs("\n", stdout);

        if (yn == 'N')
            return false;

    } while (yn != 'Y');
    return true;
}

/*
 * prints the suggestion based on quiz score
 */
void print_suggestion(int total)
{
    if (total > 40) {
        puts("Your depression seems to be extreme. You should seek medical help immediately.");
    }
    else if (total > 30) {
        puts("Your depression is severe.");
    }
    else if (total > 20) {
        puts("You suffer from moderate depression.");
    }
    else if (total > 16) {
        puts("Your mood disturbance is borderline clinical depression.");
    }
    else if (total > 10) {
        puts("You may suffer from mild mood disturbances.");
    }
    else if (total > 1) {
        puts("These ups and downs are considered normal.");
    }
    else {
        puts("You do not seem to have any mood disturbance.");
    }
}

/*
 * prompts for a single character, and returns that character
 * returns 0 when input is invalid
 */
int get_single(void)
{
    int count = 0;
    int c = getchar();

    if (c == '\n')
        return c;

    while(getchar() != '\n') {
        ++count;
    }

    return count == 0 ? c : 0;
}

/*
 * opens "beck.txt" for reading and returns the file pointer
 * this function expects argv[0] which it may or may not use
 */
FILE* open_beck(const char* arg0)
{
    char filename[] = "beck.txt";
    char path[MAX_PATH];
    GetResourcePath(filename, sizeof(filename), path, sizeof(path), arg0);
    return fopen(path, "r");
}

/*
 * opens "history.txt" for writing and returns the file pointer
 * this function expects argv[0] which it may or may not use
 */
FILE* open_log(const char* arg0)
{
    char filename[] = "history.txt";
    char path[MAX_PATH];
    GetResourcePath(filename, sizeof(filename), path, sizeof(path), arg0);
    return fopen(path, "a");
}

/*
 * gets the path of a resource located in the same directory as the executable
 */
size_t GetResourcePath(const char* filename, size_t name_size, char* buff, size_t buff_size, const char* arg0)
{
    size_t len = GetExecPath(arg0, buff, buff_size); /* get executable path */

    if (len + name_size < buff_size) {
         buff[len++] = SEPARATOR[0];
         memcpy(&buff[len], filename, name_size); /* copy filename to buffer */
         return len + name_size - 1; /* return the length of the buffer */
    }
    else {
         return len; /* buffer is not large enough to copy file name */
    }
}

/*
 * gets the path of the current executable
 */
size_t GetExecPath(const char* arg0, char* buff, size_t buff_size)
{
    char* temp_path = emalloc(buff_size);
#ifdef _WIN32
    /* if windows, define things in terms of DWORD */
    DWORD size;
    DWORD index;
    size = GetModuleFileNameA(NULL, temp_path, buff_size);
#elif defined __linux__
    ssize_t size;
    ssize_t index;
    size = readlink("/proc/self/exe", temp_path, buff_size); /* hopefully it's a linux version that supports this */
#else
    size_t size;
    size_t index;
    strcpy(temp_path, arg0); /* hope that the path is in arg0 */
    size = strlen(temp_path);
#endif

    for(index = size - 1; index > 0; --index) { /* go backwards until we reach a directory separator */
        if (temp_path[index] == SEPARATOR[0]) {
            temp_path[index] = '\0'; /* set where we want the string to end (at the separator) */
            if (index > buff_size)
                goto overflow;
            strcpy(buff, temp_path); /* copy the temp path to the buff */
            goto cleanup;
        }
    }

    if (buff_size < 2)
        goto overflow;

    strcpy(buff, ".");
    goto cleanup;
overflow:
    exit_error("unable to copy executable directory path, buffer is too small");
cleanup:
    free(temp_path);
    return strlen(buff); /* return path length */
}

/*
 * prints an error message then exits with EXIT_FAILURE
 */
void exit_error(const char* msg)
{
    printf("error: %s\n", msg);
    exit(EXIT_FAILURE);
}

/*
 * realloc() that exits on failure
 */
void* erealloc(void* ptr, size_t count)
{
    void* newptr = realloc(ptr, count);
    if (newptr == NULL) {
        exit_error("call to realloc() failed");
    }
    return newptr;
}

/*
 * malloc() that exits on failure
 */
void* emalloc(size_t count)
{
    void* newptr = malloc(count);
    if (newptr == NULL) {
        exit_error("call to malloc() failed");
    }
    return newptr;
}
