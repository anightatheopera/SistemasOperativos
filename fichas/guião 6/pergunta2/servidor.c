#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

void creates_fifo() {
    if (mkfifo("CLIENTE", 0777) < 0) {
        perror("Não foi possível criar o fifo.\n");
        return;
    }
}

void read_fifo() {
    int fd = open("CLIENTE", O_RDWR);
    int nfd = open("log.txt", O_CREAT | O_RDWR, 0777);

    printf("Aberto\n");

    size_t rd;
    char buf[1024];

    while ((rd = read(fd, buf, 1024)) > 0) {
        write(nfd, buf, rd);
    }
    close(fd);
}

int main(){
    creates_fifo();
    read_fifo();
    return 0;
}

