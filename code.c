#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    sigset_t set;          // a list of signals
    int sig;               
    char answer[5];     

    sigemptyset(&set);                    // start with an empty list
    sigaddset(&set, SIGINT);              // put Ctrl-C on the list
    sigprocmask(SIG_BLOCK, &set, NULL);   // tell the OS to not interrupt me

    while (1) {
        sigwait(&set, &sig);              // wait here until Ctrl-C is pressed
        write(1, "Do you really want to quit [y/n]? ", 34);
        read(0, answer, 5);
        if (answer[0] == 'y')
            exit(0);                      
    }                                     
}