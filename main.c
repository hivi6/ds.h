#include <stdio.h>

#define DS_IMPLEMENTATION
#include "ds.h"

int main()
{
    vec_t vec;

    printf("== vec_init ==\n");
    int errno = vec_init(&vec);
    printf("ERROR: %s\n", vec_error(errno));

    printf("== vec_append ==\n");
    for (int i = 0; i < 10; i++)
    {
	errno = vec_append(&vec, &i, sizeof(i));
	printf("ERROR: %s\n", vec_error(errno));
    }

    printf("== vec_pop ==\n");
    for (int i = 0; i < 10; i++)
    {
	errno = vec_pop(&vec);
	printf("ERROR: %s\n", vec_error(errno));
    }

    printf("== vec_free ==\n");
    errno = vec_free(&vec);
    printf("ERROR: %s\n", vec_error(errno));

    printf("== test vec_err ==\n");
    for (int i = 0; i < 10; i++)
	printf("ERROR: %s\n", vec_error(i));
    return 0;
}
