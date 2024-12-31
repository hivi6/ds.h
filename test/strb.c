#include <stdio.h>

#define DS_IMPLEMENTATION
#include "ds.h"

int main()
{
    strb_t strb;
    int errno = strb_init(&strb);
    printf("strb_init() | ERROR: %s\n", ds_error(errno));

    for (int i = 0; i < 26; i++)
    {
	errno = strb_appendc(&strb, 'a' + i);
	printf("strb_appendc(%c) | LEN: %d | ERROR: %s | STR: ", 'a' + i, 
	       strb.chars.cnt, ds_error(errno));
	char *str;
	strb_build(&strb, &str);
	printf("%s\n", str);
	free(str);
    }

    for (int i = 0; strb.chars.cnt; i++)
    {
	for (int j = 0; j < 5; j++)
	{
	    errno = strb_pop(&strb);
	    printf("strb_pop() | LEN: %d | ERROR: %s | STR: ", strb.chars.cnt, 
		   ds_error(errno));
	    char *str;
	    strb_build(&strb, &str);
	    printf("%s\n", str);
	    free(str);
	}
    }

    const char *cstr = "this is a string!";
    strb_append(&strb, cstr);
    char *str;
    errno = strb_build(&strb, &str);
    printf("strb_append(%s) | LEN: %d | ERROR: %s | STR: %s\n", cstr, 
	   strb.chars.cnt, ds_error(errno), str);
    free(str);

    for (int i = 0; strb.chars.cnt; i++)
    {
	for (int j = 0; j < 5; j++)
	{
	    errno = strb_pop(&strb);
	    printf("strb_pop() | LEN: %d | ERROR: %s | STR: ", strb.chars.cnt, 
		   ds_error(errno));
	    char *str;
	    strb_build(&strb, &str);
	    printf("%s\n", str);
	    free(str);
	}
    }

    strb_free(&strb);
    printf("strb_free() | ERROR: %s\n", ds_error(errno));

    return 0;
}
