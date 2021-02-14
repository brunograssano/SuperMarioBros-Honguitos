#ifndef SRC_SERVER_UTILIDADESSERVER_HPP_
#define SRC_SERVER_UTILIDADESSERVER_HPP_

#include <list>
#include "src/Utils/Thread.hpp"
#include "src/Utils/Socket.hpp"
#include "src/Utils/Utils.hpp"


/* *
 * Crea un socket para el servidor, configurandolo con lo necesario para empezar a ejecutar.
 * En caso de fallar se termina el programa.
 */
Socket iniciarSocketServidor(int puerto, char* ip);

void empezarHilo(Thread* hilo,const std::string& nombreHilo);

void escribirMensajesDeArchivoLeidoEnLog(const std::list<std::string>& mensajesError);

bool coincidenCredenciales(const usuario_t &posibleUsuario,const usuario_t &usuario);

#endif /* SRC_SERVER_UTILIDADESSERVER_HPP_ */
