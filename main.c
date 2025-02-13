#include "header.h"

void handle_cd(char **arg, int i)
{
    if (i != 2)
        err_cd_arg();
    else if (chdir(arg[1]))
        err_cd_fail(arg[1]);
}

void execute(char **arg, int i, char **env)
{
    if (!fork())
    {
        arg[i] = NULL;
        execve(arg[0], arg, env);
        err_cmd_fail(arg[0]);
        exit(EXIT_FAILURE);
    }
    waitpid(-1, NULL, 0);
}

void do_pipe(char **arg, int i, char **env)
{
    int fd[2];
    pipe(fd);
    
    if (!fork())
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