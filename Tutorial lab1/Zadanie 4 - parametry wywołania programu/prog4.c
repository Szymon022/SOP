#include <stdio.h>
#include <stdlib.h>

/* 
    Aby przekazać imiona z pliku dane.txt jako parametry do naszego programu
    musimy użyć "xargs". Możemy to zrobić na 2 sposoby:
    1: cat dane.txt | xargs ./prog4                         ==> każdy WYRAZ to oddzielny argument
    2: cat dane.txt | tr "\n" "\0" | xargs -0 ./prog4       ==> każda LINIA to oddzielny argument
                      ^    ^    ^           ^
                      |    |    |           |
        zamieniamy znak "\n" na "\0"    od teraz paramatry są oddzielane znakiem null "\0"

*/

int main(int argc, char** argv)
{
    for (int i = 0; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }

    return EXIT_SUCCESS;   
    
}