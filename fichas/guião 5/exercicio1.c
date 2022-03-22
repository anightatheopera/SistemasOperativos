#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>



//afinal ta mal nao copiem
void opcao1(){
    int novo[2];
    assert(pipe(novo) == 0);
    pid_t pid = fork();
    if(pid){
        write(novo[1],"yuh",3);
    }
    else{
        char buf[3];
        assert(read(novo[0],buf,3) > 0);
    }
}

void opcao2(){
    int novo[2];
    assert(pipe(novo) == 0);
    pid_t pid = fork();
    if(pid){
        sleep(5);
        write(novo[1],"yuh",3);
    }
    else{
        char buf[3];
        assert(read(novo[0],buf,3) > 0);
    }
}

void opcao3(){
    int novo[2];
    assert(pipe(novo) == 0);
    pid_t pid = fork();
    if(!pid){
        write(novo[1],"yuh",3);
    }
    else{
        char buf[3];
        assert(read(novo[0],buf,3) > 0);
    }
}

int main(){
    opcao3();
    return 0;
}