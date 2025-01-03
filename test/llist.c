#include <stdio.h>

#define DS_IMPLEMENTATION
#include "ds.h"

int main()
{
    llist_t llist;
    int errno = llist_init(&llist);
    printf("llist_init() | ERROR: %s\n", ds_error(errno));

    int a = -1;
    errno = llist_front(&llist, &a, sizeof(a));
    printf("llist_front(): %d | ERROR: %s\n", a, ds_error(errno));
    if (errno != DS_EMPTY_ERR)
    {
	printf("Was expecting DS_EMPTY_ERR\n");
	exit(1);
    }

    a = -1;
    errno = llist_back(&llist, &a, sizeof(a));
    printf("llist_back(): %d | ERROR: %s\n", a, ds_error(errno));
    if (errno != DS_EMPTY_ERR)
    {
	printf("Was expecting DS_EMPTY_ERR\n");
	exit(1);
    }

    printf("-- llist_pushb() --\n");
    for (int i = 0; i < 10; i++)
    {
	errno = llist_pushb(&llist, &i, sizeof(i));
	printf("llist_pushb(%d) | ERROR: %s\n", i, ds_error(errno));
	errno = llist_back(&llist, &a, sizeof(a));
	printf("llist_back(): %d | ERROR: %s\n", a, ds_error(errno));
	if (errno != DS_NO_ERR)
	{
	    printf("Was expecting DS_NO_ERR\n");
	    exit(1);
	}
	errno = llist_front(&llist, &a, sizeof(a));
	printf("llist_front(): %d | ERROR: %s\n", a, ds_error(errno));
	if (errno != DS_NO_ERR)
	{
	    printf("Was expecting DS_NO_ERR\n");
	    exit(1);
	}
    }

    printf("-- llist_popb() --\n");
    for (int i = 0; i < 10; i++)
    {
	errno = llist_back(&llist, &a, sizeof(a));
	printf("llist_back(): %d | ERROR: %s\n", a, ds_error(errno));
	if (errno != DS_NO_ERR)
	{
	    printf("Was expecting DS_NO_ERR\n");
	    exit(1);
	}
	errno = llist_front(&llist, &a, sizeof(a));
	printf("llist_front(): %d | ERROR: %s\n", a, ds_error(errno));
	if (errno != DS_NO_ERR)
	{
	    printf("Was expecting DS_NO_ERR\n");
	    exit(1);
	}
	errno = llist_popb(&llist);
	printf("llist_popb() | ERROR: %s\n", ds_error(errno));
    }

    a = -1;
    errno = llist_front(&llist, &a, sizeof(a));
    printf("llist_front(): %d | ERROR: %s\n", a, ds_error(errno));
    if (errno != DS_EMPTY_ERR)
    {
	printf("Was expecting DS_EMPTY_ERR\n");
	exit(1);
    }

    a = -1;
    errno = llist_back(&llist, &a, sizeof(a));
    printf("llist_back(): %d | ERROR: %s\n", a, ds_error(errno));
    if (errno != DS_EMPTY_ERR)
    {
	printf("Was expecting DS_EMPTY_ERR\n");
	exit(1);
    }

    printf("-- llist_pushf() --\n");
    for (int i = 0; i < 10; i++)
    {
	errno = llist_pushf(&llist, &i, sizeof(i));
	printf("llist_pushf(%d) | ERROR: %s\n", i, ds_error(errno));
	errno = llist_back(&llist, &a, sizeof(a));
	printf("llist_back(): %d | ERROR: %s\n", a, ds_error(errno));
	if (errno != DS_NO_ERR)
	{
	    printf("Was expecting DS_NO_ERR\n");
	    exit(1);
	}
	errno = llist_front(&llist, &a, sizeof(a));
	printf("llist_front(): %d | ERROR: %s\n", a, ds_error(errno));
	if (errno != DS_NO_ERR)
	{
	    printf("Was expecting DS_NO_ERR\n");
	    exit(1);
	}
    }

    printf("-- llist_popf() --\n");
    for (int i = 0; i < 10; i++)
    {
	errno = llist_back(&llist, &a, sizeof(a));
	printf("llist_back(): %d | ERROR: %s\n", a, ds_error(errno));
	if (errno != DS_NO_ERR)
	{
	    printf("Was expecting DS_NO_ERR\n");
	    exit(1);
	}
	errno = llist_front(&llist, &a, sizeof(a));
	printf("llist_front(): %d | ERROR: %s\n", a, ds_error(errno));
	if (errno != DS_NO_ERR)
	{
	    printf("Was expecting DS_NO_ERR\n");
	    exit(1);
	}
	errno = llist_popf(&llist);
	printf("llist_popf() | ERROR: %s\n", ds_error(errno));
    }

    errno = llist_free(&llist);
    printf("llist_free() | ERROR: %s\n", ds_error(errno));

    return 0;
}
