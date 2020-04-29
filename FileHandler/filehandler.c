#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

// reads input file and return a char ** 
// each for each line in input file
//
// gets absolut/relative input file path
// and a pointer to line numbers in it
// 
// line numbers will be set to ln after
// reading is finished
char ** read_file(char * file_path, int * ln)
{
    FILE * input_file = fopen(file_path, "r");
    if(input_file == NULL) { fprintf(stderr, "input_file %s, not found", file_path); exit(EXIT_FAILURE);}
    char ** inp = malloc(sizeof(*inp));
    char * line = NULL;
    size_t sz;
    int line_num = 0;
    char * n_pos = NULL;
    while(getline(&line, &sz, input_file) >= 0)
    {
        line_num++;
        inp = realloc(inp, line_num * sizeof(*inp));
        if((n_pos = strchr(line, '\r')) != NULL)
            *n_pos = '\0';
        inp[line_num - 1] = line;
        line = NULL;
        n_pos = NULL;
    }
    free(line);
    fclose(input_file);
    if(n_pos != NULL)
        free(n_pos);
    *ln = line_num;
    if(*ln == 0)
        return NULL;
    return inp;
}


