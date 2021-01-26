#include "AplicacionServidor.hpp"
#include <unistd.h>
#include <utility>
#include "src/Server/Botonera/Botonera.hpp"
#include "src/Server/Servidor/Servidor.hpp"

AplicacionServidor::AplicacionServidor(Servidor* server,list<Nivel*> niveles,int cantidadJugadores,int ancho_pantalla ,int  alto_pantalla){
	juego = Juego::getInstance(std::move(niveles),cantidadJugadores, alto_pantalla, ancho_pantalla);
    terminoElJuego = false;
	comenzoElJuego = false;
    log = Log::getInstance();
	Botonera::getInstance();
	servidor = server;
}

info_partida_t AplicacionServidor::obtenerInfoPartida(map<int,string> mapaIDNombre,int IDJugador){
	Log::getInstance()->mostrarMensajeDeInfo("Se prepara la informacion de la partida para el jugador: " + mapaIDNombre[IDJugador]);
	return juego->obtenerInfoPartida(mapaIDNombre, IDJugador);
}

info_ronda_t AplicacionServidor::obtenerInfoRonda() {
	Log::getInstance()->mostrarAccion("Se prepara la informacion de la ronda para ejecutar.");
    return juego->obtenerInfoRonda();
}

nivel_t AplicacionServidor::obtenerInfoNivel(){
    return juego->serializarNivel();
}

void AplicacionServidor::iniciarJuego(){
	comenzoElJuego = true;
	despertarHilo();
}

void AplicacionServidor::mandarInfoNivel() {
    nivel_t nivel = juego->serializarNivel();
    servidor->mandarNivelAClientes(nivel);
}

void AplicacionServidor::revisarSiMandarInfoNivel(int* cantidadNivelesRestantes){
    if((*cantidadNivelesRestantes)>juego->cantidadDeNiveles()){
        (*cantidadNivelesRestantes) = juego->cantidadDeNiveles();
        mandarInfoNivel();
    }
}

void AplicacionServidor::ejecutar(){
	int microSegundosEspera = 16666;
	while(!comenzoElJuego){
	    dormirHilo();
	}

	Log::getInstance()->mostrarMensajeDeInfo("Inicia el ciclo del juego en el server");
	auto contador = Contador(microSegundosEspera, USEGUNDOS);
    juego->iniciar();
    int cantidadNivelesRestantes = juego->cantidadDeNiveles();
    mandarInfoNivel();
	while(!terminoElJuego || juego->hayConectados()){
	    contador.iniciar();
		if(!terminoElJuego){

			while(!colaDeEntradasUsuario.empty()){
				entrada_usuario_id_t parIDEntrada = colaDeEntradasUsuario.front();
				juego->actualizarJugador(parIDEntrada.id, parIDEntrada.entradas);
                pthread_mutex_lock(&mutex);
				colaDeEntradasUsuario.pop();
                pthread_mutex_unlock(&mutex);
			}
			juego->actualizarModelo();

			terminoElJuego = juego->ganaron() || juego->perdieron();
		}
		revisarSiMandarInfoNivel(&cantidadNivelesRestantes);
		info_ronda_t ronda = obtenerInfoRonda();
		servidor->guardarRondaParaEnvio(ronda);
        enviarSonidos();

		usleep(contador.tiempoRestante());
	}

	Log::getInstance()->mostrarMensajeDeInfo("Termina el ciclo del juego en el server");
    servidor->terminarElJuego();
}

void AplicacionServidor::encolarEntradaUsuario(entrada_usuario_id_t entradaUsuario){
    pthread_mutex_lock(&mutex);
    this->colaDeEntradasUsuario.push(entradaUsuario);
    pthread_mutex_unlock(&mutex);
}

void AplicacionServidor::activarJugador(int idMarioConectandose){
	juego->conectarJugador(idMarioConectandose);
}

void AplicacionServidor::desconectarJugador(int idJugador){
	juego->desconectarJugador(idJugador);
}

bool AplicacionServidor::empezoElJuego() const {
    return comenzoElJuego;
}

void AplicacionServidor::enviarSonidos() {
    std::map<int, string> jugadores = servidor->obtenerMapaJugadores();
    Botonera *botonera = Botonera::getInstance();
    std::list<sonido_t> sonidoDeTodos = botonera->obtenerSonidosDe(ID_TODOS_DETONANTES);
    for(auto const& parClaveJugador : jugadores){
        std::list<sonido_t> sonidos = botonera->obtenerSonidosDe(parClaveJugador.first);
        sonidos.insert(sonidos.end(), sonidoDeTodos.begin(), sonidoDeTodos.end());
        servidor->enviarSonidosA(parClaveJugador.first, sonidos);
    }
}

AplicacionServidor::~AplicacionServidor(){
    delete Botonera::getInstance();
    delete juego;
}