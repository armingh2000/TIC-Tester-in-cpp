#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

// reads input file and return a 
char ** read_input(char * file_path, int * ln)
{
    FILE * input_file = fopen(file_path, "r");
    if(input_file == NULL) { fprintf(stderr, "input_file %s, not found", file_path); exit(EXIT_FAILURE);}
    char ** inp = malloc(sizeof(*inp));
    char * line = NULL;
    size_t sz;
    int lines_number= 0;
    while(getline(&line, &sz, input_file) >= 0)
    {
        lines_number++;
        inp = realloc(inp, lines_number * sizeof(*inp));
        inp[lines_number - 1] = line;
        line = NULL;
    }
    free(line);
    fclose(input_file);
    return inp;
}


