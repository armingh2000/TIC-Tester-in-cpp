#include <stdio.h>
#include <stdlib.h>

int main()
{
    char str[100];
    fgets(str, sizeof(str), stdin);
    printf("you wrote %s", str);
    return EXIT_SUCCESS;
}
