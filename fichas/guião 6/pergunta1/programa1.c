#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
    if(mkfifo("fifo", 0777) == -1){
        printf("Não foi possível criar o fifo");
        return -1;
    }
    return 0;
}