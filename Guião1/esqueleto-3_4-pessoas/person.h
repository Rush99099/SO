#include <stdio.h>
#include <string.h>

#define DB "pessoas.db"

typedef struct pessoa{
    char nome[100];
    int idade
} Pessoa;

// return 1 se correr tudo bem
// return 0 se falhar
int adicionarPessoa(char* nome, int idade);


// return 1 se correr tudo bem
// return 0 se falhar
int listarPessoas(int n);


// return 1 se correr tudo bem
// return 0 se falhar
int atualizarPessoa(char* nome, int idade);
