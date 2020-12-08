#ifndef SRC_SERVER_UTILIDADESSERVER_HPP_
#define SRC_SERVER_UTILIDADESSERVER_HPP_

#include "AplicacionServidor.hpp"
#include "Servidor.hpp"

/* *
 * Crea un socket para el servidor, configurandolo con lo necesario para empezar a escuchar.
 * En caso de fallar se termina el programa.
 */
int iniciarSocketServidor(int puerto, char* ip);

void iniciarJuego(pthread_t* hiloJuego,AplicacionServidor* aplicacionServidor);

void crearHiloConectarJugadores(Servidor* servidor);

void escribirMensajesDeArchivoLeidoEnLog(list<string> mensajesError);

void unirHilosPrincipalYGameLoop(pthread_t* hiloJuego);

void crearHiloReconectarJugadoresFaseInicial(Servidor* servidor);

#endif /* SRC_SERVER_UTILIDADESSERVER_HPP_ */
