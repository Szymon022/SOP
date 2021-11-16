#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

#define MAXFD 20
#define MAX_INPUT 255
#define MAX_LENGTH 50
#define MAX_CMDS 10
#define MAX_PATH 300
#define ERR(source) (perror(source),\
                fprintf(stderr, "%s:%d", __FILE__, __LINE__),\
                exit(EXIT_FAILURE))

void usage(const char* pname) {
    fprintf(stderr, "USAGE: %s [-p PATH]\n", pname);
    exit(EXIT_FAILURE);
}

int ls() {
    DIR* dir;
    struct dirent* dp;
    struct stat st;

    if((dir = opendir(".")) == NULL) {
        ERR("Couldn't open directory");
        return -1;
    } 

    do {
        errno=0;
        if((dp = readdir(dir)) != NULL) {
            if(lstat(dp->d_name, &st) != 0) ERR("lstat");
            char* mtime = ctime(&st.st_mtime);
            fprintf(stdout, "%-50s%s", dp->d_name, mtime);
        }
    } while(dp != NULL);

    if(errno != 0) ERR("Readdir");
    if(closedir(dir)) ERR("Couldn't close directory");

    return 0;
}

int rm(const char* path, int verbose_flag, int handle_error_flag) {
    if(unlink(path) != 0) {
        if(handle_error_flag == 1) fprintf(stderr, "Cant remove file: %s\n", path);
        return -1;
    }
    if(verbose_flag == 1) printf("Removed %s\n", path);
    return 0;
}

int cp_rec(char* source, char* destination, int verbose_flag, int handle_error_flag) {
    return -1;
}

int cp(char* source, char* destination, int verbose_flag, int handle_error_flag) {

    FILE* sfile=NULL;
    FILE* ofile=NULL;
    char in[MAX_INPUT];

    if((sfile = fopen(source, "r")) == NULL) {
        if(handle_error_flag == 1)
            fprintf(stderr, "Couldnt open file %s\n", source);
        return -1;
    }
    if((ofile = fopen(destination, "w")) == NULL) {
        if(handle_error_flag == 1)
            fprintf(stderr, "Couldnt create file %s\n", source);
        return -1;
    }
    while(fgets(in, MAX_INPUT, sfile) != NULL) {
        fprintf(ofile, "%s", in);
    }

    if(fclose(sfile) != 0) ERR("fclose sfile");
    if(fclose(ofile) != 0) ERR("fclose ofile");

    if(verbose_flag == 1)
        printf("Copied %s to %s\n", source, destination);

    return 0;
}

int isLs(const char* cmd) {
    return (cmd[0] == 'l' && cmd[1] == 's');
}
int isRm(const char* cmd) {
    return (cmd[0] == 'r' && cmd[1] == 'm');
}
int isCp(const char* cmd) {
    return (cmd[0] == 'c' && cmd[1] == 'p');
}
int isExit(const char* cmd) {
    return (cmd[0] == 'e' && cmd[1] == 'x' && cmd[2] == 'i' && cmd[3] == 't');
}


int main(int argc, char** argv) {
    // int ext_flag=0;
    int o;
    char* wdpath=".";
    int wdpath_flag=0;
    char cmdin[MAX_LENGTH];
    char* verbose=getenv("VERBOSE");
    char* handle_error=getenv("HANDLE_ERROR");
    int verbose_flag=0, handle_error_flag=0;

    if(verbose) {
        if((verbose_flag=atoi(verbose)) != 1) ERR("Couldnt set verbose flag");
    }
    if(handle_error) {
        if((handle_error_flag=atoi(handle_error)) != 1) ERR("Couldnt set handle error flag");
    }

    while ((o = getopt(argc, argv, "p:")) != -1) {
        switch(o) {
        case 'p':
            if(wdpath_flag > 1) {
                if(handle_error_flag == 1) fprintf(stderr, "Too many -p options\n");
                exit(EXIT_FAILURE);
            }
            wdpath=optarg;
            if(chdir(wdpath) != 0) {
                if(handle_error_flag == 1) fprintf(stderr, "Couldnt change directory to %s\n", wdpath);
                exit(EXIT_FAILURE);
            }
            if(verbose_flag == 1) fprintf(stdout, "cwd changed to %s\n", wdpath);
            break;
        case ':':
            usage(argv[0]);
            break;
        default:
            ls();
        }
    }

    optind=1;
    while(fgets(cmdin, MAX_LENGTH, stdin) != NULL) {
        // if(strcmp(cmdin, "\n") == 0) continue;q
        // char* ptr = NULL;
        cmdin[strcspn(cmdin, "\n")] = 0;
        char* cmd[MAX_CMDS];
        char delim[] = " ";
        
        int i=0, cmd_count=0;
        
        cmd[i] = strtok(cmdin, delim); 
        cmd_count++;
        i++;

        while ((cmd[i] = strtok(NULL, delim)) != NULL && cmd_count < MAX_CMDS) {
            i++;
            cmd_count++;
        }
    
        if(isLs(cmd[0])) {
            ls();
        } else if(isRm(cmd[0])) {
            if(cmd_count != 2) ERR("rm without parameters!");
            rm(cmd[1], verbose_flag, handle_error_flag);

        } else if(isCp(cmd[0])) {
            int rflag=0;
            optind=1;
            while ((o = getopt(cmd_count, cmd, ":R")) != -1) {
                switch(o) {
                    case 'R':
                        if(rflag == 1) {
                            if(handle_error_flag == 1) {
                                fprintf(stderr, "-R argument passed too many times\n");
                            }
                            exit(EXIT_FAILURE);
                        }
                        rflag=1;
                    break;
                    case '?':
                        if(handle_error_flag == 1) 
                            fprintf(stderr, "Unknown option for cp\n");
                        exit(EXIT_FAILURE);
                    break;
                    default:
                    break;
                }
            }
            rflag == 1 ? 
                cp_rec(cmd[2], cmd[3], verbose_flag, handle_error_flag) :
                cp(cmd[1], cmd[2], verbose_flag, handle_error_flag);
        } else if(isExit(cmd[0])) {
            if(verbose_flag == 1) printf("Exited\n");
            return EXIT_SUCCESS;
        }        
    } 
    return EXIT_SUCCESS;
}
