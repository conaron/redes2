#include "jogo/cabecalho.h"

int main(int argc, char** argv) {
    struct sockaddr_in s_servidor, s_cliente;
    int i, x, y, situacao = 0; //coordenadas cartesianas da grade
    jogo jogo = {0, 0, 0, 0, 0, 0, 0};
    int alvo;
    char entrada[10];
    int n;
    int n_servidor, n_cliente, porta = 8888, t_cliente = sizeof (s_cliente);

    // socket inicio

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
        erro("Erro na conex�o");

    n = read(n_cliente, jogo.mapa, sizeof (jogo.mapa));
    if (n < 0) erro("Erro ao receber mensagem");

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

            if (jogo.jogador == situacao) jogo.adversario++;
            else jogo.adversario--;

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
                n = write(n_cliente, entrada, (sizeof (entrada)));
                if (n < 0) erro("Erro ao enviar mensagem");
            } else {
                //                bzero(entrada, 10);

                n = read(n_cliente, entrada, sizeof (entrada));
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

