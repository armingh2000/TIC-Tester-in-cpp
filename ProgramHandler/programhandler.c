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

// char ** get_program_result()
