#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAXD 20
#define MAX_FILES 500
#define MAX_PATH 200
#define MAX_LENGTH 60
#define ERR(source) (perror(source),\
                    fprintf(stderr, "%s:%d", __FILE__, __LINE__),\
                    exit(EXIT_FAILURE))

struct file {
    char path[MAX_PATH];
    off_t size;
};

FILE* out;
struct file biggest_file;
char* key;
int Iflag;

int walk(const char* path, const struct stat* buf, int tflag, struct FTW* f) {
    
    uid_t uid = getuid(); 
    
    if(tflag != FTW_D && tflag != FTW_SL && uid == buf->st_uid) {
        if(Iflag == 1) {
            FILE* file = NULL;
            char line[MAX_LENGTH];
            if((file = fopen(path, "r")) == NULL) {
                fprintf(stderr, "Cant read %s", path);
                return 0;
            }
            if(fgets(line, MAX_LENGTH, file) != NULL) {
                if(strstr(line, key) != NULL) {
                    if(fclose(file) == EOF) ERR("fclose");
                    return 0;
                } 
            }

            if(fclose(file) == EOF) ERR("fclose");
        }
        if(biggest_file.size <= buf->st_size) {
            strcpy(biggest_file.path, path);
            biggest_file.size = buf->st_size;
        }
        fprintf(out, "%s\n", path);
    }   

    return 0;
}   

void usage(const char* prog) {
    fprintf(stderr, "USAGE: %s [-L IGNOREME] FILE1 FILE2 ...\n", prog);
    exit(EXIT_SUCCESS);
}

int main(int argc, char** argv) {

    int i=1, o;
    char* logfile=NULL; 
    int logflag=0;   
    key = NULL;
    Iflag=0;
    out = stdout;
    
    if((logfile = getenv("L1_LOGFILE")) != NULL) {
        if((out = fopen(logfile, "w")) == NULL) ERR("fopen");
        logflag=1;
    }

    while((o = getopt(argc, argv, "I:")) != -1) {
        switch (o)
        {
        case 'I':
            key = optarg;
            Iflag = 1;
            i = 3;
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

    for( ; i < argc; i++) {
        strcpy(biggest_file.path, "");
        biggest_file.size=0;

        fprintf(out, "Analizing %s\n", argv[i]);

        if(nftw(argv[i], walk, MAXD, FTW_PHYS) == -1) ERR("nftw");
        if(biggest_file.size == 0) 
            fprintf(out, "No files found in %s", argv[i]);
        else    
            printf("Largest file in %s: %s (%ld bytes)\n", argv[i], biggest_file.path, biggest_file.size);
        
    }

    if(logflag == 1) {
        if(fclose(out) == EOF) ERR("fclose");
    }   
    
    return EXIT_SUCCESS;
}