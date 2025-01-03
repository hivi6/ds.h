#include <stdio.h>

#define DS_IMPLEMENTATION
#include "ds.h"

int main()
{
    pair_t pair;
    int errno = pair_init(&pair);
    printf("pair_init() | ERROR: %s\n", ds_error(errno));

    int a = -1;
    errno = pair_getf(&pair, &a, sizeof(a));
    printf("pair_getf(): %d | ERROR: %s\n", a, ds_error(errno));

    a = 10;
    errno = pair_setf(&pair, &a, sizeof(a));
    printf("pair_setf(%d) | ERROR: %s\n", a, ds_error(errno));

    a = -1;
    errno = pair_getf(&pair, &a, sizeof(a));
    printf("pair_getf(): %d | ERROR: %s\n", a, ds_error(errno));

    a = -1;
    errno = pair_gets(&pair, &a, sizeof(a));
    printf("pair_gets(): %d | ERROR: %s\n", a, ds_error(errno));

    a = 20;
    errno = pair_sets(&pair, &a, sizeof(a));
    printf("pair_sets(%d) | ERROR: %s\n", a, ds_error(errno));

    a = -1;
    errno = pair_gets(&pair, &a, sizeof(a));
    printf("pair_gets(): %d | ERROR: %s\n", a, ds_error(errno));

    a = -1;
    errno = pair_getf(&pair, &a, sizeof(a));
    printf("pair_getf(): %d | ERROR: %s\n", a, ds_error(errno));
    a = -1;
    errno = pair_gets(&pair, &a, sizeof(a));
    printf("pair_gets(): %d | ERROR: %s\n", a, ds_error(errno));

    double x = 3.14;
    errno = pair_setf(&pair, &x, sizeof(x));
    printf("pair_setf(%f) | ERROR: %s\n", x, ds_error(errno));
    char y = 'x';
    errno = pair_sets(&pair, &y, sizeof(y));
    printf("pair_sets(%c) | ERROR: %s\n", y, ds_error(errno));

    x = -1;
    errno = pair_getf(&pair, &x, sizeof(x));
    printf("pair_getf(): %f | ERROR: %s\n", x, ds_error(errno));
    y = -1;
    errno = pair_gets(&pair, &y, sizeof(y));
    printf("pair_gets(): %c | ERROR: %s\n", y, ds_error(errno));

    errno = pair_free(&pair);
    printf("pair_free() | ERROR: %s\n", ds_error(errno));

    return 0;
}

