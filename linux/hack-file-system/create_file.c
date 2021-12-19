#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/* create a file of provided length */
int main(int argc, char* argv[])
{
    if (argc != 4) {
        fprintf(stderr, "usage: ./create_file 1 50 -o/-h (1MB, 50 files, output folder or here)\n");
        exit(-1);
    }
    for(int i=0; i<atoi(argv[2]); i++){
        int length = atoi(argv[1])*1048576;
        char* file_name = calloc(1, 20);
        if(strcmp(argv[3], "-o") == 0){
            sprintf(file_name, "./output/%smb_%d.txt", argv[1], i+1);
        }else{
            sprintf(file_name, "%smb_%d.txt", argv[1], i+1);
        }
        if (open(file_name, O_RDONLY) != -1) {
            remove(file_name);
        }
        char* buffer = calloc(1, length);
        memset(buffer, 'a', length);
        int file_to_create = creat(file_name, S_IRUSR | S_IWUSR);
        if (write(file_to_create, buffer, length) == -1) {
            fprintf(stderr, "Writing error\n");
            exit(1);
        }
        free(file_name);
        free(buffer);
        close(file_to_create);
    }
    
    return 0;
}
