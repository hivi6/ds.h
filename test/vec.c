#include <stdio.h>

#define DS_IMPLEMENTATION
#include "ds.h"

int main()
{
    vec_t vec;

    int errno = vec_init(&vec);
    printf("vec_init() | ERROR: %s\n", vec_error(errno));

    for (int i = 0; i < 10; i++)
    {
	int temp = 100 - i;
	errno = vec_append(&vec, &temp, sizeof(i));
	printf("vec_append(%d) | vec.cnt: %d | ERROR: %s\n", temp, vec.cnt, 
	       vec_error(errno));
    }

    for (int i = 0; i < vec.cnt; i++)
    {
	int temp;
	errno = vec_get(&vec, i, &temp, sizeof(temp));
	printf("vec_get(%d): %d | ERROR: %s\n", i, temp, vec_error(errno));
    }

    int cnt = vec.cnt;
    for (int i = 0; i < cnt; i++)
    {
	errno = vec_pop(&vec);
	printf("vec_pop() | vec.cnt: %d | ERROR: %s\n", vec.cnt, 
	       vec_error(errno));
    }

    errno = vec_free(&vec);
    printf("vec_free() | ERROR: %s\n", vec_error(errno));

    for (int i = 0; i < 10; i++)
	printf("vec_err(%d): %s\n", i, vec_error(i));

    return 0;
}