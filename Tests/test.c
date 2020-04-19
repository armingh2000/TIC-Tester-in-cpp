#include <stdio.h>
#include <stdlib.h>


char ** read_input(char * file_path, int * ln);

void read_input_test()
{
    char fp[] = { "./tests_dir/In_1.txt" }; 
    int __attribute__((unused)) fln = 0;
    char ** test1 = read_input(fp, &fln);
    for(int i = 0; i < fln; i++)
    {
        printf("%s\n", test1[i]);
    }
    printf("%d", fln);

}

int main()
{
    // FileHandler tests

    // read_input
    read_input_test();

    return EXIT_SUCCESS;
}

