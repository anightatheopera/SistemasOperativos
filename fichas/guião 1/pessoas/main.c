#include <sys/types.h> 
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */ 
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */ 
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_NAME_SZ 32

typedef struct person{
    char name[MAX_NAME_SZ];
    size_t name_sz;
    int age;
} Person;

Person Person_new(char* name, int age){
    Person p = {0};
    p.age = age;
    p.name_sz = strlen(name);
    if(p.name_sz > MAX_NAME_SZ){
        fprintf(stderr, "Your name is too big '%s', unlucky.\n", name);
        exit(1);
    }
    memcpy(p.name, name, p.name_sz);
    return p;
}

void Person_debug(Person* p){
    printf("Person{ name: '%s', age: '%d'}\n", p->name, p->age);
}

ssize_t append(char* name, int age){
    int fd = open("pessoas.bin", O_RDWR | O_CREAT | O_APPEND, 0666);
    Person p = Person_new(name, age);
    Person_debug(&p);
    off_t a = lseek(fd,0,SEEK_END) / (off_t) sizeof(p);
    printf("registo %ld\n", a);
    return write(fd, &p, sizeof(p));
}

ssize_t update(char* name, int age){
    int fd = open("pessoas.bin", O_RDWR | O_CREAT, 0666);
    Person p =  {0};
    ssize_t nbr;
    while(nbr = read(fd,&p,sizeof(p)) && strcmp(p.name,name));
    if (!nbr) exit(1); 
    lseek(fd,-(off_t) sizeof(p),SEEK_CUR);
    p.age = age;
    return write(fd, &p, sizeof(p));  
}

ssize_t numberUp(int code, int age){
    int fd = open("pessoas.bin", O_RDWR | O_CREAT, 0666);
    Person p =  {0};
    lseek(fd,code * (off_t) sizeof(p),SEEK_SET);
    ssize_t nbr = read(fd,&p,sizeof(p));
    if (!nbr) exit(1); 
    lseek(fd,-(off_t) sizeof(p),SEEK_CUR);
    p.age = age;
    return write(fd, &p, sizeof(p));  
}

void list(){
    int fd = open("pessoas.bin", O_RDONLY | O_CREAT, 0666);
    Person p;
    while(read(fd, &p, sizeof(p))){
        Person_debug(&p);
    }
}

void main(int argc, char** argv){
    if(argc == 2 && !strcmp(argv[1], "-l")) {
        list();
    } else if(argc == 4 && !strcmp(argv[1], "-i")) {
        append(argv[2], atoi(argv[3]));
    } else if(argc == 4 && !strcmp(argv[1], "-u")) {
        update(argv[2],atoi(argv[3]));
    }
      else if(argc == 4 && !strcmp(argv[1], "-o")) {
        numberUp(atoi(argv[2]),atoi(argv[3]));
    }
     else {
        fprintf(stderr, "bad arguments bruh\n");
    }
}

// adicionar 1000
// 1ª iteraçao: 0,46s user 0,20s system 104% cpu 0,634 total
// 2ª iteraçao: 0,46s user 0,20s system 104% cpu 0,634 total
// 3ª iteraçao: 0,48s user 0,17s system 105% cpu 0,617 total
// 4ª iteraçao: 0,50s user 0,20s system 104% cpu 0,670 total
// Observa-se que não existe qualquer tipo de degradação significativa


// dar update com 1000 pessoas
// 1ª iteraçao: 0,00s user 0,00s system 67% cpu 0,001 total
// 2ª iteraçao: 0,00s user 0,00s system 64% cpu 0,001 total
// 3ª iteraçao: 0,00s user 0,00s system 66% cpu 0,001 total
// 4ª iteraçao: 0,00s user 0,00s system 72% cpu 0,001 total
// Observa-se que não existe qualquer tipo de degradação significativa
