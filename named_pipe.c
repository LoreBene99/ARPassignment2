#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <termios.h>

#define SIZE 2000000

int main(int argc, char* argv[]){

    int fd_np;
    int fd_time0;
    int fd_time1;
    time_t seconds0;
    time_t seconds1;

    printf("Insert number of elements of the array\n");

    int num;

    scanf("%d", & num);

    if (num > 25000000){

        printf("Insert a number smaller than 25000000");

        scanf("%d", & num);



    }

    int id = fork();

    if (id == -1){

        printf("Error forking...\n");
        exit(1);
    }

    if (id != 0){

        printf("Producer!\n");

        //maximum size of array that can occupy memory without segmentation fault

        int A[SIZE];

        for(int i = 0; i < SIZE; i++){

            A[i] = 1 + rand()%100;

        }

        fd_np = open(argv[1], O_WRONLY);

        fd_time0 = open(argv[2], O_WRONLY);

        // Stores time seconds

        time(&seconds0);

        write(fd_time0, &seconds0, sizeof(seconds0));
        
        printf("Time 0 : %ld\n", seconds0);

        

        for(int i = 0; i < num ; i++){

            write(fd_np, &A[i%SIZE], sizeof(A[i%SIZE]));
        }
    }

    else{

        printf("Consumer!\n");
            
        fd_np = open(argv[1], O_RDONLY);

        fd_time1 = open(argv[3], O_WRONLY);

        int B[SIZE];
                    
        for(int i = 0; i < num; i++){

            read(fd_np, &B[i%SIZE], sizeof(B[i%SIZE]));

        }

        // Stores time seconds

        time(&seconds1);

        printf("Time 1 : %ld\n", seconds1);

        write(fd_time1, &seconds1, sizeof(seconds1));
        
        

    }
    
    close(fd_np);
    close(fd_time0);
    close(fd_time1);

    return 0;
}
