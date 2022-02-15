#include <sys/types.h> 
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */ 
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */ 
#include <stdio.h>

int main(int argc, char** argv){
    char* source = argv[1];
    char* dest = argv[2];
    int fd_source = open(source,O_RDONLY);
    int fd_dest = open(dest,O_WRONLY);
    char buf;
    while(read(fd_source, &buf, sizeof(char))){
        write(fd_dest, &buf, sizeof(char));
    }
    close(fd_source);
    close(fd_dest);
}