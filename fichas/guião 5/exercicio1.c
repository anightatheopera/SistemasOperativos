#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <stdio.h>

void opcao1(){
    int novo[2];
    pipe(novo);
    int res;
    char buffer[20];
    pid_t pid = fork();
    int status;
    if(pid){
        close(novo[1]);
		res = read(novo[0], &buffer, sizeof(buffer));
		printf("[FILHO]: read %s from pipe res %d\n", buffer,res);
		close(novo[0]);
		_exit(0);
    }
    else{
		close(novo[0]);
		write(novo[1], "yuh", 3);
		printf("[PAI]: wrote line to pipe\n");
		close(novo[1]);
		wait(&status);
    }
}

void opcao2(){
    int novo[2];
    pipe(novo);
    int res;
    char buffer[20];
    pid_t pid = fork();
    int status;
    if(pid){
        close(novo[1]);
		res = read(novo[0], &buffer, sizeof(buffer));
		printf("[FILHO]: read %s from pipe res %d\n", buffer,res);
		close(novo[0]);
		_exit(0);
    }
    else{
		close(novo[0]);
        sleep(5);
		write(novo[1], "yuh", 3);
		printf("[PAI]: wrote line to pipe\n");
		close(novo[1]);
		wait(&status);
    }
}

void opcao3(){
    int novo[2];
    pipe(novo);
    int res;
    char buffer[20];
    pid_t pid = fork();
    int status;
    if(pid){
        close(novo[0]);
		write(novo[1], "yuh", 3);
		printf("[PAI]: wrote line to pipe\n");
		close(novo[1]);
		wait(&status);
    }
    else{
        close(novo[1]);
		res = read(novo[0], &buffer, sizeof(buffer));
		printf("[FILHO]: read %s from pipe res %d\n", buffer,res);
		close(novo[0]);
		_exit(0);
    }
}

int main(){
    opcao3();
    return 0;
}