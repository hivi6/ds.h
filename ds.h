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
} sbuilder_t;

int sbuilder_init(sbuilder_t *sbuilder);
int sbuilder_free(sbuilder_t *sbuilder);
int sbuilder_append(sbuilder_t *sbuilder, const char *str);
int sbuilder_appendc(sbuilder_t *sbuilder, char ch);
int sbuilder_pop(sbuilder_t *sbuilder);
int sbuilder_get(sbuilder_t *sbuilder, int index, char *ch);
int sbuilder_set(sbuilder_t *sbuilder, int index, char ch);
int sbuilder_build(sbuilder_t *sbuilder, char **str);

// --------------------------------------------------
// (double) linked list
// --------------------------------------------------

typedef struct llist_node_t
{
    void *item;
    int item_size;
    struct llist_node_t *prev;
    struct llist_node_t *next;
} llist_node_t;

typedef struct
{
    int cnt;
    llist_node_t *head;
    llist_node_t *tail;
} llist_t;

int llist_init(llist_t *llist);
int llist_free(llist_t *llist);
int llist_front(llist_t *llist, void *item, int item_size);
int llist_back(llist_t *llist, void *item, int item_size);
int llist_pushb(llist_t *llist, void *item, int item_size);
int llist_pushf(llist_t *llist, void *item, int item_size);
int llist_popb(llist_t *llist);
int llist_popf(llist_t *llist);

// --------------------------------------------------
// pair
// --------------------------------------------------

typedef struct
{
    void *first;
    int first_size;

    void *second;
    int second_size;
} pair_t;

int pair_init(pair_t *pair);
int pair_free(pair_t *pair);
int pair_setf(pair_t *pair, void *first, int first_size);
int pair_getf(pair_t *pair, void *first, int first_size);
int pair_sets(pair_t *pair, void *second, int second_size);
int pair_gets(pair_t *pair, void *second, int second_size);

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

int sbuilder_init(sbuilder_t *sbuilder)
{
    if (sbuilder == NULL) return DS_NULL_ERR;
    return vec_init(&sbuilder->chars);
}

int sbuilder_free(sbuilder_t *sbuilder)
{
    if (sbuilder == NULL) return DS_NULL_ERR;
    return vec_free(&sbuilder->chars);
}

int sbuilder_append(sbuilder_t *sbuilder, const char *str)
{
    if (sbuilder == NULL || str == NULL) return DS_NULL_ERR;
    for (int i = 0; str[i]; i++)
    {
	int errno = vec_append(&sbuilder->chars, (void*)str + i, sizeof(char));
	if (errno) return errno;
    }
    return DS_NO_ERR;
}

int sbuilder_appendc(sbuilder_t *sbuilder, char ch)
{
    if (sbuilder == NULL) return DS_NULL_ERR;
    return vec_append(&sbuilder->chars, &ch, sizeof(ch));
}

int sbuilder_pop(sbuilder_t *sbuilder)
{
    if (sbuilder == NULL) return DS_NULL_ERR;
    return vec_pop(&sbuilder->chars);
}

int sbuilder_get(sbuilder_t *sbuilder, int index, char *ch)
{
    if (sbuilder == NULL || ch == NULL) return DS_NULL_ERR;
    return vec_get(&sbuilder->chars, index, ch, sizeof(*ch));
}

int sbuilder_set(sbuilder_t *sbuilder, int index, char ch)
{
    if (sbuilder == NULL) return DS_NULL_ERR;
    return vec_set(&sbuilder->chars, index, &ch, sizeof(ch));
}

int sbuilder_build(sbuilder_t *sbuilder, char **str)
{
    if (sbuilder == NULL || str == NULL) return DS_NULL_ERR;

    int len = sbuilder->chars.cnt;
    char *temp = malloc(sizeof(char) * len + 1);
    if (temp == NULL) return DS_MALLOC_ERR;
    temp[len] = 0;
    for (int i = 0; i < len; i++)
    {	
	int errno = sbuilder_get(sbuilder, i, temp + i);
	if (errno) return errno;
    }

    *str = temp;
    return DS_NO_ERR;
}

// --------------------------------------------------
// (double) linked list
// --------------------------------------------------

int llist_init(llist_t *llist)
{
    if (llist == NULL) return DS_NULL_ERR;
    llist->cnt = 0;
    llist->head = NULL;
    llist->tail = NULL;
    return DS_NO_ERR;
}

int llist_free(llist_t *llist)
{
    if (llist == NULL) return DS_NULL_ERR;
    llist_node_t *node = llist->head;
    while (node)
    {
	free(node->item);
	llist_node_t *next = node->next;
	free(node);
	node = next;
    }

    llist_init(llist);
    return DS_NO_ERR;
}

int llist_front(llist_t *llist, void *item, int item_size)
{
    if (llist == NULL || item == NULL) return DS_NULL_ERR;
    if (llist->cnt == 0) return DS_EMPTY_ERR;
    if (llist->head->item_size != item_size) return DS_SIZE_ERR;

    memcpy(item, llist->head->item, item_size);
    return DS_NO_ERR;
}

int llist_back(llist_t *llist, void *item, int item_size)
{
    if (llist->cnt == 0) return DS_EMPTY_ERR;
    if (llist->tail->item_size != item_size) return DS_SIZE_ERR;

    memcpy(item, llist->tail->item, item_size);
    return DS_NO_ERR;
}

int llist_pushb(llist_t *llist, void *item, int item_size)
{
    if (llist == NULL || item == NULL) return DS_NULL_ERR;

    char *temp = malloc(sizeof(char) * item_size);
    if (temp == NULL) return DS_MALLOC_ERR;
    memcpy(temp, item, item_size);

    llist_node_t *node = malloc(sizeof(llist_node_t));
    if (node == NULL)
    {
	free(temp);
	return DS_MALLOC_ERR;
    }
    node->item = temp;
    node->item_size = item_size;
    node->prev = NULL;
    node->next = NULL;

    if (llist->cnt == 0) llist->head = llist->tail = node;
    else
    {
	llist->tail->next = node;
	node->prev = llist->tail;
	llist->tail = node;
    }
    llist->cnt++;
    return DS_NO_ERR;
}

int llist_pushf(llist_t *llist, void *item, int item_size)
{
    if (llist == NULL || item == NULL) return DS_NULL_ERR;

    char *temp = malloc(sizeof(char) * item_size);
    if (temp == NULL) return DS_MALLOC_ERR;
    memcpy(temp, item, item_size);

    llist_node_t *node = malloc(sizeof(llist_node_t));
    if (node == NULL)
    {
	free(temp);
	return DS_MALLOC_ERR;
    }
    node->item = temp;
    node->item_size = item_size;
    node->prev = NULL;
    node->next = NULL;

    if (llist->cnt == 0) llist->head = llist->tail = node;
    else
    {
	llist->head->prev = node;
	node->next = llist->head;
	llist->head = node;
    }
    llist->cnt++;
    return DS_NO_ERR;
}

int llist_popb(llist_t *llist)
{
    if (llist == NULL) return DS_NULL_ERR;

    if (llist->cnt == 0) return DS_EMPTY_ERR;

    llist_node_t *node = llist->tail;
    llist->tail = llist->tail->prev;
    if (llist->tail != NULL)
	llist->tail->next = NULL;
    else
	llist->head = NULL;
    free(node->item);
    free(node);

    llist->cnt--;
    return DS_NO_ERR;
}

int llist_popf(llist_t *llist)
{
    if (llist == NULL) return DS_NULL_ERR;

    if (llist->cnt == 0) return DS_EMPTY_ERR;

    llist_node_t *node = llist->head;
    llist->head = llist->head->next;
    if (llist->head != NULL)
	llist->head->prev = NULL;
    else
	llist->tail = NULL;
    free(node->item);
    free(node);

    llist->cnt--;
    return DS_NO_ERR;
}

// --------------------------------------------------
// pair
// --------------------------------------------------

int pair_init(pair_t *pair)
{
    if (pair == NULL) return DS_NULL_ERR;

    pair->first = NULL;
    pair->first_size = 0;
    pair->second = NULL;
    pair->second_size = 0;
    return DS_NO_ERR;
}

int pair_free(pair_t *pair)
{
    if (pair == NULL) return DS_NULL_ERR;

    free(pair->first);
    free(pair->second);
    return pair_init(pair);
}

int pair_setf(pair_t *pair, void *first, int first_size)
{
    if (pair == NULL || first == NULL) return DS_NULL_ERR;
    if (pair->first != NULL) free(pair->first);

    char *temp = malloc(first_size * sizeof(char));
    if (temp == NULL) return DS_MALLOC_ERR;
    memcpy(temp, first, first_size);
    pair->first = temp;
    pair->first_size = first_size;
    return DS_NO_ERR;
}

int pair_getf(pair_t *pair, void *first, int first_size)
{
    if (pair == NULL || first == NULL) return DS_NULL_ERR;
    if (pair->first == NULL) return DS_NULL_ERR;
    if (pair->first_size != first_size) return DS_SIZE_ERR;

    memcpy(first, pair->first, first_size);
    return DS_NO_ERR;
}

int pair_sets(pair_t *pair, void *second, int second_size)
{
    if (pair == NULL || second == NULL) return DS_NULL_ERR;
    if (pair->second != NULL) free(pair->second);

    char *temp = malloc(second_size * sizeof(char));
    if (temp == NULL) return DS_MALLOC_ERR;
    memcpy(temp, second, second_size);
    pair->second = temp;
    pair->second_size = second_size;
    return DS_NO_ERR;
}

int pair_gets(pair_t *pair, void *second, int second_size)
{
    if (pair == NULL || second == NULL) return DS_NULL_ERR;
    if (pair->second == NULL) return DS_NULL_ERR;
    if (pair->second_size != second_size) return DS_SIZE_ERR;

    memcpy(second, pair->second, second_size);
    return DS_NO_ERR;
}

#endif // DS_IMPLEMENTATION
