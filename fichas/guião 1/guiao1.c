#include <sys/types.h> 
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */ 
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */ 

int open(const char *path, int oflag [, mode]); 
ssize_t read(int fildes, void *buf, size_t nbyte); 
ssize_t write(int fildes, const void *buf, size_t nbyte); 
off_t lseek(int fd, off_t offset, int whence); 
int close(int fildes); 


int main(int argc, char** argv){
    char* source = argv[1];
    char* dest = argv[2];
    int fd_source = open(source,O_RDONLY);
    char buf;
    ssize_t nrd = read(fd_source, &buf, sizeof(char)); // nrd = number of bytes read
    close(fd_source);
    printf("%c", buf);
}