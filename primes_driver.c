#include "primes_driver.h"

int main(int argc, char** argv)
{
    int wpid;
    int status;

    // creating pipe
    int fd[2];

    if(pipe(fd))
    {
        printf("ERROR: FAILED TO CREATE PIPE!\n");
        return -1;
    }

    // creating a child process
    int pid = fork();

    if(pid < 0)
    {
        printf("ERROR: FORK FAILED!\n");
        return -1;
    }
    else if(pid == 0)
    {
        // child process
        if(argc != 2)
        {
            printf("ERROR: ONE ARGUMENT VALUE REQUIRED!\n");
            return -1;
        }

        int N;
        if(!(N = atoi(argv[1])))
        {
            printf("ERROR: INVALID INTEGER INPUTTED!\n");
            return -1;
        }

        int* primes = find_primes(N);
        int* ptr;

        int len = 0;
        // if *ptr == 0 then stop the loop
        for(ptr = primes; *ptr; ptr++)
            len++;
        
        // outputting prime numbers
        // for(ptr = primes; *ptr;)
        //     printf("primes: %d\n", *ptr++);
        
        // closing output side of pipe
        close(fd[0]);

        char str[100];
        sprintf(str, "PRIMES FOUND: %d\n", len);
        write(fd[1], str, (strlen(str) + 1));

        free(primes);
    }
    else
    {
        // parent process 
        printf("PARENT PROCESS!\n");

        // waiting for child to finish
        wpid = (int)waitpid(pid, &status, 0);
        printf("CHILD PROCESS FINISHED!\n");

        // reading from the pipe
        char buff[100];
        int numBytes;

        close(fd[1]);
        numBytes = read(fd[0], buff, sizeof(buff));

        printf("Parent recieved:\t %s\n", buff);

        printf("PARENT PROCESS FINISHED!\n");
    }
    return 0;
}
