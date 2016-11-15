#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUFLEN 512 //Tamanho máximo do buffer
#define PORT 8888 //Porta para envio de dados

void die(char *s) {
    perror(s);
    exit(1);
}

main(int argc, char *argv[]) {
	struct sockaddr_in servidor;
	int s, i, slen=sizeof(servidor);
	char buf[BUFLEN];
	char message[BUFLEN];
	char ip[20];
	char end_servidor[15] = "321321321";

	if (argv > 1)
		strcpy(end_servidor, argv[1]);

	if ( (s=socket(AF_INET, SOCK_STREAM, 0)) == -1){
			die("Erro ao criar socket");
	}

	memset((char *) &servidor, 0, sizeof(servidor));
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons(PORT);

	if (inet_aton(end_servidor , &servidor.sin_addr) == 0){
			fprintf(stderr, "inet_aton() failed\n");
			exit(1);
	}

	while(1){
		printf("Enter message : ");
		scanf("%s", message);

		//Enviando menssagem
		if (sendto(s, message, strlen(message) , 0 , (struct sockaddr *)&servidor, slen)==-1){
				die("Erro ao enviar dados");
		}

		//limpando o buffer
		memset(buf,'\0', BUFLEN);

		//tentando receber os dados, código fica bloqueado até receber
		if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &servidor,&slen) == -1){
				die("Erro ao receber dados");
		}

		puts(buf);
	}

	close(s);
	return 0;
}
