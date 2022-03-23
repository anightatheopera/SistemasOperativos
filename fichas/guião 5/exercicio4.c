#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <errno.h>

int main(){
    int novo[2];
    assert(pipe(novo) == 0);
    pid_t pid = fork();
    if(!pid){
        dup2(novo[1],STDOUT_FILENO);
        close(novo[0]);
        close(novo[1]);
        execlp("ls", "ls", "/etc", NULL);
    }
    else{
        dup2(novo[0],STDIN_FILENO);
        close(novo[1]);
        close(novo[0]);
        execlp("wc", "wc", "-l", NULL);
    }
    return 0;
}