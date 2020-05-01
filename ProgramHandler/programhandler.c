#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "programhandler.h"

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

FILE * get_program_file_popen(char * program_path, prog_extn ext)
{
    switch(ext)
    {
        case PYTHON:
            ;
            char * run_command = { "python3 " };
            run_command = strcat(run_command, program_path);

            FILE * fp = popen(run_command, "w");
            if(fp == NULL) { fprintf(stderr, "File at path '%s' not found", program_path); exit(EXIT_FAILURE); }
            
            return fp;
            break;
        default:
            return NULL;
    }
}

void free_program_file_popen(FILE * p)
{
    pclose(p);
}

void give_std_input(FILE * program, char ** stdinp, int line_num)
{
    
}

