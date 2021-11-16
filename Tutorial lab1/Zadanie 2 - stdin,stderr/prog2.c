#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 20

int main(int argc, char** argv)
{
    // 20 chars + '\0' sign + one letter to check if user
    // entered >20 characters
    char name[MAX_LENGTH+2];

    scanf("%21s", name);
    // strlen ignores '\0'
    if(strlen(name) > MAX_LENGTH)
    {
        perror("Name too long");
        fprintf(stderr, "%s:%d\n", __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }
    printf("Hello %s :)\n", name);


    return EXIT_SUCCESS;
}