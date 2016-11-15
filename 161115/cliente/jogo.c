#include "jogo/cabecalho.h"

int main(int argc, char** argv) {
    jogo jogo = {0, 0, 0, 0, 0, 0, 0};
    int i, x, y; //coordenadas cartesianas da grade
    int alvo, situacao = 1;
    char entrada[10];

    int n_servidor, porta = 8888, n;
    struct sockaddr_in s_servidor;
    struct hostent *server;

    time_t semente;
    time(&semente);

    srand((int) semente);
    construcao(&jogo);

    // socket inicio

    if (argc < 2) {
        fprintf(stderr, "Uso: %s <ip servidor>\n", argv[0]);
        exit(0);
    }

    n_servidor = socket(AF_INET, SOCK_STREAM, 0);
    if (n_servidor < 0)
        erro("Erro ao abrir socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr, "IP inv�lido\n");
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

    n = write(n_servidor, jogo.mapa, sizeof (jogo.mapa));
    if (n < 0)
        erro("Erro ao enviar mensagem");

    // socket fim

    //    for (i = 0; i < 10; i++) printf("%d", jogo.mapa[0][0][i]);
    //    exit(1);

    //    executa_transacao(construcao, &jogo);
    executa_transacao(abertura, &jogo);

    while (jogo.etapa == 0)
        continue;

    while (1) {

        menu(jogo);

        while (1) {

            if (jogo.jogador == situacao) jogo.adversario--;
            else jogo.adversario++;

            tela_jogo(&jogo);
            sprintf(jogo.grade, "%s          Jogador %d (%d pontos) - ", jogo.grade, jogo.jogador + 1, jogo.pontuacao[jogo.jogador]);

            if (jogo.jogador == situacao)
                strcat(jogo.grade, "Informe a coordenada de ataque (ou S para encerrar o jogo): ");
            else strcat(jogo.grade, "Aguardando jogada...");

            for (i = 0; i < 2; i++) // Encerramento por vitória
                if (jogo.pontuacao[i] == 30) {
                    tela_menu(5, &jogo);
                    system("clear");
                    printf("%s", jogo.grade);
                    exit(0);
                }

            system("clear");
            printf("%s", jogo.grade);

            if (jogo.jogador == situacao) {
                scanf("%s", entrada);
                n = write(n_servidor, entrada, (sizeof (entrada)));
                if (n < 0) erro("Erro ao enviar mensagem");
            } else {
                //                bzero(entrada, 10);
                n = read(n_servidor, entrada, sizeof (entrada));
                if (n < 0) erro("Erro ao receber mensagem");
            }

            if ('S' == toupper(entrada[0])) { // Encerramento por desistencia;
                tela_menu(6, &jogo);
                system("clear");
                printf("%s", jogo.grade);
                exit(0);
            } else jogo.jogada = atoi(entrada);

            if ((jogo.jogada < 0) || jogo.jogada > 99) {
                printf("%s", "                      Jogada Inválida\n");
                getchar();
                getchar();
            } else {
                x = jogo.jogada / 10;
                y = jogo.jogada - x * 10;
                alvo = jogo.mapa[jogo.adversario][x][y];

                if (alvo == 1) jogo.pontuacao[jogo.jogador]++;
                if (alvo < 2) jogo.mapa[jogo.adversario][x][y] = alvo + 2;
            }
            if (jogo.jogador == 0) jogo.jogador++;
            else jogo.jogador--;
        }
    }
    pthread_exit(NULL);
}

