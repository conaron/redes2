#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

#define MINHA_PORTA     20000

main() {
    int Meusocket;
    struct mensagem vitima;
    struct mensagem meu_endereco;
    int Conector;

    Meusocket = socket(AF_INET, SOCK_STREAM, 0);
    if (Meusocket < 0) /* Aqui faz-se uma simples checagem de erro */ {
        perror("Socket");
        exit(1);
    }

    vitima.sin_family = AF_INET;
    vitima.sin_port = htons(31337);
    vitima.sin_addr.s_addr = inet_addr("200.100.100.1");
    bzero(&(vitima.sin_zero), 8);

    local.sin_family = AF_INET;
    local.sin_port = htons(MINHA_PORTA);
    local.sin_addr.s_addr = inet_addr("200.100.100.1");
    bzero(&(local.sin_zero), 8);
    
    bind(Meusocket,(struct sockaddr *)&local,sizeof(struct sockaddr));

    Conector = connect(Meusocket, (struct sockaddr *) &vitima, sizeof (vitima));
    if (Conector < 0) /* Mais uma checagem de erro */ {
        perror("Connect");
        exit(1);
    }
}
