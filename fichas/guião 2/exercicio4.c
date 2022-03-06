#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

void filhos() {
    int i;
    int status;
    for (i = 1; i < 11; i++) {
        if (!fork()) {
            printf("pai = %d  filho = %d  i = %d\n", getppid(), getpid(), i);
            _exit(i);
        }
    }
    for (i = 0; i < 10; i++) {
        pid_t terminated_pid = wait(&status);
        printf("id do coiso terminado = %d, codigo de saida do filho = %d\n", terminated_pid, WEXITSTATUS(status));
    }
}

int main(){
    filhos();
    return 0;
}