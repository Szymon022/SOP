#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    if(argc < 3) 
    {
        perror("Not enough arguments");
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[2]);
    if(n == 0) 
    {
        perror("Invalid number");
        exit(EXIT_FAILURE);
    }

    char* name = argv[1];

    for (int i = 0; i < n; i++)
    {
        printf("%s\n", name);
    }
    
    return EXIT_SUCCESS;
}