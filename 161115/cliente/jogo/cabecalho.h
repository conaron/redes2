#include <arpa/inet.h>
#include <ctype.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h> 
#include <unistd.h>
#include <netdb.h> 


//! Dimensão (lado) do tabuleiro
#define T         10 
//! Quantidade de caracteres da tela
#define TT      2700 
//! Linha do cabeçalho
#define LINHA_T  703

//! Estrutura do elemento jogo

/*! Definição do jogo com atributos pertinentes */
struct jogo {
    //! Mapa de barcos com a situação deles (ativo / abatido)
    int mapa[2][T][T];
    //! Lista de barcos
    int barcos[2][T];
    //! Jogador da rodada
    int jogador;
    //! Oponente da rodada
    int adversario;
    //! Pontuação de cada jogador (lembrando que quem fizer 30 antes ganha :) )
    int pontuacao[2];
    //! Valor da jogada de ataque (saida ou coordenadas)
    int jogada;
    //! Divisor de momento entre a abertura e o menu do jogo
    int etapa;
    //! Tela com o mapa impresso
    char grade[TT];
} typedef jogo;


//! Executa uma função através de uma thread
void executa_transacao(void *funcao, void *parametro);
//! Controla a tela a ser impressa no menu atraves da entrada da opção
void menu(jogo jogo);
//! Executado por thread - Executa a animação na abertura do jogo
void *abertura(void *p_jogo);

//! Monta uma 'moldura' padrão para ser alterada conforme necessário
char tela(char *tela);
//! 'Traduz' a situação do bloco da grade para uma versão impressa (-: tiro na agua, X: bloco pontuado e ' ': para intocado )
char mascara(int valor);
//! Preenche uma linha centralizando o conteúdo informado
char linha(int linha, char *retorno, char *conteudo);
//! Monta a tela com a estrutura do jogo propriamente dito com tabuleiros e chamada de ataque
char tela_jogo(jogo *p_jogo);
//! Monta a tela conforme a opção do menu (incluindo duas situaçÃµes de vitória que só ocorrem durante o jogo)
char tela_menu(int opcao, jogo *p_jogo);
//! Monta as telas da animação da abertura do jogo conforme sua ordem de aparição
char animacao(char *retorno, int loop);


//! Verifica se o espaço destinado para o barco esta livre e o estabelece
int preenchimento(int blocos, int barco[10], int posicao, int grade[T][T]);
//! Executado por thread - Popula as duas grades com os barcos necessários
void construcao(jogo *p_jogo);

#include "situacoes.c"
#include "telas.c"
#include "metodos.c"
