#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>


int main(){
    int terminal_fd;
    terminal_fd = dup(STDOUT_FILENO);

    int fd_in = open("/etc/passwd", O_RDONLY);
    int fd_out = open("saida.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);
    int fd_err = open("erros.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);

    dup2(fd_in,STDIN_FILENO);
    dup2(fd_out,STDOUT_FILENO);
    dup2(fd_err,STDERR_FILENO);

    pid_t pid = fork();
    (void) pid;
    FILE* f = fdopen(terminal_fd, "w");
    fprintf(f, "fixe\n");

    close(fd_in);
    close(fd_out);
    close(fd_err);

    return 0;
}