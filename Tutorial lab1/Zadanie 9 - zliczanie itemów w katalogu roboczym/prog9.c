#include <stdlib.h>
#include <stdio.h>
/* For managing directories */
#include <dirent.h>
/* For getting stats of files */
#include <sys/stat.h>
/* IT IS NEEDED */
#include <errno.h>

#define ERR(message)   (perror(message),\
                        fprintf(stderr, "%s:%d\n", __FILE__, __LINE__),\
                        exit(EXIT_FAILURE))

void scan_dir();

int main(int argc, char** argv) {
    
    scan_dir();

    return EXIT_SUCCESS;
}

void scan_dir() {
    /* Directory pointer */
    DIR* dir;
    struct dirent* dp;
    struct stat stat_buf;

    int dirs=0, files=0, links=0, other=0;

    /* Open current woring directory */
    if((dir = opendir(".")) == NULL) ERR("Cant open .");


    do {
        /*
            Jeżeli funkcja dobrze się wykonała, to errno jest wg man 3p errno UNSPECIFIED
        */
        errno = 0;
        if((dp = readdir(dir)) != NULL) {
            /*
                Zdobywamy staty (lstat, bo chcemy policzyć linki, a nie pliki na które one wskazują)
                o pliku o nazwie dp->d_name.
                Przechowujemy te informacje w struct stat_buf.
            */
            /*
                To sprawdzenie nie ma tutaj sensu. Dlaczego?
                Gdy readdir wywali Errora, to zwraca NULL
                Gdy readdir dobrze się wykona, to też zwraca NULL
                Czyli w sytuacji błędu, nie wykona się nigdy kod poniżej.

                if(errno != 0) ERR("readir");
            */
            if(lstat(dp->d_name, &stat_buf) != 0) ERR("lstat");
            /*
                Sprawdzamy za pomocą makr typy plików.
            */
            if(S_ISDIR(stat_buf.st_mode)) dirs++;
            else if(S_ISREG(stat_buf.st_mode)) files++;
            else if(S_ISLNK(stat_buf.st_mode)) links++;
            else other++;
        }
    } while(dp != NULL);
    /*
        Tylko readdir mógł zmienić wartość errno w pętli
        Dlaczego tutaj sprawdzamy? Patrz do pętli do..while
    */
    if(errno != 0) ERR("readir");

    printf("In . directory there are:\n%3d directories\n%3d files\n%3d links\n%3d others\n", dirs, files, links, other);

    if(closedir(dir) != 0) ERR("closedir");
}