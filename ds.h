// ==================================================
// DEFINITIONS
// ==================================================

#ifndef DS_H
#define DS_H

// --------------------------------------------------
// error
// --------------------------------------------------

enum
{
    DS_NO_ERR = 0,
    DS_NULL_ERR,
    DS_MALLOC_ERR,
    DS_RANGE_ERR,
    DS_SIZE_ERR,
    DS_EMPTY_ERR,
    DS_NUM_OF_ERRORS
};

const char *ds_error(int errno);

// --------------------------------------------------
// vector
// --------------------------------------------------

typedef struct
{
    int cap; 	  // capacity of the vector
    int cnt;      // number of items in the vector
    void **items; // array of items
    int *sizes;   // size of each item
} vec_t;

int vec_init(vec_t *vec);
int vec_free(vec_t *vec);
int vec_append(vec_t *vec, void *item, int size);
int vec_pop(vec_t *vec);
int vec_get(vec_t *vec, int index, void *item, int size);
int vec_set(vec_t *vec, int index, void *item, int size);

// --------------------------------------------------
// string builder
// --------------------------------------------------

typedef struct
{
    vec_t chars;
} strb_t;

int strb_init(strb_t *strb);
int strb_free(strb_t *strb);
int strb_append(strb_t *strb, const char *str);
int strb_appendc(strb_t *strb, char ch);
int strb_pop(strb_t *strb);
int strb_get(strb_t *strb, int index, char *ch);
int strb_set(strb_t *strb, int index, char ch);
int strb_build(strb_t *strb, char **str);

#endif // DS_H

// ==================================================
// IMPLEMENTATIONS
// ==================================================

#ifdef DS_IMPLEMENTATION

#include <stdlib.h>
#include <string.h>

// --------------------------------------------------
// error
// --------------------------------------------------

const char *ds_error(int errno)
{
    static const char *msg[] = {
	"No error", // DS_NO_ERR = 0,
	"NULL argument error", // DS_NULL_ERR,
	"Malloc error", // DS_MALLOC_ERR,
	"Index out of range error", // DS_RANGE_ERR,
	"Mismatch size error", // DS_SIZE_ERR,
	"Empty vector error", // DS_EMPTY_ERR,
    };

    if (errno >= DS_NUM_OF_ERRORS)
    {
	return "What is this errno?";
    }
    return msg[errno];
}

// --------------------------------------------------
// vector
// --------------------------------------------------

int vec_init(vec_t *vec)
{
    if (vec == NULL) return DS_NULL_ERR;

    vec->cap = 0;
    vec->cnt = 0;
    vec->items = NULL;
    vec->sizes = NULL;
    return DS_NO_ERR;
}

int vec_free(vec_t *vec)
{
    if (vec == NULL) return DS_NULL_ERR;

    for (int i = 0; i < vec->cnt; i++) free(vec->items[i]);
    free(vec->items);
    free(vec->sizes);

    return vec_init(vec);
}

int vec_append(vec_t *vec, void *item, int size)
{
    if (vec == NULL || item == NULL) return DS_NULL_ERR;

    if (vec->cnt == vec->cap)
    {
	int new_cap = (vec->cap < 8 ? 8 : 2 * vec->cap);
	void **new_items = malloc(new_cap * sizeof(void *));
	int *new_sizes = malloc(new_cap * sizeof(int));
	if (new_items == NULL || new_sizes == NULL) return DS_MALLOC_ERR;

	for (int i = 0; i < vec->cap; i++)
	{
	    new_items[i] = vec->items[i];
	    new_sizes[i] = vec->sizes[i];
	}
	free(vec->items);
	free(vec->sizes);

	vec->cap = new_cap;
	vec->items = new_items;
	vec->sizes = new_sizes;
    }

    char *temp = malloc(sizeof(char) * size);
    if (temp == NULL) return DS_MALLOC_ERR;
    memcpy(temp, item, size);

    vec->items[vec->cnt] = temp;
    vec->sizes[vec->cnt] = size;
    vec->cnt++;
    return DS_NO_ERR;
}

int vec_pop(vec_t *vec)
{
    if (vec == NULL) return DS_NULL_ERR;
    if (vec->cnt == 0) return DS_EMPTY_ERR;

    free(vec->items[vec->cnt - 1]);
    vec->cnt--;
    return DS_NO_ERR;
}

int vec_get(vec_t *vec, int index, void *item, int size)
{
    if (vec == NULL || item == NULL) return DS_NULL_ERR;
    if (index < 0 || index >= vec->cnt) return DS_RANGE_ERR;
    if (vec->sizes[index] != size) return DS_SIZE_ERR;

    memcpy(item, vec->items[index], size);
    return DS_NO_ERR;
}

int vec_set(vec_t *vec, int index, void *item, int size)
{
    if (vec == NULL || item == NULL) return DS_NULL_ERR;
    if (index < 0 || index >= vec->cnt) return DS_RANGE_ERR;

    char *temp = malloc(sizeof(char) * size);
    if (temp == NULL) return DS_MALLOC_ERR;
    memcpy(temp, item, size);

    free(vec->items[index]);
    vec->items[index] = temp;
    vec->sizes[index] = size;
    return DS_NO_ERR;
}

// --------------------------------------------------
// string builder
// --------------------------------------------------

int strb_init(strb_t *strb)
{
    if (strb == NULL) return DS_NULL_ERR;
    return vec_init(&strb->chars);
}

int strb_free(strb_t *strb)
{
    if (strb == NULL) return DS_NULL_ERR;
    return vec_free(&strb->chars);
}

int strb_append(strb_t *strb, const char *str)
{
    if (strb == NULL || str == NULL) return DS_NULL_ERR;
    for (int i = 0; str[i]; i++)
    {
	int errno = vec_append(&strb->chars, (void*)str + i, sizeof(char));
	if (errno) return errno;
    }
    return DS_NO_ERR;
}

int strb_appendc(strb_t *strb, char ch)
{
    if (strb == NULL) return DS_NULL_ERR;
    return vec_append(&strb->chars, &ch, sizeof(ch));
}

int strb_pop(strb_t *strb)
{
    if (strb == NULL) return DS_NULL_ERR;
    return vec_pop(&strb->chars);
}

int strb_get(strb_t *strb, int index, char *ch)
{
    if (strb == NULL || ch == NULL) return DS_NULL_ERR;
    return vec_get(&strb->chars, index, ch, sizeof(*ch));
}

int strb_set(strb_t *strb, int index, char ch)
{
    if (strb == NULL) return DS_NULL_ERR;
    return vec_set(&strb->chars, index, &ch, sizeof(ch));
}

int strb_build(strb_t *strb, char **str)
{
    if (strb == NULL || str == NULL) return DS_NULL_ERR;

    int len = strb->chars.cnt;
    char *temp = malloc(sizeof(char) * len + 1);
    temp[len] = 0;
    for (int i = 0; i < len; i++)
    {	
	int errno = strb_get(strb, i, temp + i);
	if (errno) return errno;
    }

    *str = temp;
    return DS_NO_ERR;
}

#endif // DS_IMPLEMENTATION
