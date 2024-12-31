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
    VEC_NO_ERR = 0,
    VEC_NULL_ERR,
    VEC_MALLOC_ERR,
    VEC_RANGE_ERR,
    VEC_SIZE_ERR,
    VEC_EMPTY_ERR,
    VEC_NUM_OF_ERRORS
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
	"No error", // VEC_NO_ERR = 0,
	"NULL argument error", // VEC_NULL_ERR,
	"Malloc error", // VEC_MALLOC_ERR,
	"Index out of range error", // VEC_RANGE_ERR,
	"Mismatch size error", // VEC_SIZE_ERR,
	"Empty vector error", // VEC_EMPTY_ERR,
    };

    if (errno >= VEC_NUM_OF_ERRORS)
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
    if (vec == NULL) return VEC_NULL_ERR;

    vec->cap = 0;
    vec->cnt = 0;
    vec->items = NULL;
    vec->sizes = NULL;
    return VEC_NO_ERR;
}

int vec_free(vec_t *vec)
{
    if (vec == NULL) return VEC_NULL_ERR;

    for (int i = 0; i < vec->cnt; i++) free(vec->items[i]);
    free(vec->items);
    free(vec->sizes);

    return vec_init(vec);
}

int vec_append(vec_t *vec, void *item, int size)
{
    if (vec == NULL || item == NULL) return VEC_NULL_ERR;

    if (vec->cnt == vec->cap)
    {
	int new_cap = (vec->cap < 8 ? 8 : 2 * vec->cap);
	void **new_items = malloc(new_cap * sizeof(void *));
	int *new_sizes = malloc(new_cap * sizeof(int));
	if (new_items == NULL || new_sizes == NULL) return VEC_MALLOC_ERR;

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
    if (temp == NULL) return VEC_MALLOC_ERR;
    memcpy(temp, item, size);

    vec->items[vec->cnt] = temp;
    vec->sizes[vec->cnt] = size;
    vec->cnt++;
    return VEC_NO_ERR;
}

int vec_pop(vec_t *vec)
{
    if (vec == NULL) return VEC_NULL_ERR;
    if (vec->cnt == 0) return VEC_EMPTY_ERR;

    free(vec->items[vec->cnt - 1]);
    vec->cnt--;
    return VEC_NO_ERR;
}

int vec_get(vec_t *vec, int index, void *item, int size)
{
    if (vec == NULL || item == NULL) return VEC_NULL_ERR;
    if (index < 0 || index >= vec->cnt) return VEC_RANGE_ERR;
    if (vec->sizes[index] != size) return VEC_SIZE_ERR;

    memcpy(item, vec->items[index], size);
    return VEC_NO_ERR;
}

int vec_set(vec_t *vec, int index, void *item, int size)
{
    if (vec == NULL || item == NULL) return VEC_NULL_ERR;
    if (index < 0 || index >= vec->cnt) return VEC_RANGE_ERR;

    char *temp = malloc(sizeof(char) * size);
    if (temp == NULL) return VEC_MALLOC_ERR;
    memcpy(temp, item, size);

    free(vec->items[index]);
    vec->items[index] = temp;
    vec->sizes[index] = size;
    return VEC_NO_ERR;
}

#endif // DS_IMPLEMENTATION
