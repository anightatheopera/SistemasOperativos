#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>

char* parse_arg(char* command){
    while(*command != '\0' && *command != ' '){
        command++;
    }
    while(*command == ' '){
        *(command++) = '\0';
    }
    return *command == '\0' ? NULL : command;
}

pid_t system2(char* command){
    pid_t child = fork();
    if(child == 0){
        char* args[69] = { 0 };
        size_t i = 0;
        do {
            args[i++] = command;
        } while((command = parse_arg(command)) != NULL);
        execvp(args[0], args);
    } else {
        return child;
    }
}

int main(int argc, char** argv){
    system2(argv[1]);
    wait(NULL);
    return 0;
}