#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
    
    printf("A abrir..\n");
    int fd = open("fifo", O_RDONLY);
    printf("Aberto\n");

    char buf[1440];
    size_t rd;
    printf("A escrever..\n");
    while((rd = read(fd,buf,1440)) > 0){
            write(STDOUT_FILENO, buf, rd);
        }
    printf("Escrito\n");
    close(fd);
    return 0;
}