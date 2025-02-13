#include "microshell.h"

void execute(char **arg, int i, char **env)
{ 
    if (fork() == 0)
    {
        arg[i] = NULL;
        execve(arg[0], arg, env);
        err_cmd_fail(arg[0]);
        exit(EXIT_FAILURE);
    }
    else
        waitpid(-1, NULL, 0);
}

void do_pipe(char **arg, int i, char **env)
{
    int fd[2];

    pipe(fd);
    if (fork() == 0)
    {
        arg[i] = NULL;
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execve(arg[0], arg, env);
        err_cmd_fail(arg[0]);
        exit(EXIT_FAILURE);
    }

    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    waitpid(-1, NULL, 0);
}

void handle_cd(char **arg, int i)
{
    if (i != 2)
        err_cd_arg();
    else if (chdir(arg[1]))
        err_cd_fail(arg[1]);
}

int main(int ac, char **av, char **env)
{
    int i = 0;
    (void)ac;

    while (av[i] && av[i + 1])
    {
        av = &av[i + 1];
        i = 0;

        while (av[i] && strcmp(av[i], ";") && strcmp(av[i], "|"))
            i++;

        if (!strcmp(av[0], "cd"))
            handle_cd(av, i);

        else if (i > 0 && (!av[i] || !strcmp(av[i], ";")))
            execute(av, i, env);

        else if (i > 0 && !strcmp(av[i], "|"))
            do_pipe(av, i, env);
    }
}

/*
Test cases

Basic argument (Absoulte & relative path)
=========================================

./microshell
./microshell /bin/ls
./microshell /bin/echo OK
./microshell /usr/bin/echo OK
./microshell echo ERROR ";" /bin/echo ERROR
./microshell /bin/cat microshell.c

Never try "|" immediately followed or preceded by nothing or "|" or ";" (But everything in between)
=======================================================================================================

./microshell ";"
./microshell ";" /bin/echo OK ";"
./microshell cd ";"
./microshell /bin/echo -n Try this ";"

cd built-in
============
./microshell cd 
./microshell cd path1 path2
./microshell cd invalid_path
./microshell /bin/mkdir new ";" cd new ";" /bin/touch hello.txt ";" /bin/ls ";" /bin/pwd
./microshell ";" /bin/rm -r new



Fail execution
=====================
./microshell cd dsadad ";" /bin/ls -l
./microshell wrong_executable ";" not_correct ";" /bin/pwd ";" /bin/ls -l

Pipes
===============
./microshell /bin/ls "|" /usr/bin/grep micro "|" /bin/tr a-z A-Z "|" /bin/wc -l
./microshell /bin/echo Hello World "|" /bin/tr a-z A-Z
./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell
./microshell blah "|" /bin/echo OK ";"
test_line /bin/ls ewqew "|" /usr/bin/grep micro "|" /bin/cat -n ";" /bin/echo dernier ";" /bin/echo

./microshell /bin/ls "|" /usr/bin/grep microshell "|" /usr/bin/grep micro "|" /usr/bin/grep shell "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro


*/