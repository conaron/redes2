#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h> 

void erro(char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]) {
    int n_servidor, porta = 8888, i;

    struct sockaddr_in s_servidor;
    struct hostent *server;

    char mensagem[256];
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <ip servidor>\n", argv[0]);
        exit(0);
    }

    n_servidor = socket(AF_INET, SOCK_STREAM, 0);
    if (n_servidor < 0)
        erro("Erro ao abrir socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr, "IP inválido\n");
        exit(0);
    }
    bzero((char *) &s_servidor, sizeof (s_servidor));
    s_servidor.sin_family = AF_INET;
    bcopy((char *) server->h_addr,
            (char *) &s_servidor.sin_addr.s_addr,
            server->h_length);
    s_servidor.sin_port = htons(porta);
    if (connect(n_servidor, (struct sockaddr *) &s_servidor, sizeof (s_servidor)) < 0)
        erro("Erro na conexao");

    while (1) {
        printf("Cliente: ");
        bzero(mensagem, 256);
        fgets(mensagem, 255, stdin);
        i = write(n_servidor, mensagem, strlen(mensagem));
        if (i < 0)
            erro("Erro ao enviar mensagem");
        bzero(mensagem, 256);

        i = read(n_servidor, mensagem, (sizeof (mensagem)));
        if (i < 0)
            erro("Erro ao receber mensagem");

        printf("Servidor: %s\n", mensagem);
    }

    return 0;
}