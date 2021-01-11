#ifndef SRC_SERVER_UTILIDADESSERVER_HPP_
#define SRC_SERVER_UTILIDADESSERVER_HPP_

#include <list>
#include "src/Utils/Utils.hpp"
#include "src/Utils/Thread.hpp"
class AceptadorDeConexiones;
class Servidor;

/* *
 * Crea un socket para el servidor, configurandolo con lo necesario para empezar a ejecutar.
 * En caso de fallar se termina el programa.
 */
int iniciarSocketServidor(int puerto, char* ip);

void empezarHilo(Thread* hilo,const string& nombreHilo);

void escribirMensajesDeArchivoLeidoEnLog(const list<string>& mensajesError);

bool coincidenCredenciales(const usuario_t &posibleUsuario,const usuario_t &usuario);

void cerrarServidor(int socketServer);

#endif /* SRC_SERVER_UTILIDADESSERVER_HPP_ */
