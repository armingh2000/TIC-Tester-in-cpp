#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../FileHandler/filehandler.h"
#include "test.h"
#include "../ProgramHandler/programhandler.h"


void read_file_test()
{
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
}

void free_read_file_test()
{

    // test 1
    char fp1[] = { "./tests_dir/In_1.txt" }; 
    int fln1 = 0;
    char ** test1 = read_file(fp1, &fln1);
    free_read_file(test1, fln1);

    // test 2
    char fp2[] = { "./tests_dir/In_2.txt" }; 
    int fln2 = 0;
    char ** test2 = read_file(fp2, &fln2);
    free_read_file(test2, fln2);

}

void find_file_extension_test()
{
    // test 1
    char fp1[] = { "./tests_dir/prog1.py" }; 
    assert(find_program_extension(fp1) == PYTHON);

    char fp2[] = { "./tests_dir/prog2.F" };
    assert(find_program_extension(fp2) == NOT_SUPPORTED);

}

void handle_python_program_test()
{
     char fp1[] = { "./tests_dir/python_test1.py" };
     char * res1 = get_program_stdout(fp1, PYTHON, "STDIN CHECK");
     assert(strcmp(res1, "STDIN CHECK") == 0);
     free(res1);

     char fp2[] = { "./tests_dir/python_test2.py" };
     char * res2 = get_program_stdout(fp2, PYTHON, "STDOUT CHECK");
     assert(strcmp(res2, "STDOUT CHECK") == 0);
     free(res2);

     char fp3[] = { "./tests_dir/python_test3.py" };
     char * res3 = get_program_stdout(fp3, PYTHON, "");
     assert(res3 == NULL);
}

void handle_executable_program_test()
{
    char fp1[] = { "./tests_dir/executable_test1" };
    char * res1 = get_program_stdout(fp1, EXECUTABLE, "");
    assert(strcmp(res1, "This is C code\n") == 0);
    free(res1);

    char fp2[] = { "./tests_dir/executable_test2" };
    char * res2 = get_program_stdout(fp2, EXECUTABLE, "TEST INPUT");
    assert(strcmp(res2, "you wrote TEST INPUT") == 0);
    free(res2);
}

void handle_java_program_test()
{
    char fp1[] = { "./tests_dir/Simple" };
    char * res1 = get_program_stdout(fp1, JAVA, "");
    printf("%s", res1);
    free(res1);
}

void split_program_path_test(char * program_path)
{
    char * test1 = "./tests_dir/Simple.class";
    char ** res1 = split_program_path(test1);
    assert(strcmp(res1[0], "Simple.class") == 0);
    assert(strcmp(res1[1], "./tests_dir/") == 0);
    free_read_file(res1, 2);

    char * test2 = "./temp.test";
    char ** res2 = split_program_path(test2);
    //printf("%s\n", res2[0]);
    //printf("%s\n", res2[1]);
    assert(strcmp(res2[0], "temp.test") == 0);
    assert(strcmp(res2[1], "./") == 0);
    free_read_file(res2, 2);
}

int main(int argc, char ** argv)
{
    fprintf(stdout, "Two options availabe :\n");
    fprintf(stdout, "   1- run all tests\n");
    fprintf(stdout, "   2- run specific tests one by one with your selevtion\n");
    fprintf(stdout, "   3- run specific tests with name (Not implemented yet)\n");
    fprintf(stdout, "Which option do you want (1, 2, 3): ");
    char * opt = NULL;
    size_t opt_size;
    getline(&opt, &opt_size, stdin);

    if(*opt == '1')
    {
        int func_nums = 7;
        char * func_names[] = { "read_file", "free_read_file", 
            "find_file_extension", "handle_python_program", 
            "handle_executable_program", "handle_java_prgoram",
            "split_program_path" };

        void (*funcs[])() = { &read_file_test, &free_read_file_test,
            &find_file_extension_test, &handle_python_program_test,
            &handle_executable_program_test, &handle_java_program_test, 
            &split_program_path_test };

        for(int i = 0; i < func_nums; i++)
        {
            fprintf(stdout, "\tstarting '%s_test'\n", func_names[i]);
            (*(funcs[i]))();
            fprintf(stdout, "\t\t*test successfully finished*\n\n");
        }
    }
    else if(*opt == '2')
    {
        fprintf(stdout, "If you want to run a test write y, everything else will be considered as no\n\n");
        int func_nums = 5;
        char * func_names[] = { "read_file", "free_read_file", 
            "find_file_extension", "handle_python_program", 
            "handle_executable_program" };

        void (*funcs[])() = { &read_file_test, &free_read_file_test,
            &find_file_extension_test, &handle_python_program_test,
            &handle_executable_program_test };
        char * line = NULL;
        size_t line_sz;

        for(int i = 0; i < func_nums; i++)
        {
            fprintf(stdout, "Do you want to run '%s_test' test?", func_names[i]);
            getline(&line, &line_sz, stdin);

            if(strcmp(line, "y\n") == 0)
            {
                fprintf(stdout, "\tstarting '%s_test'\n", func_names[i]);
                (*(funcs[i]))();
                fprintf(stdout, "\t\t*test successfully finished*\n\n");
            }
            else
            {
                fprintf(stdout, "\t--Test '%s_test' didn't run--\n\n", func_names[i]);
                continue;
            }
        }

        free(line);
    }

    free(opt);
    return EXIT_SUCCESS;
}

