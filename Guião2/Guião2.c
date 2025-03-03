#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void primeiro() {
    int res = fork();

    if (res == 0){
        printf("FILHO | res: %d\n", res);
        printf("FILHO | my pid: %d\n", getpid());
        printf("FILHO | my parent pid: %d\n", getppid());
    } else {
        printf("PAI | res: %d\n", res);
        printf("PAI | my pid: %d\n", getpid());
        printf("PAI | my parent pid: %d\n", getppid());
    }
    
    printf("Terminei (pid=%d)\n", getpid());
}

// res == 0 se for filho e res == pid do filho se for pai
void segundo(){
    int res = fork();
    
    if (res == 0){
        printf("FILHO | my pid: %d\n", getpid());
        printf("FILHO | my parent pid: %d\n", getppid());
    } else {
        printf("PAI | child pid: %d\n", res);
        printf("PAI | my pid: %d\n", getpid());
        printf("PAI | my parent pid: %d\n", getppid());
    }
}

void terceiro(){
    for (int i = 1; i <= 10; i++){
        int res = fork();
        if (res == 0){
            printf("FILHO | my pid: %d\n", getpid());
            printf("FILHO | my parent pid: %d\n", getppid());
            exit(i);
        } else {
            int status;
            wait(&status);
            printf("PAI | child %d exit code: %d\n", i, WEXITSTATUS(status));
        }
    }
    printf("Todos os filhos terminaram\n");
}

void quarto(){
    for (int i = 1; i <= 10; i++){
        int res = fork();
        if (res == 0){
            printf("FILHO %d | my pid: %d\n", i, getpid());
            printf("FILHO %d | my parent pid: %d\n", i, getppid());
            exit(i);
        }
    }

    for (int i = 1; i <= 10; i++){
        int status;
        wait(&status);
        printf("PAI | child %d exit code: %d\n", i, WEXITSTATUS(status));
    }

    printf("Todos os filhos terminaram\n");
}

/*
4. Implemente um programa que crie dez processos filhos que deverao executar em concorrencia. O pai
devera esperar pelo fim da execucao de todos os seus filhos, imprimindo os respetivos codigos de saıda.

5. Pretende-se determinar a existˆencia de um determinado n´umero inteiro nas linhas de numa matriz de
n´umeros inteiros, em que o n´umero de colunas ´e muito maior do que o n´umero de linhas. Implemente,
utilizando processos um programa que determine a existˆencia de um determinado n´umero, recebido como
argumento, numa matriz gerada aleatoriamente.

6. A partir do cen´ario descrito no exerc´ıcio anterior, pretende-se que imprima por ordem crescente os
n´umeros de linha onde existem ocorrˆencias do n´umero.

1. Implemente uma nova vers˜ao do programa feito nos exerc´ıcios anteriores que opere sobre uma matriz
persistida em ficheiro (em formato bin´ario). A matriz deve ser gerada aleatoriamente pelo processo pai
e escrita em ficheiro, no in´ıcio da execuc¸ ˜ao do programa. Ap´os este passo deve ser poss´ıvel pesquisar a
existˆencia de um determinado n´umero utilizando m´ultiplos processos.
*/

int main() {
    //primeiro();
    //segundo();
    //terceiro();
    quarto();
    return 0;
}