#include <signal.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
typedef void (*sighandler_t)(int);

int counter = 0;
int seconds = 0;

void sigint_handler(int signum){
    printf("\nPassaram %d segundos desde que o programa começou\n", seconds);
    counter++;
}

void signquit_handler(int signum){
    printf("\nO utilizador carregou no Ctrl+C %d vezes\n", counter);
    _exit(0);
}

void sigalrm_handler(int signum) {
    seconds++;
    alarm(1);
}

int main(){
    if(signal(SIGINT,sigint_handler) == SIG_ERR){
        printf("algo correu mal\n");
        exit(1);
    }
    if(signal(SIGQUIT,signquit_handler) == SIG_ERR){
        printf("algo correu mal\n");
        exit(1);
    }
    if(signal(SIGALRM,sigalrm_handler) == SIG_ERR){
        printf("algo correu mal\n");
        exit(1);
    }

    alarm(1);
    while(1) sleep(1);

    return 0;
}