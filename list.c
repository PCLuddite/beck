#include "list.h"

int list_init(BLIST* list)
{
    list->items = malloc(10 * sizeof*list->items);
    if (list->items == NULL)
        return 1;
    list->size = 0;
    list->allocated = 10;
    return 0;
}


void* list_add(BLIST* list, const BYTE* value, size_t len)
{
    BLIST_ITM itm;
    memcpy(itm->value, value, len);
    itm->len = len;

    if (list->allocated < list->size + 1) {
        void* items = realloc(list->items, (list->allocated *= 2) * sizeof*list->items);
        if (items == NULL)
            return 1;
        list->items = items;
    }

    list->items[list->size++] = itm;

    return 0;
}

void* list_rm(BLIST* list, size_t idx);

BLIST_ITM* list_set(BLIST* list, size_t idx, const BYTE* value, size_t len);

BLIST_ITM* list_get(BLIST* list, size_t idx)
{
    if (idx < 0 || idx >= list->size)
        return NULL;
    return &list->items[idx];
}

int list_int(BLIST* list, int idx)
{
    int i;
    BLIST_ITM* itm = list_get(list, idx);
    if (itm == NULL || itm->len != sizeof(int))
        return 0;

    if (memcpy(&i, itm->value, sizeof(int)) == NULL)
        return 0;

    return i;
}

long list_long(BLIST* list, int idx)
{
    long l;
    BLIST_ITM* itm = list_get(list, idx);
    if (itm == NULL || itm->len != sizeof(long))
        return 0;

    if (memcpy(&l, itm->value, sizeof(long)) == NULL)
        return 0;

    return i;
}

double list_double(BLIST* list, int idx)
{
    double d;
    BLIST_ITM* itm = list_get(list, idx);
    if (itm == NULL || itm->len != sizeof(double))
        return 0;

    if (memcpy(&d, itm->value, sizeof(double)) == NULL)
        return 0;
    return d;
}

float list_float(BLIST* list, int idx)
{
    float f;
    BLIST_ITM* itm = list_get(list, idx);
    if (itm == NULL || itm->len != sizeof(float))
        return 0;

    if (memcpy(&f, itm->value, sizeof(float)) == NULL)
        return 0;

    return f;
}

BECK_STR* list_str(BLIST* list, int idx)
{
    return list_get(list, idx);
}

