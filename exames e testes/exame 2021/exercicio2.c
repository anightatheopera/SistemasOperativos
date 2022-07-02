bool alarm_occurred = false;

void alarm_handler(int signum){
    alarm_occurred = true;
}

int round(char* cmd){
    int finished = 0;
    pid_t children[100];

    /* spawn children */
    for(int i = 0; i < 100; i++){
        children[i] = fork();
        if(children[i] == 0){
            execlp(cmd, cmd, NULL);
        }
  }
  
  /* setup an alarm signal for the next 20 secs */
  signal(alarm_handler, SIG_ALARM);
  alarm(20);

  /* await until all finished or alarm has occurred */
  while(finished < 100 && !alarm_occurred) {
        pid_t pid = wait(NULL);
        finished++;
  
        for(int i = 0; i < 100; i++){
            if(children[i] == pid) {
                children[i] = 0;
            }
        }
  }

  /* remove alarm schedule if present */
  alarm(0);
  alarm_occurred = false;

  /* kill children remaining */
  for(int i = 0; i < 100; i++){
        if(children[i] != 0) {
            kill(children[i], SIGINT);
        }
  }

}

int correr(int n){
    int ret = 0;
    for(int i = 0; i < n; i++){
        int t = ronda();
        if(t==100) ret++;
    }
    return ret;
}