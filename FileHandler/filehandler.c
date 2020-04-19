#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

// reads input file and return a char ** 
// each for each line in input file
//
// gets absolut/relative input file path
// and a pointer to line numbers in it
// 
// line numbers will be set to ln after
// reading is finished
char ** read_input(char * file_path, int * ln)
{
    FILE * input_file = fopen(file_path, "r");
    if(input_file == NULL) { fprintf(stderr, "input_file %s, not found", file_path); exit(EXIT_FAILURE);}
    char ** inp = malloc(sizeof(*inp));
    char * line = NULL;
    size_t sz;
    *ln = 0;
    while(getline(&line, &sz, input_file) >= 0)
    {
        *ln++;
        inp = realloc(inp, *ln * sizeof(*inp));
        inp[*ln - 1] = line;
        line = NULL;
    }
    free(line);
    fclose(input_file);
    return inp;
}


