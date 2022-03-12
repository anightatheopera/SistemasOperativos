#include <unistd.h>
#include <sys/types.h>

void exercicio2(){
    pid_t pid = fork();
    if(pid == 0) {
		execlp("ls", "-l", NULL);
	}
}

int main(){
    exercicio2();
    return 0;
}