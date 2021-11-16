#include <stdio.h>
#include <stdlib.h>

#define MAX_CHARS 20

int main(int argc, char** argv)
{
    // 22 znakow = 20 znaków + znak '\0' + znak '\n'
    char name[MAX_CHARS+2];
    // wczytujemy MAX_CHARS-1 znaków do zmiennej name z strumienia stdin
    while(fgets(name, MAX_CHARS+2, stdin) != NULL)
    {
        printf("Hello %s", name);
    }    

    return EXIT_SUCCESS;
}