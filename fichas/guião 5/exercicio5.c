#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <errno.h>

int main(){
    int novo1[2];
    int novo2[2];
    int novo3[2];

    assert(pipe(novo1) == 0);

    int pid = fork();
    if(!pid){
        dup2(novo1[1],STDOUT_FILENO);
        close(novo1[0]);
        close(novo1[1]);
        execlp("grep", "grep", "-v", "ˆ#", "/etc/passwd", NULL);
    }

    assert(pipe(novo2) == 0);
    if(!fork()){
        dup2(novo1[0],STDIN_FILENO);
        dup2(novo2[1],STDOUT_FILENO);
        close(novo1[0]);
        close(novo1[1]);
        close(novo2[0]);
        close(novo2[1]);
        execlp("cut", "cut", "-f7", "-d:", NULL);
    }

    assert(pipe(novo3) == 0);
    if(!fork()){
        dup2(novo2[0],STDIN_FILENO);
        dup2(novo3[1],STDOUT_FILENO);
        close(novo1[0]);
        close(novo1[1]);
        close(novo2[0]);
        close(novo2[1]);
        close(novo3[0]);
        close(novo3[1]);
        execlp("uniq", "uniq", NULL);
    }


    dup2(novo3[0],STDIN_FILENO);
    close(novo1[0]);
    close(novo1[1]);
    close(novo2[0]);
    close(novo2[1]);
    close(novo3[0]);
    close(novo3[1]);
    execlp("wc", "wc", "-l", NULL);
}