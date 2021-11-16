#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

#define MAXFD 20
#define ERR(source) (perror(source),\
                     fprintf(stderr, "%s:%d\n", __FILE__, __LINE__),\
                     exit(EXIT_FAILURE))

void usage(const char* pname) {
    printf("USAGE: %s -p PATH [-t TYPE] [-s SIZE] [-f FILE] ...", pname);
    exit(EXIT_FAILURE);
}

int type_flag;
mode_t ftype;
int walk(const char* path, const struct stat* buf, int tflag, struct FTW* f) {
    
    if(type_flag == 1 && ftype == buf->st_mode) {
        fprintf(stdout, "%s\n", path);
        return 0;
    } 
    fprintf(stdout, "%s\n", path);    
    return 0;
}   


int main(int argc, char** argv) {

    int o;
    int path_flag=0;
    type_flag=0;
    char* dir_path=NULL;
    char* type_ch=NULL;

    

    while((o = getopt(argc, argv, "p:t:")) != -1) {
        switch(o) {
            case 'p':
                dir_path = optarg;
                path_flag++;
                if(path_flag > 1) usage(argv[0]);
                break;
            case 't':
                type_ch = optarg;
                if(strcmp(type_ch, "d") == 0) 
                    ftype = S_IFDIR;
                else if(strcmp(type_ch, "r") == 0)
                    ftype = S_IFREG;
                else if(strcmp(type_ch, "s") == 0)
                    ftype = S_IFLNK;
                else
                    ERR("Wrong type");
                type_flag++;
                if(type_flag > 1) usage(argv[0]);
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
    if(path_flag == 0) usage(argv[0]);
    if(nftw(dir_path, walk, MAXFD, FTW_PHYS) != 0)


    return EXIT_SUCCESS;
}
