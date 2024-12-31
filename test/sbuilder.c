#include <stdio.h>

#define DS_IMPLEMENTATION
#include "ds.h"

int main()
{
    sbuilder_t sbuilder;
    int errno = sbuilder_init(&sbuilder);
    printf("sbuilder_init() | ERROR: %s\n", ds_error(errno));

    for (int i = 0; i < 26; i++)
    {
	errno = sbuilder_appendc(&sbuilder, 'a' + i);
	printf("sbuilder_appendc(%c) | LEN: %d | ERROR: %s | STR: ", 'a' + i, 
	       sbuilder.chars.cnt, ds_error(errno));
	char *str;
	sbuilder_build(&sbuilder, &str);
	printf("%s\n", str);
	free(str);
    }

    for (int i = 0; sbuilder.chars.cnt; i++)
    {
	for (int j = 0; j < 5; j++)
	{
	    errno = sbuilder_pop(&sbuilder);
	    printf("sbuilder_pop() | LEN: %d | ERROR: %s | STR: ", sbuilder.chars.cnt, 
		   ds_error(errno));
	    char *str;
	    sbuilder_build(&sbuilder, &str);
	    printf("%s\n", str);
	    free(str);
	}
    }

    const char *cstr = "this is a string!";
    sbuilder_append(&sbuilder, cstr);
    char *str;
    errno = sbuilder_build(&sbuilder, &str);
    printf("sbuilder_append(%s) | LEN: %d | ERROR: %s | STR: %s\n", cstr, 
	   sbuilder.chars.cnt, ds_error(errno), str);
    free(str);

    for (int i = 0; sbuilder.chars.cnt; i++)
    {
	for (int j = 0; j < 5; j++)
	{
	    errno = sbuilder_pop(&sbuilder);
	    printf("sbuilder_pop() | LEN: %d | ERROR: %s | STR: ", sbuilder.chars.cnt, 
		   ds_error(errno));
	    char *str;
	    sbuilder_build(&sbuilder, &str);
	    printf("%s\n", str);
	    free(str);
	}
    }

    sbuilder_free(&sbuilder);
    printf("sbuilder_free() | ERROR: %s\n", ds_error(errno));

    return 0;
}
