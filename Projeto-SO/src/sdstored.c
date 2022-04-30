#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "util/sv.h"
#include "util/proc.h"
#include "util/utilities.h"

//SERVIDOR


char* get_trans_id(char* path){
    while(*path != '\0' && *path != ' '){
        path++;
    }
    while(*path == ' '){
        *(path++) = '\0';
    }
    return *path == '\0' ? NULL : path;
}

int get_max_inst(char* path){
    while(*path != '\0' && *path != ' '){
        path++;
    }
    if(*path++ != '\0'){
        return atoi(path);
    }
    else return 0;
}


/* Prints instructions on how to use the program */
void usage(int argc, char** argv){
    (void) argc;

    char buf[1024];
    snprintf(buf, sizeof(buf), "USAGE: %s [conf_file] [bin_path]\n", argv[0]);
    sv_write(sv_from_cstr(buf), STDOUT_FILENO);
}

void parse_message(char* buf, int size){
    // ex:
    // buf is --> xxxxxx:proc-file;<priority>;file_in;file_out;filter_1;filter_2;...filter_n;

    char* pid = malloc(sizeof (char));
    char fifo[MAX_MESSAGE];
    int i,j;
    for ( i = 0; buf[i] != ':'; i++){
        pid = realloc(pid, sizeof(char)*(i+1));
        pid[i] = buf[i];
    }
    pid[i]='\0';
    // pid is --> xxxxxx
    RESPONSE_PIPE(fifo, pid);
    // fifo is --> /temp/pid
    if(mkfifo(fifo, 0666) == -1){
        perror(fifo);
    }
    i++;
    char message[size-i];
    for (j = 0; i<size; j++, i++){
        message[j] = buf[i];
    }
    // message is --> proc-file;<priority>;file_in;file_out;filter_1;filter_2;...filter_n;
    /*



    EXECUTAR A MENSAGEM




    */
}




/* Main */
int main(int argc, char** argv){
    if(argc != 3){
        usage(argc, argv);
        exit(-1);
    }
    if(mkfifo(CLIENT_SERVER_PIPE, 0666) == -1){
        perror(CLIENT_SERVER_PIPE);
    }
    SV conf = sv_slurp_file(argv[1]);
    (void) conf;

    
    Operations* ops =  operations_new();
    operations_add(ops, BCOMPRESS);
    operations_add(ops, BDECOMPRESS);
    operations_add(ops, NOP);
    operations_add(ops, NOP);

    procs_run_operations("bin","README.md","teste",ops);
    
   /*
    while(conf.count > 0){
        SV line = sv_chop_line(&conf);
        sv_write(line, STDOUT_FILENO);
    }
    */  

    
    char buf[MAX_MESSAGE];
    int fd = open(CLIENT_SERVER_PIPE, O_RDONLY);
    while (1){
        size_t bytes_read = 0;
        while(!bytes_read ) 
           bytes_read = read(fd, buf, MAX_MESSAGE);
        parse_message(buf, bytes_read);
    }


    //sv_write(conf, STDOUT_FILENO);
    return 0;
}
