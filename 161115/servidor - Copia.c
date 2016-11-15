#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void erro(char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    struct sockaddr_in s_servidor, s_cliente;
    char mensagem[256];
    int n;
    int n_servidor, n_cliente, porta = 8888, t_cliente = sizeof (s_cliente);

    n_servidor = socket(AF_INET, SOCK_STREAM, 0);
    if (n_servidor < 0)
        erro("Erro ao abrir socket");

    bzero((char *) &s_servidor, sizeof (s_servidor));
    s_servidor.sin_family = AF_INET;
    s_servidor.sin_addr.s_addr = INADDR_ANY;
    s_servidor.sin_port = htons(porta);

    if (bind(n_servidor, (struct sockaddr *) &s_servidor, sizeof (s_servidor)) < 0)
        erro("Erro ao associar o bind");

    listen(n_servidor, 5);

    n_cliente = accept(n_servidor, (struct sockaddr *) &s_cliente, &t_cliente);
    if (n_cliente < 0)
        erro("Erro na conexão");

    while (1) {

        bzero(mensagem, 256);

        n = read(n_cliente, mensagem, sizeof (mensagem) - 1);
        if (n < 0) erro("Erro ao receber mensagem");

        printf("Cliente: %s"
                "Servidor: ", mensagem);
        scanf("%s", mensagem);

        n = write(n_cliente, mensagem, (sizeof (mensagem)));
        if (n < 0) erro("Erro ao enviar mensagem");
    }
    return 0;
}