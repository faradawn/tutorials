#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "time.h"
#include <sys/types.h> 
#include <sys/wait.h>

#define BLOCKSIZE 4096
#define NUM_READ  2560

int total_file_length(int file_to_read) {
    int res = lseek(file_to_read, 0, SEEK_END);
    lseek(file_to_read,0,SEEK_SET);
    return res;
}

double sequential_io(int file_to_read, int file_to_write, int direct_io, int read_or_write)
{
    clock_t start, end;
    double total_read_time = 0, total_write_time = 0;

    int n;
    void* buffer = calloc(1, BLOCKSIZE);
    posix_memalign(&buffer, BLOCKSIZE, BLOCKSIZE);

    while (1) {
        start = clock();
        if ((n = read(file_to_read, buffer, BLOCKSIZE)) == -1) {
            fprintf(stderr, "Reading error\n");
            exit(1);
        }
        end = clock();
        total_read_time += (double)(end-start)/(double)(CLOCKS_PER_SEC);
        if (n == 0) {
            break;
        }

        if (read_or_write == 2) {
            start = clock();
            if (write(file_to_write, buffer, BLOCKSIZE) == -1) {
                fprintf(stderr, "Writing error\n");
                exit(1);
            }
            end = clock();
            total_write_time += (double)(end-start)/(double)(CLOCKS_PER_SEC);
        }
    }
    free(buffer);

    if (direct_io) {
        if (read_or_write == 1){
            printf("Time taken for sequential direct I/O reading:   %.10lf\n", total_read_time);
            return total_read_time;
        }
        else{
            printf("Time taken for sequential direct I/O writing:   %.10lf\n", total_write_time);
            return total_write_time;
        }
    } else {
        if (read_or_write == 1){
            printf("Time taken for sequential indirect I/O reading: %.10lf\n", total_read_time);
            return total_read_time;
        }
        else{
            printf("Time taken for sequential indirect I/O writing: %.10lf\n", total_write_time);
            return total_write_time;
        }
    }
    return 0;
    
}

int generate_random_number(int range)
{
    int random = (((rand() & 255)<<8 | (rand() & 255))<<8 | (rand() & 255))<<7 | (rand() & 127);
    return (random % range) / BLOCKSIZE * BLOCKSIZE;
}

void random_read(int file_to_read, int total_file_length, int direct_io)
{
    clock_t start, end;
    double total_read_time = 0;
    int random_number;

    int n;
    void* buffer = calloc(1, BLOCKSIZE);
    posix_memalign(&buffer, BLOCKSIZE, BLOCKSIZE);

    for (unsigned int i = 0; i < NUM_READ; i++) {
        random_number = generate_random_number(total_file_length);
        start = clock();
        lseek(file_to_read, random_number, SEEK_SET);
        if ((n = read(file_to_read, buffer, BLOCKSIZE)) == -1) {
            fprintf(stderr, "Reading error\n");
            exit(1);
        }
        end = clock();
        total_read_time += (double)(end-start)/(double)(CLOCKS_PER_SEC);
    }

    if (direct_io) {
        printf("Time taken for random direct I/O reading:       %.10lf\n", total_read_time);
    } else {
        printf("Time taken for random indirect I/O reading:     %.10lf\n", total_read_time);
    }
    free(buffer);
}

void wrapper_seq_read(int file_to_read, int file_to_write, int direct_io, int read_or_write){
    double num=10;
    double sum=0;
    pid_t pid;
    for(int i=0; i<num; i++){
        sum += sequential_io(file_to_read, file_to_write, direct_io, read_or_write);
        if((pid=fork())==0){
            char* argv[]={"vmtouch","-e", "1048576.txt", NULL};
            if(execvp(argv[0], argv)<0){
                perror("why error!!");
                exit(1);
            }
        }else{
            while(wait(NULL)>0){;}
        }
    }

    printf("avg time %.10lf\n", sum/num);
    printf("avg MB/s %.10lf\n", 60/(sum/num));
}

int main(int argc, char *argv[])
{
    int opt;
    int direct_io = -1;
    char* read_file = NULL;
    int sequential_or_random = 0, read_or_write = 0;
    while ((opt = getopt(argc, argv, "diasrwf:")) != -1) {
        switch (opt) {
            case 'd':
                direct_io = 1;
                break;
            case 'i':
                direct_io = 0;
                break;
            case 'a':
                sequential_or_random = 2;
                break;
            case 's':
                sequential_or_random = 1;
                break;
            case 'f':
                read_file = strdup(optarg);
                break;
            case 'r':
                read_or_write = 1;
                break;
            case 'w':
                read_or_write = 2;
                break;
            default:
                fprintf(stderr, "ERROR: Unknown option -%c\n", opt);
                exit(-1);
        }
    }

    /* Error checking */
    if (!read_file) {
        fprintf(stderr, "ERROR: No file specified\n");
        exit(0);
    }
    if (direct_io == -1) {
        fprintf(stderr, "Direct IO or indirect IO not specified\n");
        exit(0);
    }
    if (sequential_or_random == 0) {
        fprintf(stderr, "Sequential or random not specified\n");
        exit(0);
    }
    if (read_or_write == 0) {
        fprintf(stderr, "Read or write not specified\n");
        exit(0);
    }
    if (read_or_write == 2 && sequential_or_random == 2) {
        fprintf(stderr, "Random write not implemented\n");
        exit(0);
    }

    /* open the file to read */
    int file_to_read;
    if (direct_io)
        file_to_read = open(read_file, O_RDONLY | O_DIRECT | O_SYNC, S_IRUSR | S_IWUSR);
    else
        file_to_read = open(read_file, O_RDONLY, S_IRUSR | S_IWUSR);
    
    if (file_to_read == -1) {
        fprintf(stderr, "ERROR: The specified file does not exist");
        exit(0);
    }
        
    int file_to_write = creat("tmp.txt", S_IRUSR | S_IWUSR);

    int file_length = total_file_length(file_to_read);

    if (sequential_or_random == 1)
        wrapper_seq_read(file_to_read, file_to_write, direct_io, read_or_write);
    else
        random_read(file_to_read, file_length, direct_io);

    close(file_to_read);
    close(file_to_write);
    remove("tmp.txt");

    return 0;
}
