#include "person.h"
#include <fcntl.h>
#include <unistd.h>

// return 1 se correr tudo bem
// return 0 se falhar
int adicionarPessoa(char* nome, int idade){
    Pessoa p;
    p.idade = idade;
    strcpy(p.nome,nome);

    printf("Pessoa - Nome: %s, idade: %d\n", p.nome, p.idade);

    int fd = open("pessoas.db", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if(fd < 0){
        perror("Erro ao abrir o ficheiro");
        return 0;
    }

    ssize_t bytes_escritos = write(fd, &p, sizeof(Pessoa));
    if(bytes_escritos < 0){
        perror("erro na escrita");
        close(fd);
        return 0;
    }
    printf("escrevi %d bytes", bytes_escritos);

    close(fd);
    return 1;
}


// return 1 se correr tudo bem
// return 0 se falhar
int listarPessoas(int n){
    int fd = open("pessoas.db", O_RDONLY);
    if(fd < 0){
        perror("Erro ao abrir o ficheiro");
        return 0;
    }

    Pessoa p;
    ssize_t bytes_lidos;
    while((bytes_lidos = read(fd, &p, sizeof(Pessoa))) > 0){
        printf("Pessoa - Nome: %s, idade: %d\n", p.nome, p.idade);
    }

    if(bytes_lidos < 0){
        perror("erro na leitura");
        close(fd);
        return 0;
    }

    close(fd);
    return 1;
}


// return 1 se correr tudo bem
// return 0 se falhar
int atualizarPessoa(char* nome, int idade){
    Pessoa p;
    p.idade = idade;
    strcpy(p.nome,nome);

    printf("Pessoa - Nome: %s, idade: %d\n", p.nome, p.idade);

    int fd = open("pessoas.db", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if(fd < 0){
        perror("Erro ao abrir o ficheiro");
        return 0;
    }

    ssize_t bytes_escritos = write(fd, &p, sizeof(Pessoa));
    if(bytes_escritos < 0){
        perror("erro na escrita");
        close(fd);
        return 0;
    }
    printf("escrevi %d bytes", bytes_escritos);

    close(fd);
    return 1;
}
