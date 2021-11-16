#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
    Jeśli chcemy wyłączyć komunikat: 'option requires an argument -- 'n''
    to musimy ustawić zmienną globalną opterr na 0.

    opterr = 0;    
*/

void usage(char* err_message);
void print_name(char* name, int n);

int main(int argc, char** argv)
{
    int option;
    char* name;
    int x = 1;

    while((option = getopt(argc, argv, "t:n:")) != -1)
    {
        switch (option)
        {
        case 't':
            x = atoi(optarg);
            break;
        
        case 'n':
            name = optarg;
            print_name(name, x);
            break;

        case ':':
            usage(argv[0]);
            break;

        case '?':
            usage(argv[0]);
            break;
        
        default:
            usage(argv[0]);
            break;
        }
        
    }
    if(argc > optind)
    {
        usage(argv[0]);
    }
    return EXIT_SUCCESS;
}

void usage(char* pname)
{
    fprintf(stderr, "USAGE: %s [-t x] -n name ... \n", pname);
    exit(EXIT_FAILURE);
}

void print_name(char* name, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s\n", name);
    }
    
}