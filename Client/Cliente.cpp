#include "Cliente.hpp"


Cliente::Cliente(char ip[LARGO_IP], int puerto){
	struct sockaddr_in serv_addr;
	socketCliente = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socketCliente < 0){
		fprintf(stderr, "\n No se pudo crear el socket: Abortamos.\n");
		exit(-1);
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(puerto);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, ip, &serv_addr.sin_addr)<=0){
		fprintf(stderr, "\nDirección inválida / Dirección no soportada: Abortamos.\n");
		exit(-1);
	}
	int res = connect(socketCliente, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if (res < 0){
		fprintf(stderr, "\nFalló la conexión: Abortamos.\n");
		fprintf(stderr, "\tError:%i\n", errno);
		exit(-1);
	}
}


int Cliente::_Read4Bytes(char* buffer){
    int bytesRead = 0;
    int result;
    memset(buffer, 0, 5);
    while (bytesRead < 4){
        result = recv(socketCliente, buffer, 4, MSG_DONTWAIT);
        if (result < 1 ){
            return bytesRead;
        }
        bytesRead += result;
    }
    return bytesRead;
}

void Cliente::escuchar(){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	while(true){
		string mensaje;
		char buffer[5] = "";
		while(_Read4Bytes(buffer) > 0){
			if(!(strlen(buffer) == 0)){
				mensaje = mensaje + (string) buffer;
			}
		}
		if(mensaje.length() != 0){
			pthread_mutex_lock(&mutex);
			cout << "Se recibió el mensaje: " + mensaje << endl;
			pthread_mutex_unlock(&mutex);
		}
	}
}


void Cliente::enviar(){
	int i = 0;
	while(i < 5){
		char msg[100 /*TODO: a cte*/] = "";
		scanf(" %[^\n]", msg);
		send(socketCliente, msg, strlen(msg), 0);
		i++;
	}
}

Cliente::~Cliente(){
	close(socketCliente);
}
