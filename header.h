#ifndef HEADER_H
#define HEADER_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <string.h>

void err_cd_arg(void);
void err_cd_fail(char *path_to_change);
void err_cmd_fail(char *executable_that_failed);

#endif

// gcc -Wall -Werror -Wextra -o microshell main.c err_msg.c

/* Test case

Basic command
=================
./microshell
./microshell ";" ";" 
./microshell /bin/echo OK
./microshell /usr/bin/cat main.c
./microshell ls ";" /bin/echo ERROR

cd
====
./microshell cd
./microshell cd path1 path2
./microshell cd invalid_path
./microshell /bin/mkdir new ";" cd new ";" /bin/touch hello.txt ";" /bin/ls ";" /bin/pwd
./microshell /bin/rm -r new

pipe
=======
./microshell /bin/ls | /bin/grep micro | /bin/tr a-z A-Z | /bin/wc -l 
./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell

./microshell hantu "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell

 ./microshell /bin/cat "|" /bin/cat "|" /bin/cat "|" /bin/ls
*/