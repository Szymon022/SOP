#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 20

void print_hello_name(char* name, int times);

int main(int agrc, char** argv)
{
    char* times_char = getenv("TIMES");
    /*
        Sprawdzamy czy zmienna TIMES w ogóle istnieje
    */
    int times = 1;
    if(times_char) times = atoi(times_char);
    char name[MAX_LENGTH+2];

    while(fgets(name, MAX_LENGTH+2, stdin) != NULL)
    {
        print_hello_name(name, times);
    } 

    /*
        Jeżeli udało się dodać zmienną środowiskową RESULT to super
        Jeżeli się NIE udało, to wypisujemy error i kończymy program
    */
    if(putenv("RESULT=DONE") != 0)
    {
        fprintf(stderr, "putenv failed");
        return EXIT_FAILURE;
    }
    /*
        Wypisujemy zmienną RESULT.
        Sprawdzamy, czy faktycznie zmienna RESULT pojawiła się w zmiennych
        środowiskowych grepem. Funkcja system zwraca nam kody zakończenia programu,
        który wywołuje. Czyli inna wartość niż 0 oznacza błąd wykonania => zmiennej nie znaleziono.
    */
    printf("%s\n", getenv("RESULT"));
    if(system("env | grep RESULT") != 0)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

/*
    Wypisanie imienia times razy
*/
void print_hello_name(char* name, int times)
{
    for (int i = 0 ; i < times; i++)
    {
        printf("HELLO %s", name);
    }
    
}