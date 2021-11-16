#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>


#define ERR(source) (perror(source),\
                    fprintf(stderr, "%s:%dn", __FILE__, __LINE__))

void usage(char* pname){
    fprintf(stderr, "USAGE: %s ([-o OUT_FILE] -p DIR_NAME) ...\n", pname);
    exit(EXIT_FAILURE);
}

int list_dir(FILE* out, char* dir_name) {
    DIR* dir;
    struct dirent* dp;
    struct stat st;
    char wd[MAX_INPUT];
    if(getcwd(wd, MAX_INPUT) == NULL) ERR("Cant get cwd");
    if(chdir(dir_name) != 0) ERR("Cant change dir");
    
    if((dir = opendir(dir_name)) == NULL) {
        ERR("Cant open directory");
        return -1;
    }
    if(out == NULL) return -1;
    fprintf(out, "SCIEZKA:\n%s\nLISTA PLIKOW:\n", dir_name);        
    do {
        errno=0;
        if((dp = readdir(dir)) != NULL) {
            
            if(stat(dp->d_name, &st) != 0) {
                fprintf(stderr, "Cant read file: %s\n", dp->d_name);
                continue;
            }
            
            fprintf(out, "%-40s%td\n", dp->d_name, st.st_size);
            
        }
    } while(dp != NULL);
    if(errno != 0) {
        ERR("readdir");
        return -1;
    }
    if(chdir(wd) != 0) ERR("Cant change dir");
    if(closedir(dir) == -1) ERR("closedir");
    fprintf(out, "---------------\n");
    
    return 0;
}

int main(int argc, char** argv) {

    int o=-1, outflag=0, path_flag=0;
    FILE* out=stdout;
    char* file_name=NULL;

    while((o = getopt(argc, argv, "p:o:")) != -1) {
        switch (o)
        {
        case 'p':
            /* Directory to list */

            list_dir(out, optarg);
            path_flag=1;
            break;
        case 'o':
            outflag++;
            file_name=optarg;
            if(outflag > 1) usage(argv[0]);
            if((out = fopen(file_name, "w")) == NULL) {
                ERR("Cant open file");
                out = stdout;
            } 
            break;        
        case ':':
            usage(argv[0]);
            break;
        case '?':
            usage(argv[0]);
        }
    }
    if(argc == 1 || 0 == path_flag) list_dir(out, ".");
    if(fclose(out) == EOF)  ERR("Cant close file");
    

    return EXIT_SUCCESS;
}