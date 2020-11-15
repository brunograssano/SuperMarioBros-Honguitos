
#include "ConexionServidor.hpp"

ConexionServidor::ConexionServidor(int socket,string nombre){
	socketCliente = socket;
	nombreUsuario = nombre;
}

ConexionServidor::~ConexionServidor(){

}




