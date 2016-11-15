#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUFLEN 512 //Tamanho máximo do buffer
#define PORT 8888 //Porta de entrada

void die(char *s) {
    perror(s);
    exit(1);
}

int main(void) {
    struct sockaddr_in servidor, cliente;
    int s, i, slen = sizeof (cliente), recv_len;
    char buf[BUFLEN];
    char message[BUFLEN];

    //criação do socket UDP
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        die("Erro ao criar socket");
    }
    //Completa estrutura com zeros
    memset(&addr.sin_zero, 0, sizeof (addr.sin_zero));

    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    //Associa o endereço e a porta local ao socket
    if (bind(s, (struct sockaddr*) &servidor, sizeof (servidor)) == -1) {
        die("Erro ao criar bind");
    }

    //Coloca o socket em modo de espera
    while (1) {
        printf("Aguardando conexão...");
        fflush(stdout);
        memset(buf, '\0', BUFLEN);

        //tentando receber dados, bloqueia o código aguardando dados
        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &cliente, &slen)) == -1) {
            die("Erro ao receber dados");
        }

        //imprimindo detalhes do cliente e os dados recebidos
        printf("Recebendo pacotes de %s:%d\n", inet_ntoa(cliente.sin_addr), ntohs(cliente.sin_port));
        printf("Data: %s\n", buf);

        printf("Enter message : ");
        scanf("%s", message);

        //Enviando menssagem
        if (sendto(s, message, strlen(message), 0, (struct sockaddr *) &cliente, slen) == -1) {
            die("Erro ao enviar dados");
        }

        printf("Aguardando conexão...");
        fflush(stdout);
        memset((char *) &buf, 0, sizeof (BUFLEN));
    }
    close(s);
    return 0;
}
