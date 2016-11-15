#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define SERVER "127.0.0.0"
#define BUFLEN 512 //Tamanho máximo do buffer
#define PORT 8888 //Porta para envio de dados

void die(char *s) {
    perror(s);
    exit(1);
}

int main(void) {
	char servidor[20] = "127.0.0.0";
	struct sockaddr_in addr_other;
	int s, i, slen=sizeof(addr_other);
	char buf[BUFLEN];
	char message[BUFLEN];

	if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
			die("Erro ao criar socket");
	}

	memset((char *) &addr_other, 0, sizeof(addr_other));
	addr_other.sin_family = AF_INET;
	addr_other.sin_port = htons(PORT);

	if (inet_aton(servidor, &addr_other.sin_addr) == 0){
			fprintf(stderr, "inet_aton() failed\n");
			exit(1);
	}

	while(1){
		printf("Enter message : ");
		gets(message);

		//Enviando menssagem
		if (sendto(s, message, strlen(message) , 0 , (struct sockaddr *)&addr_other, slen)==-1){
				die("Erro ao enviar dados");
		}

		//limpando o buffer
		memset(buf,'\0', BUFLEN);

		//tentando receber os dados, código fica bloqueado até receber
		if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &addr_other,&slen) == -1){
				die("Erro ao receber dados");
		}

		puts(buf);
	}

	close(s);
	return 0;
}
