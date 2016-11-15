#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PORTA 1234
char *end_destino = "127.0.0.1";
FILE *saida;
void * servidor();
int enviar(char msg[]);
void finalizarRegistro();

int main(int argc, char *argv[]) {
    if (argc > 1)
        end_destino = argv[1];
    saida = fopen("/tmp/registro.txt", "a+");
    if (saida == NULL) {
        puts("Nao foi possivel criar arquivo de registro\n");
    }
    puts("\nBem vindo ao chat\nPara sair digite /e \n\n\n");
    //criando uma thread
    pthread_t lendoServer;
    //iniciando a thread, está thread será responsavel em aguardar novas mensagens
    pthread_create(&lendoServer, NULL, servidor, NULL);
    //limite de caracteres sera 1000
    char msg[1000];
    int houveErro = 0;
    if (saida != NULL)
        fprintf(saida, "------------------------------------------------------\nInicio da conversa : \n\n");
    do {
        scanf("%s", msg);
        if (msg[0] == '/' && msg[1] == 'e')
            break;
        houveErro = enviar(msg);
        if (saida != NULL) {
            fprintf(saida, "|Cliente| envia: ");
            fprintf(saida, strcat(msg, "\n"));
            fflush(saida);
        }
    } while (houveErro != -1);
    finalizarRegistro();

    return 0;
}

void * servidor() {
    int eng_socket;
    //A funcao socket() é respons�vel por criar um socket e retornar uma identificação para ele
    eng_socket = socket(AF_INET, SOCK_STREAM, 0); //SOCK_STREAM - Stream Socket
    if (eng_socket == -1) {
        puts("Erro ao criar o socket.\n");
        finalizarRegistro();
        exit(1);
    }
    struct sockaddr_in addr; //armazena tds as informacoes da familia
    addr.sin_family = AF_INET; ///Familia do socket
    addr.sin_port = htons(PORTA); //porta de entrada
    //htons converte "Host Byte Order" para "Network Byte Order"
    addr.sin_addr.s_addr = INADDR_ANY; //Endereço ZERO -> utiliza endereço local padrão->Aceita qualquer tipo de mensagem
    /* Preenche o restante da estrutura com ZEROS */
    memset(&addr.sin_zero, 0, sizeof (addr.sin_zero));
    //Associa ao socket a porta e o endereço local
    if (bind(eng_socket, (struct sockaddr*) &addr, sizeof (addr)) == -1) {
        puts("Erro na funcao bind()\n");
        finalizarRegistro();
        exit(1);
    }
    //socket em modo de espera definindo um m�ximo de 1 conexão pendente
    if (listen(eng_socket, 1) == -1) {
        puts("Erro na fucao listen()\n");
        finalizarRegistro();
        exit(1);
    }
    // puts("Aguardando conexoes\n");
    int tamanhoBytesRecebidos = 0;
    while (tamanhoBytesRecebidos != -1) {
        // Aceita a primeira conexão pendente e associa o novo socket
        int socketRecebido = accept(eng_socket, 0, 0);
        if (socketRecebido == -1) {
            puts("Erro na funcao accept()");
            finalizarRegistro();
            exit(1);
        }
        // puts("Pedido de conexão feito!");
        char resposta[1000];
        memset(resposta, 0, sizeof (resposta)); //Limpa o buffer
        tamanhoBytesRecebidos = recv(socketRecebido, resposta, 100, 0);
        if (tamanhoBytesRecebidos == -1) {
            puts("Erro ao receber os dados");
        } else {
            printf("<Servidor> enviou: %s\n", resposta);
            if (saida != NULL) {

                fprintf(saida, "<Servidor> enviou: ");
                fprintf(saida, strcat(resposta, "\n"));
                fflush(saida);
            }
        }
    }
    close(eng_socket);
}

int enviar(char msg[]) {
    int eng_socket;
    eng_socket = socket(AF_INET, SOCK_STREAM, 0); //SOCK_STREAM - Stream Socket(Protocolo TCP)
    if (eng_socket == -1) {
        puts("Erro ao criar o socket.\n");
        finalizarRegistro();
        exit(1);
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORTA);
    addr.sin_addr.s_addr = inet_addr(end_destino); //Endereco de destino
    memset(&addr.sin_zero, 0, sizeof (addr.sin_zero)); ///preenchendo a var sin_zero com 000...
    if (connect(eng_socket, (struct sockaddr*) &addr, sizeof (addr)) == -1) {
        puts("Erro ao conectar\n");
        finalizarRegistro();
        exit(1);
    }
    int enviados = send(eng_socket, msg, strlen(msg), 0);
    close(eng_socket);

    return enviados;
}

void finalizarRegistro() {
    fprintf(saida, "\nFim da conversa\n\n");
    fclose(saida);
}
