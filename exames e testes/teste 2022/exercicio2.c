int autores_que_usaram(char* palavra, int n, char* autores[]){
    int total = 0;
    for(int i = 0; i < n; i++){
        if(!fork()){
            if(mensagens(palavra, autores[i]) > 0){
                _exit(1);
            }
            else _exit(0);
        }
    }
    for(int i = 0; i < n; i++){
        int wstatus;
        wait(&wstatus);
        if(WIFEXITED(wstatus)){
            if(WEXITSTATUS(wstatus)){
                total++;
            }
        }
    }
    return total;
}