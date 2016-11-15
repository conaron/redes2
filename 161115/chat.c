#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h>

int main(int argc, char *argv[]) {
    struct mensagem destino;
    int i = 0, m_socket = 0, conexao = 0;
    char mensagem[1025];

    if ((argv[1][0] != '-') || ((argv[1][1] != 's')&&(argv[1][1] != 'c')) || ((argv[1][1] == 'c')&&(argv[2] == NULL))) {
        printf("\n Modo de uso: %s <opcao> [ip do servidor] \n\n"
                "Opcoes:\n"
                "-c      Modo Cliente <ip do servidor>\n"
                "        ex.: %s -c 192.168.0.1\n\n"
                "-s      Modo Servidor\n\n\n"
                "", argv[0], argv[0]);
        exit(1);
    }

    memset(&destino, '0', sizeof (destino));
    memset(mensagem, '0', sizeof (mensagem));

    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket < 0) {
        printf("\n Erro : Não foi possível criar o socket \n");
        exit(1);
    }

    destino.sin_family = AF_INET;
    destino.sin_port = htons(8888);

    switch (argv[1][1]) {
        case 's':
            destino.sin_addr.s_addr = htonl(INADDR_ANY);
            bind(m_socket, (struct sockaddr*) &destino, sizeof (destino));
            listen(m_socket, 10);

            while (1) {
                conexao = accept(m_socket, (struct sockaddr*) NULL, NULL);
                if (conexao > 0) {
                    sprintf(mensagem, "Parabens, sucesso %d\r\n", conexao);
                    write(conexao, mensagem, strlen(mensagem));
                    close(conexao);
                    sleep(1);
                }
            }
            break;
        case 'c':
            destino.sin_addr.s_addr = inet_addr(argv[2]);
            if (inet_pton(AF_INET, argv[2], &destino.sin_addr) <= 0) {
                printf("\n Erro: IP do servidor inválido\n");
                return 1;
            }

            system("clear");

            while (1) {

                printf("Aguardando servidor\n");

                while ((i = connect(m_socket, (struct sockaddr *) &destino, sizeof (destino))) < 0)
                    continue;

                while ((i = read(m_socket, mensagem, sizeof (mensagem) - 1)) > 0)
                    mensagem[i] = 0;

                puts(mensagem);
                printf("Servidor: %s\n", mensagem);
                printf("Cliente: ");
                scanf("%s", mensagem);


            }

            return 0;
            break;
    }

    return 0;
}
