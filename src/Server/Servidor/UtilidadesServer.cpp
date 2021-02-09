#include <cstdlib>
#include "src/Utils/log/Log.hpp"
#include "UtilidadesServer.hpp"

const int TAMANIO_COLA = 4;

void salir(const std::string& mensajeLog){
	Log* log = Log::getInstance();
    std::cout << "No se pudo iniciar el server, cerrando la aplicacion, mire el log para mas detalles" << std::endl;
	log->huboUnError(mensajeLog);
	delete log;
	exit(EXIT_FAILURE);
}

Socket iniciarSocketServidor(int puerto, char* ip){
    Socket socket;
    try{
        socket = Socket(ip,puerto,TAMANIO_COLA);
    }catch (std::exception& e) {
        salir(e.what());
    }
	return socket;
}

void escribirMensajesDeArchivoLeidoEnLog(const std::list<std::string>& mensajesError){
	Log* log = Log::getInstance();
	for(auto const& mensaje:mensajesError){
		log->huboUnError(mensaje);
	}
}

void empezarHilo(Thread* hilo,const std::string& nombreHilo){
    try{
        hilo->empezarHilo(nombreHilo);
    }catch(const std::exception& e){
        salir("Ocurrio un error creando el hilo "+nombreHilo+", no se va a poder ejecutar el server correctamente. Terminando el servidor");
    }
}

bool coincidenCredenciales(const usuario_t &posibleUsuario,const usuario_t &usuario){
    return posibleUsuario.nombre == usuario.nombre && posibleUsuario.contrasenia == usuario.contrasenia &&
               !usuario.usado;
}