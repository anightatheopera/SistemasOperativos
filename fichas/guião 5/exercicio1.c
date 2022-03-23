#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <stdio.h>

void opcao1(){
    int novo[2];
    assert(pipe(novo) == 0);
    pid_t pid = fork();
    if(pid){
        assert(write(novo[1],"yuh",3) > 0);
    }
    else{
        char buf[3];
        assert(read(novo[0],buf,3) > 0);
        printf("[FILHO] : li %.*s\n", 3, buf);
    }
}

void opcao2(){
    int novo[2];
    assert(pipe(novo) == 0);
    pid_t pid = fork();
    if(pid){
        sleep(5);
        assert(write(novo[1],"yuh",3) > 0);
    }
    else{
        char buf[3];
        assert(read(novo[0],buf,3) > 0);
        printf("[FILHO] : li %.*s\n", 3, buf);
    }
}

void opcao3(){
    int novo[2];
    assert(pipe(novo) == 0);
    pid_t pid = fork();
    if(!pid){
        assert(write(novo[1],"yuh",3) > 0);
    }
    else{
        char buf[3];
        assert(read(novo[0],buf,3) > 0);
        printf("[FILHO] : li %.*s\n", 3, buf);
    }
}

int main(){
    opcao1();
    return 0;
}