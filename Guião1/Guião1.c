#include <stdio.h>
#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdlib.h> /* for exit */

void mycat(int argc, char *argv[]);
void mycp(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    if (argc == 1 || (argc > 1 && argv[1][0] != '-')) {
        mycat(argc, argv);
    } else if (argc == 4 && argv[1][0] == '-' && argv[1][1] == 'c') {
        mycp(argc - 1, &argv[1]);
    } else {
        fprintf(stderr, "Usage: %s [file...]\n", argv[0]);
        fprintf(stderr, "       %s -c source_file dest_file\n", argv[0]);
        exit(1);
    }
    return 0;
}

void mycat(int argc, char *argv[]) {
    int fd;
    char buffer[1024];
    ssize_t bytes;

    if (argc == 1) {
        while ((bytes = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
            if (write(STDOUT_FILENO, buffer, bytes) != bytes) {
                perror("write");
                exit(1);
            }
        }
        if (bytes < 0) {
            perror("read");
            exit(1);
        }
    } else {
        for (int i = 1; i < argc; i++) {
            fd = open(argv[i], O_RDONLY);
            if (fd < 0) {
                perror("open");
                exit(1);
            }
            while ((bytes = read(fd, buffer, sizeof(buffer))) > 0) {
                if (write(STDOUT_FILENO, buffer, bytes) != bytes) {
                    perror("write");
                    close(fd);
                    exit(1);
                }
            }
            if (bytes < 0) {
                perror("read");
                close(fd);
                exit(1);
            }
            close(fd);
        }
    }
}

void mycp(int argc, char *argv[]) {
    int fd1, fd2;
    char buffer[1024];
    ssize_t bytes;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s source_file dest_file\n", argv[0]);
        exit(1);
    }

    fd1 = open(argv[1], O_RDONLY);
    if (fd1 < 0) {
        perror("open source_file");
        exit(1);
    }

    fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd2 < 0) {
        perror("open dest_file");
        close(fd1);
        exit(1);
    }

    while ((bytes = read(fd1, buffer, sizeof(buffer))) > 0) {
        if (write(fd2, buffer, bytes) != bytes) {
            perror("write");
            close(fd1);
            close(fd2);
            exit(1);
        }
    }
    if (bytes < 0) {
        perror("read");
    }

    close(fd1);
    close(fd2);
}