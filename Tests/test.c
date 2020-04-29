#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "filehandler.h"
#include "test.h"


void read_file_test()
{
    fprintf(stdout, "starting filehandler.c->read_file_test\n");

    // test 1
    char fp1[] = { "./tests_dir/In_1.txt" }; 
    int fln1 = 0;
    char ** test1 = read_file(fp1, &fln1);
    assert(strcmp(test1[0], "4") == 0);
    assert(strcmp(test1[1], "0 0") == 0);
    assert(strcmp(test1[2], "0 1") == 0);
    assert(strcmp(test1[3], "1 0") == 0);
    assert(strcmp(test1[4], "1 1") == 0);
    assert(fln1 == 5);
    free_read_file(test1, fln1);

    // test 2
    char fp2[] = { "./tests_dir/In_2.txt" }; 
    int fln2 = 0;
    char ** test2 = read_file(fp2, &fln2);
    assert(test2 == NULL);
    free_read_file(test2, fln2);

    fprintf(stdout, "%s\n", "*test successfully finished*");
}

void free_read_file_test()
{
    fprintf(stdout, "starting filehandler.c->read_file_test\n");

    // test 1
    char fp1[] = { "./tests_dir/In_1.txt" }; 
    int fln1 = 0;
    char ** test1 = read_file(fp1, &fln1);
    free_read_file(test1, fln1);

    fprintf(stdout, "%s\n", "*test successfully finished*");
}

int main(int argc, char ** argv)
{

    if(argc == 1)
    {
    // FileHandler tests
    
    // read_file
    read_file_test();

    // free_read_file_test
    free_read_file_test();

    }
    else
    {
        if(strcmp(argv[1], "focused") != 0)
            fprintf(stderr, "Option invalid; Either leave it empty or write focused");

        int func_nums = 2;
        char * func_names[] = { "read_file", "free_read_file" };
        void (*funcs[])() = { &read_file_test, &free_read_file_test };
        char * line = NULL;
        size_t sz;

        for(int i = 0; i < func_nums; i++)
        {
            printf("Do you want to run '%s' test?", func_names[i]);
            if(getline(&line, &sz, stdin) > 0)
            {
                if(strcmp(line, "\n") == 0)
                {
                    (*(funcs[i]))();
                }
                else
                    continue;
            }
        }
        free(line);
    }
    return EXIT_SUCCESS;
}

