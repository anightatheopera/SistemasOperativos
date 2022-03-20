#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(){
    int terminal_fd;
    terminal_fd = dup(STDOUT_FILENO);
    (void) terminal_fd;

    int fd_in = open("/etc/passwd", O_RDONLY);
    int fd_out = open("saida.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);
    int fd_err = open("erros.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);

    dup2(fd_in,STDIN_FILENO);
    dup2(fd_out,STDOUT_FILENO);
    dup2(fd_err,STDERR_FILENO);

    close(fd_in);
    close(fd_out);
    close(fd_err);

    execlp("wc", "wc", NULL);

    return 0;
}