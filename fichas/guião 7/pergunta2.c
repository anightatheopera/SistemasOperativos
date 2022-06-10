#include <signal.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void handler(int sig){
        exit(-1);
}

int grep(char* word, char* file, int sleepsecs){
    pid_t pid = fork();
    if (pid == 0){
        sleep(sleepsecs);
        execlp("grep", "grep", word, file, NULL);
        exit(-1);
    } else {
        return pid;
    }
}

void multigrep(char* word, char** filepaths, int n, pid_t* grep_pid){
    for(size_t i = 0; i < n; i++){
        grep_pid[i] = grep(word, filepaths[i], i*5);
    }
}

int main(){
    signal(SIGINT, handler);

    char* files[] = { "tmp.c", "tmp2.c" };
    size_t num_files = sizeof(files)/sizeof(files[0]);

    pid_t grep_pid[69] = { 0 };

    multigrep("stuff", files, num_files, grep_pid);

    size_t active_greps = num_files;
    while(active_greps > 0){
        int wstatus;
        pid_t child_pid = wait(&wstatus);
        printf("terminated: %d with status %d\n", child_pid, WEXITSTATUS(wstatus));
        active_greps--;

        for(size_t i = 0; i < num_files; i++){
            if(grep_pid[i] == child_pid){
                grep_pid[i] = 0;
            }
        }

        if(WEXITSTATUS(wstatus) == 0){
            printf("found!\n");
            for(size_t i = 0; i < num_files; i++){
                if(grep_pid[i] != 0){
                    printf("sending kill signal to %d\n", grep_pid[i]);
                    kill(grep_pid[i], SIGINT);
                }
            }
            break;
        }
    }

    while(active_greps > 0){
        int wstatus;
        pid_t child_pid = wait(&wstatus);
        printf("terminated: %d\n", child_pid);
        active_greps--;
    }

    return 0;
}
