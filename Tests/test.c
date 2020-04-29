#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


char ** read_file(char * file_path, int * ln);

void read_file_test()
{
    fprintf(stdout, "starting filehandler.c->read_file_test\n");

    // test 1
    char fp1[] = { "./tests_dir/In_1.txt" }; 
    int fln1 __attribute__((unused)) = 0;
    char ** test1 = read_file(fp1, &fln1);
    assert(strcmp(test1[0], "4") == 0);
    assert(strcmp(test1[1], "0 0") == 0);
    assert(strcmp(test1[2], "0 1") == 0);
    assert(strcmp(test1[3], "1 0") == 0);
    assert(strcmp(test1[4], "1 1") == 0);
    assert(fln1 == 5);

    // test 2
    char fp2[] = { "./tests_dir/In_2.txt" }; 
    int fln2 __attribute__((unused)) = 0;
    char ** test2 = read_file(fp2, &fln2);
    assert(test2 == NULL);
    fprintf(stdout, "%s\n", "*test successfully finished*");

}

int main()
{
    // FileHandler tests
    // read_input
    read_file_test();

    return EXIT_SUCCESS;
}

