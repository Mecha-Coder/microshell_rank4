#include "header.h"

void put_msg(char *s)
{
    while (s && *s)
        write(2, s++, 1);
}

void err_cd_arg(void)
{
    put_msg("error: cd: bad arguments");
    put_msg("\n");
}

void err_cd_fail(char *path_to_change)
{
    put_msg( "error: cd: cannot change directory to ");
    put_msg(path_to_change);
    put_msg("\n");
}

void err_cmd_fail(char *executable_that_failed)
{
    put_msg("error: cannot execute ");
    put_msg(executable_that_failed);
    put_msg("\n");
}