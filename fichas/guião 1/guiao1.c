#include <sys/types.h> 
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */ 
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */ 
#include <stdio.h>

int main(int argc, char** argv){
    char* source = argv[1];
    char* dest = argv[2];
    int fd_source = open(source,O_RDONLY);
    char buf;
    ssize_t nrd = read(fd_source, &buf, sizeof(char)); // nrd = number of bytes read
    close(fd_source);
    printf("%c\n", buf);
}