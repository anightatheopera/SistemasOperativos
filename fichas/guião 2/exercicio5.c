#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define COLS 100
#define LINE 5

//gerar random matriz
void fill_matrix(int* m){
    memset(m, 0, COLS * LINE * sizeof(int));
    m[69] = 1;
}

int encontraNum(int x, int m[LINE][COLS]){ 
    for(int i = 0; i < LINE; i++){
        pid_t pid_child = fork();
        if(pid_child == 0){
        // child code
            for(int j = 0; j < COLS; j++){
                if(m[i][j] == x)
                    exit(1);
            }
            exit(0);
        } else {
            continue;
        }
    }
    for(int i = 0; i < LINE; i++){
        int wstatus;
        wait(&wstatus);
        if(WEXITSTATUS(wstatus) == 1)
            return 1;
    }
    return 0;
}

int main(){
    int matrix[LINE][COLS];
    fill_matrix((int*) matrix);
    printf("resultado: %d\n", encontraNum(1,matrix));
    return 0;
}