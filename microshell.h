
#ifndef MICROSHELL_H
#define MICROSHELL_H

//#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void err_cd_arg(void);
void err_cd_fail(char *path_to_change);
void err_cmd_fail(char *executable_that_failed);

#endif

// gcc -Wall -Werror -Wextra -o microshell microshell.c err_msg.c
