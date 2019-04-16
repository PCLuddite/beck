#ifndef _LIST_H
#define _LIST_H

#include <stdlib.h>
#include <ctype.h>

typedef unsigned char BYTE;

struct BECK_LIST_ITEM
{
    BYTE* value;
    size_t len;
}

typedef struct BECK_LIST_ITEM BLIST_ITM;
typedef BLIST_ITM BECK_STR;

struct BECK_LIST
{
    BLIST_ITM* items;
    size_t size;
    size_t allocated;
}

typedef struct BECK_LIST BLIST;

int list_init(BLIST* list);
void* list_add(BLIST* list, const BYTE* value, size_t len);
void* list_rm(BLIST* list, int idx);

BLIST_ITM* list_set(BLIST* list, int idx, const BYTE* value, size_t len);
BLIST_ITM* list_get(BLIST* list, int idx);
int list_int(BLIST* list, int idx);
long list_long(BLIST* list, int idx);
double list_double(BLIST* list, int idx);
float list_float(BLIST* list, int idx);
BECK_STR* list_str(BLIST* list, int idx);

#endif
