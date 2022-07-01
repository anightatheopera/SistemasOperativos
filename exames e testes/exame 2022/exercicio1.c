int comando(const char* filtro, const char* entrada, const char* saida){
    int fde = open(entrada, O_RDONLY);
    int fds = open(saida, O_WRONLY);
    int fderr[2];
    assert(pipe(fderr) == 0);
    int pid = fork();
    if(!pid){
        dup2(fde, 0);
        dup2(fds, 1);
        dup2(fderr[1], 2);
        close(fde);
        close(fds);
        close(fderr[0]);
        close(fderr[1]);
        execlp(filtro, filtro, NULL);
        exit(-1);
    }
    else wait();
    char b;
    return read(fderr[0],&b,1) == 1;
}