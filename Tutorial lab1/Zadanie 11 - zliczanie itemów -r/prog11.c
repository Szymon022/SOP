/* KONIECZNIE MUSI TAK BYĆ !!! */
#define _XOPEN_SOURCE 500
#include <ftw.h>
/* DOPIERO TUTAJ DAJEMY RESZTĘ */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXFD 20

#define ERR(message) (  perror(message),\
                        fprintf(stderr, "%s:%d", __FILE__, __LINE__),\
                        exit(EXIT_FAILURE))

int dirs=0, files=0, links=0, others=0;


int walk(const char* fpath, const struct stat *sb, int type, struct FTW *f) {
    /*
        Więcej o typach w 
        $ man 0p ftw.h
    */
    switch(type) {
        /* Plik niezdatny do odczytu */
        case FTW_DNR:
        /* Directory */
        case FTW_D: dirs++; break;
        /* File */
        case FTW_F: files++; break;
        /* Link */
        case FTW_SL: links++; break;
        /* Other */
        default: others++;
    }
    return 0;
}

int main(int argc, char** argv) {
    
    for(int i = 1; i < argc; i++) {
        /*
            Funkcja nftw wywołuje dla każdego pliku funkcję walk.
            MAXFD to maksymalna liczba deskryptorów.
            FTW_PHYS nie followuje linków tak jak to robi stat()
        */
        if(nftw(argv[i], walk, MAXFD, FTW_PHYS) == 0)
            printf("%s:\n  dirs=%d\n  files=%d\n  links=%d\n  others=%d\n",argv[i], dirs, files, links, others);
        else printf("%s: access denied\n", argv[i]);
        dirs=files=links=others=0;
    }
    return EXIT_SUCCESS;
}

