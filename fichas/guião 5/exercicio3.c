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
        close(novo[1]);
        dup2(novo[0],STDIN_FILENO);
        close(novo[0]);

        execlp("wc","wc",NULL);
    }
    else{
        close(novo[0]);
        char buf[1440];
        ssize_t rd;
        while((rd = read(STDIN_FILENO,buf,1440)) > 0){
            assert(write(novo[1], buf, rd) > 0);
        }
        close(novo[1]);
    }
    return 0;
}