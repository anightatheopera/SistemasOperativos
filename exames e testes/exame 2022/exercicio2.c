typedef struct{
    char filtro[20],
    char entrada[20],
    char saida[20]
} Args;

void run_args(Args args[]){
    bool results[5] = {0};
    pid_t pids[5] = {0};
    int log = open("comando.log", O_WRONLY | O_CREAT);
    for(int i = 0; i < 5; i++){
        pids[i] = fork();
        if(!pids[i]) exit(comando(args[i].filtro, args[i].entrada, args[i].saida));
    }
    for(int i = 0; i < 5; i++){
        int wstatus;
        waitpid(pids[i], &wstatus, 0);
        results[i] = WEXITSTATUS(wstatus);
        if(results[i]) write(log, "OK\n", 3);
        else write(log, "ERRO\n", 5);
    }
}

void servidor(){
    mkfifo("comando.fifo", 0666);
    int fd = open("comando.fifo", O_RDONLY);
    Args args[5];
    int pending = 0;
    while(1){
        while(pending < 5){
            read(fd, args[pending].filtro, 20);
            read(fd, args[pending].entrada, 20);
            read(fd, args[pending].saida, 20);
            pending++;
        }
        pending = 0;
        run_args(args);
    }

}

