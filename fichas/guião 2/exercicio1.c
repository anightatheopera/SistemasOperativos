#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

void printIDs(){
    printf("identificador de processo: %d\n", getpid());
    printf("identificador do pai do processo: %d\n", getppid());
}

int main(){
    printIDs();
    return 0;
}