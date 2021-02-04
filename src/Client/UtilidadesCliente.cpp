#include "UtilidadesCliente.hpp"

#include <iostream>
#include <string>
#include <cstdlib>

#include "src/Utils/log/Log.hpp"

void salirCliente(const std::string& mensajeLog){
    std::cout<< "No se pudo conectar al server, terminamos la aplicacion"<<std::endl;
	Log::getInstance()->huboUnError(mensajeLog);
	exit(-1);
}

Socket conectarAlServidor(char ip[LARGO_IP], int puerto){
    Socket socket;
    try{
        socket = Socket(ip,puerto);
    }catch(std::exception& e){
        salirCliente(e.what());
    }
    return socket;
}
