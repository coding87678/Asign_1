#include <stdio.h>      
#include <stdlib.h>     
#include <fcntl.h>      
#include <unistd.h>     
#include <sys/wait.h>   

int main(int argc, char **argv)
{
    int pid, status;
    int newfd;
    char *cmd[] = { "/bin/ls", "-al", "/", 0 };   

    if (argc != 2) {                              
        fprintf(stderr, "usage: %s output_file\n", argv[0]);
        exit(1);
    }
    if ((newfd = open(argv[1], O_CREAT|O_TRUNC|O_WRONLY, 0644)) < 0) {
        perror(argv[1]);                          
        exit(1);
    }
    printf("writing output of the command %s to \"%s\"\n", cmd[0], argv[1]);

    pid = fork();              // make a copy of the program

    if (pid == 0) {            // the child returns 0 in the child
        dup2(newfd, 1);        // child's output now goes to the file
        execvp(cmd[0], cmd);   // child becomes "ls -al /"
        perror(cmd[0]);        
        exit(1);
    }

    wait(&status);             // the parent waits for the child to finish    
    return 0;
}