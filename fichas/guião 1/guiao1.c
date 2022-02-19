#include <sys/types.h> 
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */ 
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */ 
#include <stdio.h>
#include <string.h>

#define BUF_SZ 4000
typedef struct file {
    int fd;
    char buf[BUF_SZ];
    char* cur;
    char* end;
} File;

void mycp(int fd_src, int fd_dest){
    char buf;
    while(read(fd_src, &buf, sizeof(char))){
        write(fd_dest, &buf, sizeof(char));
    }
}

void mycat(){
    char buf;
    while(read(STDIN_FILENO, &buf, 1))
        write(STDOUT_FILENO, &buf, 1);
}

ssize_t readln(int fd, char *line, size_t size){
    size_t i = 0;
    while(i < size - 1){
        size_t nbr = (size_t) read(fd,&line[i],sizeof(char));
        if(nbr < 1) break;
        if(line[i++] == '\n') break;
    }
    line[i] = '\0';
    return (ssize_t) i;
}

ssize_t File_try_refill(File* f){
    if(f->cur >= f->end){
        ssize_t rd = read(f->fd, f->buf, BUF_SZ-1);
        if(rd <= 0){
            return rd;
        }
        f->cur = f->buf;
        f->end = f->buf + rd;
        *f->end = '\0';
    }
}

void File_debug(File* f){
    printf("{ fd: %d, buf_size: %ld, buf: '%s'}\n", f->fd, f->end - f->cur, f->cur);
}

ssize_t readln2(File* f, char* line, size_t size){
    size_t offset = 0;
    ssize_t rd = !0;
    while(offset < size-1 && rd && (offset == 0 || line[offset-1] != '\n')){
        rd = File_try_refill(f);

        char* nl = strchr(f->cur, '\n');

        size_t cp_sz = 0;
        if(nl != NULL && offset + (nl - f->cur) < size-1){
            // nl was found and we have enough space
            cp_sz = nl - f->cur + 1;
        } else if(offset - size < f->end - f->cur){
            // we don't have enough space to copy entire buffer
            cp_sz = offset - size;
        } else {
            // we have enough space and will copy the entire buffer
            cp_sz = f->end - f->cur;
        }

        memcpy(line + offset, f->cur, cp_sz);
        f->cur += cp_sz;
        offset += cp_sz;
    }
    line[offset-1] = '\0';
    return offset;
}

void nl(){
    char buf[1024];
    ssize_t i = 0;
    while(readln(STDIN_FILENO, buf,sizeof(buf))){
         printf("%ld: %s\n", i++, buf);
    }
    _exit(0);
}

//nl com readln: indeterminado, demora demasiado tempo
//nl com readln2: 0,00s user 0,00s system 77% cpu 0,001 total

void main(){
    File f = {0};
    f.fd = STDIN_FILENO;
    char line[1024];
    for(size_t line_no = 1; readln(&f, line, sizeof(line)/sizeof(line[0])); line_no++){
        printf("    %ld  %s\n", line_no, line);
    }
}
