#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>

#define MAX_PATH 300

#define ERR(source)(perror(source),\
                    fprintf(stderr, "%s:%d", __FILE__, __LINE__),\
                    exit(EXIT_FAILURE))


void scan_dir();
int main(int argc, char** argv)
{
    /*  Dir gdzie znajduje się nasz program. Jeśli tego nie podamy, to program nie wróci do położenia
        z którego zaczynał, czyli wywołanie programu
        $ ./prog10 dir1 dir2 
        nie powiedzie się, ponieważ program wejdzie do dir1 zrobi co ma zrobić, ale nie będzie umiał wrócić tak,
        aby przeszukać dir2.
    */
    char root_dir_path [MAX_PATH];
    /* Jeżeli nie podaliśmy dir to wychodzimy */
    if(argc == 1) ERR("No folder(s) entered");
    /* Bierzemy pwd i zapisujemy w root_dir_path o rozmiarze MAX_PATH bajtów */
    if(getcwd(root_dir_path, MAX_PATH) == NULL) ERR("getcwd");

    for (int i = 1; i < argc; i++)
    {
        /* sprawdzamy, czy można wejsc do dir określonego w argumencie */
        if(chdir(argv[i]) != 0) ERR("chdir");
        printf("Contents of %s:\n", argv[i]);
        scan_dir();
        /* Można, ale to nam ogranicza działanie programu */
        /* if(chdir("..") != 0) ERR("chdir"); */
        /* 
            To pozwala nam wpisać pełną ścieżkę do folderu, którego chcemy przeszukać, np:
            $ .prog10/home/szymon/My\ files/Programming\ projects/   
        */
        if(chdir(root_dir_path) != 0) ERR("chdir");
    }
    
    return EXIT_SUCCESS;
}

/* Przeszukuje pwd */
void scan_dir()
{
    DIR* dir;
    struct dirent* dirp;
    struct stat sp;

    int dirs=0, files=0, links=0, others=0;

    if((dir = opendir(".")) == NULL) ERR("opendir");

    do {
        errno = 0;
        if((dirp = readdir(dir)) != NULL) {
            if(lstat(dirp->d_name, &sp) != 0) ERR("lstat");
            if(S_ISDIR(sp.st_mode)) dirs++;
            else if(S_ISREG(sp.st_mode)) files++;
            else if(S_ISLNK(sp.st_mode)) links++;
            else others++;
        }

    } while(dirp != NULL);
    if(errno != 0) ERR("readdir");
    if(closedir(dir) != 0) ERR("closedir");

    printf("  directories=%d\n  files=%d\n  links=%d\n  others=%d\n", dirs, files, links, others);
}