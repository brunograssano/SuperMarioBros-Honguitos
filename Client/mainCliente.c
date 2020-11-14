#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define FORMAT " %[^\n]"
#define IP "127.0.0.1"
#define PORT 5003

int main(){

	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){ 
		printf("\n No se pudo crear el socket. Abortamos\n"); 
		return -1; 
	}

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT);
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, IP, &serv_addr.sin_addr)<=0){
		printf("\nInvalid address/ Address not supported \n"); 
		return -1;
	}
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
		printf("\nConnection Failed \n"); 
		return -1; 
	}

	char msg[100] = "";
	int i = 0;
	while(i < 5){
		memset(msg, 0, 100);
		printf("Escriba en mensaje a enviar: ");
		scanf(FORMAT, msg);
		send(sock, msg, strlen(msg), 0);
		printf("\nSe envió el mensaje correctamente.\n");
		i++;
	}
	return 0;
}
