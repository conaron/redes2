void executa_transacao(void *funcao, void *parametro) {
    pthread_t id;
    int transacao = pthread_create(&id, NULL, funcao, parametro);
    if (transacao) {
        perror("pthread_create");
        exit(-1);
    }
}

void erro(char *msg) {
    perror(msg);
    exit(1);
}

void menu(jogo jogo) {
    int opcao = 0;

    while (1) {
        if (opcao == 1)
            return;

        tela_menu(opcao, &jogo);
        system("clear");
        printf("%s", jogo.grade);

        if (opcao == 4)
            exit(0);
        else if ((opcao < 1) || (opcao > 3)) scanf("%d", &opcao);
        else {
            getchar();
            getchar();
            opcao = 0;
        }
    }
}

void *abertura(void *p_jogo) {
    jogo *jogo = p_jogo;
    int i;

    for (i = 0; i < 25; i++) {
        animacao(jogo->grade, i);
        usleep(20000);
        system("clear");
        printf("%s", jogo->grade);
    }
    jogo->etapa++;
}