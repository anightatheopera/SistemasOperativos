int mensagens(char* palavra, char* ficheiro){
    int pipe_in[2];
    assert(pipe(pipe_in) == 0);
    int pipe_out[2];
    assert(pipe(pipe_out) == 0);
    if(!fork()){
        close(pipe_in[0]);
        dup2(pipe_in[1], 1);
        execlp("grep","grep",palavra,ficheiro,NULL);
    }
    close(pipe_in[1]);
    if(!fork()){
        close(pipe_out[0]);
        dup2(pipe_in[0], 0);
        dup2(pipe_out[1], 1);
        execlp("wc","wc","-l",NULL);
    }
    close(pipe_out[1]);
    char buf[1024];
    while(read(pipe_out[0], buf, 1023) > 0);
    close(pipe_in[0]);
    close(pipe_out[0]);
    return atoi(buf);
}