#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/* Może będzie potrzebne do flag */
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>

#define ERR(source) (perror(source),\
                    fprintf(stderr,"%s:%d\n", __FILE__,__LINE__),\
                    exit(EXIT_FAILURE))

int make_file(char* file_name, mode_t permissions, ssize_t file_size, int percent) {

    umask(~permissions&0777);

    /* tworzymy nowy plik */
    FILE* new_file;
    if((new_file = fopen(file_name, "w+")) == NULL)
        ERR("fopen failed");
    
    for (int i = 0; i < (file_size*percent)/100; i++) {
        if(i==0) {
            if(fseek(new_file, 0, SEEK_END) != 0) ERR("fseek");
        }
        else {
            if(fseek(new_file, rand()%file_size, SEEK_SET) != 0) ERR("fseek");
        }
        fprintf(new_file, "%c", 'A' + (i % ('Z' - 'A'+1)) );
    }

    if(fclose(new_file) == EOF)
        ERR("fclose");
    return 0;
}

int main(int argc, char** argv) {

    int option;
    mode_t permissions = -1;
    ssize_t file_size = -1;
    char* file_name;

    while((option = getopt(argc, argv, "n:p:s:")) != -1) {
        switch (option)
        {
        case 'n':
            file_name = optarg;
            break;
        case 'p':
            permissions = strtol(optarg, (char**)NULL, 8);
            break;
        case 's':
            file_size = strtol(optarg, (char**)NULL, 10);
            break;
        case ':':
            ERR("Possible arguments are: -n NAME -p OCTAL -s SIZE");
            break;
        default:
            ERR("Possible arguments are: -n NAME -p OCTAL -s SIZE");
            break;
        }
    }   
    
    if(file_name==NULL || file_size == -1 || permissions == -1) ERR("Possible arguments are: -n NAME -p OCTAL -s SIZE");
    if(unlink(file_name)&&errno==ENOENT) ERR("unlink");
    srand(time(NULL));
    make_file(file_name, permissions, file_size, 10);

    return EXIT_SUCCESS;
}