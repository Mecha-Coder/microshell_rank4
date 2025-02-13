#include "microshell.h"

static void put_err(char *s)
{
    while (s && *s)
        write(2, s++, 1);
}

void err_cd_arg(void)
{
    put_err("error: cd: bad arguments");
    put_err("\n");
}

void err_cd_fail(char *path_to_change)
{
    put_err("error: cd: cannot change directory to ");
    put_err(path_to_change);
    put_err("\n");
}

void err_cmd_fail(char *executable_that_failed)
{
    put_err("error: cannot execute ");
    put_err(executable_that_failed);
    put_err("\n");
}

/*
int main()
{
    err_cd_arg();
    put_err("\n-------------------------\n");
    err_cd_fail("<Invalid path>");
    put_err("\n-------------------------\n");
    err_cmd_fail("<Invalid command>");
}
*/