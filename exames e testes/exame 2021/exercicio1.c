int memoria(){
    int pipe_in[2];
    assert(pipe(pipe_in) == 0);
    if(!fork()){
        close(pipe_in[0]);
        dup2(pipe_in[1], 1);
        char prog[200];
        sprintf(prog,"grep VmPeak /proc/%d/status",getpid());
        execlp(prog,prog, NULL);
    }
    close(pipe_in[1]);
    int pipe_out[2];
    assert(pipe(pipe_out) == 0);
    if(!fork()){
        close(pipe_out[0]);
        dup2(pipe_in[0], 0);
        dup2(pipe_out[1], 1);
        execlp("cut", "cut", "-d\"", "\"", "-f4", NULL);
    }
    close(pipe_in[0]);
    close(pipe_out[1]);
    char buf[1024];
    while(read(pipe_out[0], buf, 1023) > 0);
    return atoi(buf);
}

// fazer a main e as medias 