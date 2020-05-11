#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "programhandler.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

// returns an int that represents the
// extension of the program file
prog_extn find_program_extension(char * program_path)
{
    char * point_place = strrchr(program_path, '.');
    if(strcmp(point_place, ".py") == 0)
        return PYTHON;

    else if(strcmp(point_place, ".java") == 0)
        return JAVA;

    else
    {
        struct stat buf;
        if(stat(program_path, &buf) != 0)
        {
            return NOT_SUPPORTED;
        }

        // Executable
        else
        {
            // Check the `st_mode` field to see if the `S_IXUSR` bit is set
            if(buf.st_mode & S_IXUSR)
            {
                // Executable by user
                return EXECUTABLE;
            }
            else
            {
                return USERPROBLEM;
            }
        }

    }
}

// gets the program stdout in according 
// to it's extension
char * get_program_stdout(char * program_path, prog_extn ext, 
        char * input)
{
    char * res = "";
    switch(ext)
    {
        case PYTHON:
            res = handle_program("python3", program_path, input);
            break;
        default:
            return res;
    }
    return res;
}

// gives the input string to child
// process by the pipe and gets the
// output through another pipe
// and returns it
char * handle_program(char * path_variable, char * program_path, char * input)
{
    fprintf(stdout, "Getting program results\n");
    pid_t pid; 
    int inpipefd[2];
    int outpipefd[2];
    pipe(inpipefd);
    pipe(outpipefd);
    pid = fork();

    if(pid < 0){ fprintf(stdout, "Forking failed"); exit(EXIT_FAILURE); }

    else if(pid == 0)
    {
        // Child
        close(inpipefd[1]);
        close(outpipefd[0]);
        dup2(outpipefd[1], STDOUT_FILENO);
        dup2(inpipefd[0], STDIN_FILENO);
        waitpid(inpipefd[0], NULL, 0);

        execlp(path_variable, path_variable, program_path, NULL);

        exit(EXIT_SUCCESS);
    }

    close(outpipefd[1]);
    close(inpipefd[0]);
    
    write(inpipefd[1], input, strlen(input) + 1);
    close(inpipefd[1]);
    waitpid(pid, NULL, 0);

    char * res = malloc(sizeof(*res));
    char c;
    int i = 0;
    
    while(read(outpipefd[0], &c, 1) > 0)
    {
        if(c == '\r')
            c = '\n';
        res = realloc(res, (i + 1) * sizeof(*res));
        res[i] = c;
        i++;
    }
    if(i == 0)
        return NULL;
    res = realloc(res, (i + 1) * sizeof(*res));
    res[i] = '\0';

    close(outpipefd[0]);

    return res;
}


