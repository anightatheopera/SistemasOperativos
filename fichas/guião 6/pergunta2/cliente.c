#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>



void write_fifo() {
    int fd = open("CLIENTE", O_WRONLY);

    printf("Aberto\n");

    size_t rd;
    char buf[1024];

    while ((rd = read(0, buf, 1024)) > 0) {
        write(fd, buf, rd);
    }
    close(fd);
}

int main(){
    write_fifo();
}