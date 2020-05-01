#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "programhandler.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/prctl.h>
#include <signal.h>

// returns an int that represents the
// extension of the program file
prog_extn find_file_extension(char * file_name)
{
    char * point_place = strrchr(file_name, '.');
    if(strcmp(point_place, ".c") == 0)
        return C;

    else if(strcmp(point_place, ".cpp") == 0)
        return CPP;

    else if(strcmp(point_place, ".cs") == 0)
        return CS;

    else if(strcmp(point_place, ".py") == 0)
        return PYTHON;

    else if(strcmp(point_place, ".java") == 0)
        return JAVA;

    else if(strcmp(point_place, ".exe") == 0)
        return 2;

    else
        return NOT_SUPPORTED;
}

char * get_program_stdout(char * program_path, prog_extn ext, 
        char * input)
{
    char * res;
    switch(ext)
    {
        case PYTHON:
            res = handle_python_program(program_path, input);
            break;
        default:
            return res;
    }
}

char * handle_python_program(char * program_path, char * input)
{
    fprintf(stdout, "Getting program results");
    pid_t pid = 0; 
    int inpipefd[2];
    int outpipefd[2];
    pipe(inpipefd);
    pipe(outpipefd);
    pid = fork();

    if(pid < 0){ fprintf(stdout, "Forking failed"); exit(EXIT_FAILURE); }
    else if(pid == 0)
    {
        close(outpipefd[1]);
        close(inpipefd[0]);
        // Child
        dup2(outpipefd[0], STDIN_FILENO);
        dup2(inpipefd[1], STDOUT_FILENO);

        execl(program_path, NULL);

        exit(EXIT_SUCCESS);
    }

    close(outpipefd[0]);
    close(inpipefd[1]);
    
    write(outpipefd[1], input, strlen(input));
    char * res = malloc(sizeof(*res));
    char * line = NULL;
    size_t line_sz;
    
    FILE * inpipefd_ptr = fdopen(inpipefd[0], "r");
    while(getline(&line, &line_sz,inpipefd_ptr) > 0)
    {
        strcat(res, line);
        line = NULL;
    } 
    free(inpipefd_ptr);
    close(outpipefd[1]);
    close(inpipefd[0]);

    return res;
}


