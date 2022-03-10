#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define COLS 100
#define LINE 5

//gerar random matriz
void fill_matrix(int* m){
    memset(m, 0, COLS * LINE * sizeof(int));
    m[69] = 1;
}


//exercicio 5 e 6 no mesmo
int encontraNum(int x, int m[LINE][COLS]){ 
    pid_t children[LINE];
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
            children[i] = pid_child;
        }
    }

    bool found[LINE];
    for(int i = 0; i < LINE; i++){
        int wstatus;
        waitpid(children[i], &wstatus, 0);
        found[i] = WEXITSTATUS(wstatus);
    }

    for(int i = 0; i < LINE; i++){
      printf("%s for line %d.\n", found[i] ? "found" : "not found", i);
    }
    return -1;
}

int main(){
    int matrix[LINE][COLS];
    fill_matrix((int*) matrix);
    printf("resultado: %d\n", encontraNum(3,matrix));
    return 0;
}