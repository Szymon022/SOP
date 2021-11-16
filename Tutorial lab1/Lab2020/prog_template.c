#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

#define ERR(source) (perror(source),\
                     fprintf(stderr, "%s:%d\n", __FILE__, __LINE__),\
                     exit(EXIT_FAILURE))

void usage(const char* pname) {
    fprintf("USAGE: %s -p PATH [-t TYPE] [-s SIZE] [-f FILE] ...");
    exit(EXIT_FAILURE);
}

int main(int argc, char** argv) {


    return EXIT_SUCCESS;
}
