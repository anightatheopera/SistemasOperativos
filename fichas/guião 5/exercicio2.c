#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <errno.h>

void alt(){
    int novo[2];
    pipe(novo);
    int status;
    pid_t pid = fork();
    if(pid){
        close(novo[0]);
        write(novo[1],"yuh",3);
        printf("[PAI] : vou esperar pelo meu filho\n");
        int status;
        printf("[PAI] : esperei\n");
        close(novo[1]);
        wait(&status);
    }
    else{
        close(novo[1]);
        char buf[3];
        ssize_t rd;
        printf("[FILHO] vou ler cenas\n");
        while((rd = read(novo[0],buf,3)) > 0){
            printf("[FILHO] : li %.*s\n", 3, buf);
        }
        printf("[FILHO] : sai com rd = %ld %s\n", rd, strerror(errno));
        close(novo[0]);
        
    }
}

int main(){
    alt();
    return 0;
}