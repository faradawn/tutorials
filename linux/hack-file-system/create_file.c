#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/* create a file of provided length */
int main(int argc, char* argv[])
{
    if (argc == 1) {
        fprintf(stderr, "Length not specified\n");
        exit(-1);
    }
    int length = atoi(argv[1]);
    char* file_name = calloc(1, 20);
    sprintf(file_name, "%d.txt", length);
    if (open(file_name, O_RDONLY) != -1) {
        remove(file_name);
        printf("The original file removed\n");
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
    return 0;
}
