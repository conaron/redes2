#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUFLEN 512 //Tamanho máximo do buffer
#define PORT 8888 //Porta de entrada


void die(char *s) {
	perror(s);
	exit(1);
}

int main(void) {
	struct sockaddr_in addr, addr_other;
	int s, i, slen = sizeof(addr_other) , recv_len;
	char buf[BUFLEN];
	char message[BUFLEN];


	//criação do socket UDP
	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
			die("Erro ao criar socket");
	}
	//Completa estrutura com zeros
	memset((char *) &addr, 0, sizeof(addr));

	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	//Associa o endereço e a porta local ao socket
	if( bind(s , (struct sockaddr*)&addr, sizeof(addr) ) == -1){
			die("Erro ao criar bind");
	}

	//Coloca o socket em modo de espera
	 while(1){
		printf("Enter message : ");
		gets(message);
		
		printf("Aguardando conexão...");
		fflush(stdout);
		memset(buf,'\0', BUFLEN);

		//tentando receber dados, bloqueia o código aguardando dados
		if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *)&addr_other, &slen)) == -1){
				die("Erro ao receber dados");
		}

		//imprimindo detalhes do cliente e os dados recebidos
		printf("Recebendo pacotes de %s:%d\n",inet_ntoa(addr_other.sin_addr), ntohs(addr_other.sin_port));
		printf("Data: %s\n" , buf);

		//Replicando o valor recebido
		if (sendto(s, buf, recv_len, 0, (struct sockaddr*) &addr_other,slen) == -1){
				die("Erro ao replicar dados");
		}
		printf("Aguardando conexão...");
		fflush(stdout);
		memset((char *) &buf, 0, sizeof(BUFLEN));
		
	}	
    close(s);
    return 0;
}
