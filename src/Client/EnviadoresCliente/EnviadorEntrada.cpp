
#include "EnviadorEntrada.hpp"

EnviadorEntrada::EnviadorEntrada(int socket){
	this->socket = socket;
}

void EnviadorEntrada::enviar(){
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	entrada_usuario_t entrada;
	memset(&entrada,0,sizeof(entrada_usuario_t));
	if(!entradasUsuario.empty()){
        pthread_mutex_lock(&mutex);
	    entrada = entradasUsuario.front();
		entradasUsuario.pop();
        pthread_mutex_unlock(&mutex);
        Enviador::enviar(ENTRADA,&entrada,sizeof(entrada_usuario_t));
	}

}
void EnviadorEntrada::dejarInformacion(void* informacion){
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&mutex);
	entradasUsuario.push(*((entrada_usuario_t*)informacion));
    pthread_mutex_unlock(&mutex);
}


