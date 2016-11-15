char tela(char *tela) {
    strcpy(tela,
            "\n\n\n"
            "          * ---------------------------------------------------------------------------------------------------- *\n"
            "          |                                                                                                      |\n"
            "          |                                    * B A T A L H A    N A V A L *                                    |\n"
            "          |                                                                                                      |\n"
            "          * ---------------------------------------------------------------------------------------------------- *\n"
            "          |                                                                                                      |\n"
            "          |                                                                                                      |\n"
            "          |                                                                                                      |\n"
            "          |                                                                                                      |\n"
            "          |                                                                                                      |\n"
            "          |                                                                                                      |\n"
            "          |                                                                                                      |\n"
            "          |                                                                                                      |\n"
            "          |                                                                                                      |\n"
            "          |                                                                                                      |\n"
            "          |                                                                                                      |\n"
            "          |                                                                                                      |\n"
            "          |                                                                                                      |\n"
            "          |                                                                                                      |\n"
            "          |                                                                                                      |\n"
            "          |                                                                                                      |\n"
            "          |                                                                                                      |\n"
            "          * ---------------------------------------------------------------------------------------------------- *\n"
            );
}

char mascara(int valor) {
    if (valor == 2) return '-';
    else if (valor == 3) return 'X';
//    else if (valor == 1) return '1'; // Caso queira enxergar os barcos
    else return ' ';
}

char linha(int linha, char *retorno, char *conteudo) {
    int i;
    int posicao = LINHA_T + (115 * linha);
    int margem = (105 - strlen(conteudo)) / 2;
    for (i = 0; i < strlen(conteudo); i++)
        retorno[i + posicao + margem] = (conteudo)[i];
}

char tela_jogo(jogo *p_jogo) {
    jogo *jogo = p_jogo;
    int i, j;
    int posicao = LINHA_T + 471;

    tela(jogo->grade);
    linha(0, jogo->grade, "* J O G A D O R   1 *                           * J O G A D O R   2 *");
    linha(1, jogo->grade, " -----------------------------------------       -----------------------------------------");
    linha(2, jogo->grade, "   0   1   2   3   4   5   6   7   8   9          0   1   2   3   4   5   6   7   8   9  ");
    linha(3, jogo->grade, " -----------------------------------------       -----------------------------------------");
    linha(4, jogo->grade, "0 |   |   |   |   |   |   |   |   |   |   |    0 |   |   |   |   |   |   |   |   |   |   |");
    linha(5, jogo->grade, "1 |   |   |   |   |   |   |   |   |   |   |    1 |   |   |   |   |   |   |   |   |   |   |");
    linha(6, jogo->grade, "2 |   |   |   |   |   |   |   |   |   |   |    2 |   |   |   |   |   |   |   |   |   |   |");
    linha(7, jogo->grade, "3 |   |   |   |   |   |   |   |   |   |   |    3 |   |   |   |   |   |   |   |   |   |   |");
    linha(8, jogo->grade, "4 |   |   |   |   |   |   |   |   |   |   |    4 |   |   |   |   |   |   |   |   |   |   |");
    linha(9, jogo->grade, "5 |   |   |   |   |   |   |   |   |   |   |    5 |   |   |   |   |   |   |   |   |   |   |");
    linha(10, jogo->grade, "6 |   |   |   |   |   |   |   |   |   |   |    6 |   |   |   |   |   |   |   |   |   |   |");
    linha(11, jogo->grade, "7 |   |   |   |   |   |   |   |   |   |   |    7 |   |   |   |   |   |   |   |   |   |   |");
    linha(12, jogo->grade, "8 |   |   |   |   |   |   |   |   |   |   |    8 |   |   |   |   |   |   |   |   |   |   |");
    linha(13, jogo->grade, "9 |   |   |   |   |   |   |   |   |   |   |    9 |   |   |   |   |   |   |   |   |   |   |");
    linha(14, jogo->grade, " -----------------------------------------       -----------------------------------------");

    for (i = 0; i < T; i++) {
        for (j = 0; j < T; j++) {
            jogo->grade[posicao + j] = mascara(jogo->mapa[0][i][j]);
            jogo->grade[posicao + j + 47] = mascara(jogo->mapa[1][i][j]);
            posicao = posicao + 3;
        }
        posicao = posicao + 85;
    }
}

char tela_menu(int opcao, jogo *p_jogo) {
    jogo *jogo = p_jogo;
    tela(jogo->grade);
    switch (opcao) {
        case 2:
            linha(0, jogo->grade, "* Idealizadores *");
            linha(3, jogo->grade, "Curso: Sistemas para Internet           ");
            linha(4, jogo->grade, "Semestre: 4                             ");
            linha(5, jogo->grade, "Prof.: Thais Viegas                     ");
            linha(8, jogo->grade, "Matricula     Nome                      ");
            linha(9, jogo->grade, "006697-4      Airton da Rocha Bernardoni");
            linha(10, jogo->grade, "007715-1      Gabriel Carneiro Minatto  ");
            linha(14, jogo->grade, "* Pressione Enter para retornar *");
            break;
        case 3:
            linha(0, jogo->grade, "* Ajuda *");
            linha(1, jogo->grade, "Como jogar:                                                                                 ");
            linha(2, jogo->grade, "     Na sua vez de jogar, informe as coordenadas conforme o bloco que deseja atacar no campo");
            linha(3, jogo->grade, "        oponente, Sempre linha e coluna. Ex: 21 (veja o quadro abaixo)                      ");
            linha(5, jogo->grade, "Ganhando:                                                                  -----------------");
            linha(6, jogo->grade, "     Cada campo possui 10 barcos.                                            0   1   2   3  ");
            linha(7, jogo->grade, "        1 Barco de 5 blocos;                                               -----------------");
            linha(8, jogo->grade, "        2 Barcos de 4 blocos;                                            0 |   |   |   |   |");
            linha(9, jogo->grade, "        3 Barcos de 3 blocos;                                            1 |   |   |   |   |");
            linha(10, jogo->grade, "        4 Barcos de 2 blocos;                                            2 |   | X |   |   |");
            linha(11, jogo->grade, "     Vence quem atingir primeiro todos os barcos do oponente             3 |   |   |   |   |");
            linha(12, jogo->grade, "        (30 pontos) primeiro ou se o oponente desistir!                    -----------------");
            linha(14, jogo->grade, "* Pressione Enter para retornar *");
            break;
        case 4:
            linha(0, jogo->grade, "* Adeus! *");
            linha(7, jogo->grade, "Muito obrigado por jogar nosso jogo!");
            break;
        case 5:
            linha(0, jogo->grade, "* Vitoria! *");
            if (jogo->pontuacao[0] > jogo->pontuacao[1])
                linha(7, jogo->grade, "Jogador 1 venceu!!!");
            else
                linha(7, jogo->grade, "Jogador 2 venceu!!!");
            break;
        case 6:
            linha(0, jogo->grade, "* Vitoria! *");
            if (jogo->pontuacao[0] > jogo->pontuacao[1])
                linha(7, jogo->grade, "Jogador 1 ganhou por desistencia do oponente!!!");
            else
                linha(7, jogo->grade, "Jogador 2 ganhou por desistencia do oponente!!!");
            break;
        default:
            linha(0, jogo->grade, "* Menu de Opcoes *");
            linha(6, jogo->grade, "1 - Jogo           ");
            linha(7, jogo->grade, "2 - Desenvolvedores");
            linha(8, jogo->grade, "3 - Ajuda          ");
            linha(9, jogo->grade, "4 - Sair           ");
            strcat(jogo->grade, "\nInforme a opção desejada: ");
            break;
    }

}

char animacao(char *retorno, int loop) {
    int i, j, posicao;
    tela(retorno);

    for (i = 0; i < 100; i++)
        retorno[i + 245] = retorno[i + 475] = ' ';

    if (loop < 16) {
        for (i = 0; i < 66; i++) {
            posicao = i + loop + 130;
            retorno[posicao + 115 * 0] = "   (_    _)                     0_,-.__                           "[i];
            retorno[posicao + 115 * 1] = "      (_  )_                     |_.-._/                          "[i];
            retorno[posicao + 115 * 2] = "        (    )                    |_--..\\                         "[i];
            retorno[posicao + 115 * 3] = "        (__)                     |__--_/                          "[i];
            retorno[posicao + 115 * 4] = "      |''   ``\\                   |                               "[i];
            retorno[posicao + 115 * 5] = "      |        \\                  |      /b.                      "[i];
            retorno[posicao + 115 * 6] = "      |         \\  ,,,---===?A`\\  |  ,==y'                        "[i];
            retorno[posicao + 115 * 7] = "     ___,,,,,---==''\\        |M] \\ | ;|\\ |>                       "[i];
            retorno[posicao + 115 * 8] = "            _   _   \\   ___,|H,,---==''''bno,                     "[i];
            retorno[posicao + 115 * 9] = "     o  O  (_) (_)   \\ /          _     AWAW/                     "[i];
            retorno[posicao + 115 * 10] = "                     /         _(+)_  dMM/                        "[i];
            retorno[posicao + 115 * 11] = "        \\@_,,,,,,---=='   \\      \\\\|//  MW/                       "[i];
            retorno[posicao + 115 * 12] = "--'''''                         ===  d/                           "[i];
            retorno[posicao + 115 * 13] = "                                    //                            "[i];
            retorno[posicao + 115 * 14] = "                                    ,'__________________________  "[i];
            retorno[posicao + 115 * 15] = "     \\    \\    \\     \\               ,/~~~~~~~~~~~~~~~~~~~~~~~~~~~"[i];
            retorno[posicao + 115 * 16] = "                         _____    ,'  ~~~   .-''-.~~~~~~  .-''-.  "[i];
            retorno[posicao + 115 * 17] = "      .-''-.           ///==---   /`-._ ..-'      -.__..-'        "[i];
            retorno[posicao + 115 * 18] = "                `-.__..-' =====\\\\\\\\\\\\ V/  .---\\.                  "[i];
            retorno[posicao + 115 * 19] = "                       ~~~~~~~~~~~~, _',--/_.\\  .-''-.            "[i];
            retorno[posicao + 115 * 20] = "                             .-''-.___` --  \\|         -.__..-    "[i];
        }
    } else if ((loop == 16) || (loop == 19) || (loop == 22)) {
        linha(0, retorno, "****#****");
        linha(1, retorno, "***#@##*#@#****");
        linha(2, retorno, "*@**@@@*##**#*#**#*");
        linha(3, retorno, "**@@*#**#@*#@****#***");
        linha(4, retorno, "****@*@***#****@**@@*");
        linha(5, retorno, "*******@***@@***#****#*");
        linha(6, retorno, "*#***#*##@****##@@@**");
        linha(7, retorno, "**#@###****@*********");
        linha(8, retorno, "*****@**@*@*****@**");
        linha(9, retorno, "************@**");
        linha(10, retorno, "****#****");
    } else if ((loop == 17) || (loop == 20) || (loop == 23)) {
        linha(-5, retorno, "****   **#**@ #**#*#   ****");
        linha(-4, retorno, "***  **  **##** *@@*@*  **  ***");
        linha(-3, retorno, "**  *  @@   *@*#* ***@*   *#  *  **");
        linha(-2, retorno, "*** #  *  *#  *@#** ***@*  **  @  * *@*");
        linha(-1, retorno, "** *  * ** *@  ****@ @****  ** #* *  * **");
        linha(0, retorno, "** * @* * ** *@  #### *#**  ** ** * @* * **");
        linha(1, retorno, "*# * # ** * #* *  **** ****  @ ** * ** * * #*");
        linha(2, retorno, "** * *# * @ * #  @  @*@ *#*  *  @ # # * @* * **");
        linha(3, retorno, "*# * * * * # * @* * **# *#* * ** * * * * * # **");
        linha(4, retorno, "** # * * @ * * # * # ** @* * * * * * # @ @ * **");
        linha(5, retorno, "*# * * * * * * * * # * * * * * * @ @ * * * * * **");
        linha(6, retorno, "*# * @ * @ * @ * * * ** *@ * * # * * * * * @ @*");
        linha(7, retorno, "*# # @ * * # * *@ * *** @#@ @ ** * @ @ * * # **");
        linha(8, retorno, "*# * ** * * * @  @  **@ ***  *  @ * * * @* * #*");
        linha(9, retorno, "** * * ** * #@ *  #*** **##  * #* * #@ * * @*");
        linha(10, retorno, "*# * *@ * @@ *#  **** @***  ** ** * #* * #*");
        linha(11, retorno, "*# *  * *@ **  @**@* *@#**  ** ** *  * @*");
        linha(12, retorno, "*#* @  *  @@  **##* ****@  **  #  * @**");
        linha(13, retorno, "**  @  #*   @*@#* @*@*#   @#  *  **");
        linha(14, retorno, "*#*  @*  @#*@*# **#*@#  **  ***");
        linha(15, retorno, "****   *##**# #***@*   @***");
    } else if ((loop == 18) || (loop == 21) || (loop == 24)) {
        linha(-5, retorno, "* -- - -- -- --  --   ------ ------   --  -- -- -- - -- *");
        linha(-4, retorno, "** - -  - -- -- --  --  ------ ------  --  -- -- -- -  - - **");
        linha(-3, retorno, "*  - - -- - -- -  -  --   ----- -----   --  -  - -- - -- - -  *");
        linha(-2, retorno, "** - - - -- - -- -  -  --  ----- -----  --  -  - -- - -- - - - **");
        linha(-1, retorno, "* - - - -  - - -  - -- --  ----- -----  -- -- -  - - -  - - - - *");
        linha(0, retorno, "* - - - -  - - - -- - -- --  ---- ----  -- -- - -- - - -  - - - - *");
        linha(1, retorno, "* -- - - - - - - - -- - -- -  ---- ----  - -- - -- - - - - - - - -- *");
        linha(2, retorno, "* - - - - - - - -- - - - -  -  --- ---  -  - - - - -- - - - - - - - *");
        linha(3, retorno, "* - - - - - - - - - - - - -- - --- --- - -- - - - - - - - - - - - - *");
        linha(4, retorno, "* - - - - - - - - - - - - - - - -- -- - - - - - - - - - - - - - - - *");
        linha(5, retorno, "* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *");
        linha(6, retorno, "* - - - - - - - - - - - - - - - -- -- - - - - - - - - - - - - - - - *");
        linha(7, retorno, "* - - - - - - - - - - - - -- - --- --- - -- - - - - - - - - - - - - *");
        linha(8, retorno, "* - - - - - - - -- - - - -  -  --- ---  -  - - - - -- - - - - - - - *");
        linha(9, retorno, "* -- - - - - - - - -- - -- -  ---- ----  - -- - -- - - - - - - - -- *");
        linha(10, retorno, "* - - - -  - - - -- - -- --  ---- ----  -- -- - -- - - -  - - - - *");
        linha(11, retorno, "* - - - -  - - -  - -- --  ----- -----  -- -- -  - - -  - - - - *");
        linha(12, retorno, "** - - - -- - -- -  -  --  ----- -----  --  -  - -- - -- - - - **");
        linha(13, retorno, "*  - - -- - -- -  -  --   ----- -----   --  -  - -- - -- - -  *");
        linha(14, retorno, "** - -  - -- -- --  --  ------ ------  --  -- -- -- -  - - **");
        linha(15, retorno, "* -- - -- -- --  --   ------ ------   --  -- -- -- - -- *");
    }
}