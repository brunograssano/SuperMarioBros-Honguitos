#include "AplicacionCliente.hpp"
#include "../../Client/reproductorDeMusica/ReproductorMusica.hpp"
#include "src/Utils/Constantes.hpp"
#include "ManejadorSDL.hpp"
#include <list>

App* App::aplicacion = nullptr;

App* App::getInstance(info_partida_t informacion, Cliente* cliente){
	if(aplicacion==nullptr){
		aplicacion= new App(informacion,cliente);
	}
	return aplicacion;
}

App* App::getInstance(){
		return aplicacion;
}

void App::manejarClick(SDL_Event eventoClick) {
    this->dibujador.agregarEventoADibujadores(eventoClick);
}

App::App(info_partida_t informacion, Cliente *cliente)
    :dibujador(informacion.direccionesFondoNiveles,informacion.cantidadFondosNiveles,informacion.mundo,
               informacion.anchoVentana,informacion.altoVentana,&juegoCliente),
    juegoCliente(informacion.cantidadJugadores,informacion.jugadores,informacion.idPropio,informacion.anchoVentana,
                                                                                                                                                                                    informacion.altoVentana,informacion.podios, informacion.topePodios, informacion.podioPuntosAcumulados){
    Log* log = Log::getInstance();
    this->cliente = cliente;

    terminoElJuego = false;
    comenzoElJuego = false;
    estaReproduciendoMusicaGanadores = false;
    presionoT = false;

    log->mostrarMensajeDeInfo("Inicio del juego");
    ReproductorMusica::getInstance()->ReproducirMusicaNivel(MUSICA_INICIO);
}

void App::ocurrioUnErrorServidor(){
    dibujador.ocurrioErrorEnServidor();
}

void App::actualizarServer(const Uint8 *keystate){

	if(comenzoElJuego && !terminoElJuego){
		entrada_usuario_t entradaUsuario = {false,false,false,false,false,false};
		bool se_movio = false;
		if(keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_W]){
			entradaUsuario.W = true;
			se_movio = true;
		}

		if(keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_A]){
			entradaUsuario.A = true;
			se_movio = true;
		}

		if(keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_D]){
			entradaUsuario.D = true;
			se_movio = true;
		}

		if((keystate[SDL_SCANCODE_DOWN] || keystate[SDL_SCANCODE_S]) && !se_movio){
			entradaUsuario.S = true;
			se_movio = true;
		}

		if(presionoT){
		    entradaUsuario.T = true;
		    se_movio = true;
            presionoT = false;
		}

		if(keystate[SDL_SCANCODE_SPACE]){
            entradaUsuario.ESP = true;
            se_movio = true;
		}

		if(se_movio){
            cliente->agregarMensajeAEnviar(ENTRADA,&entradaUsuario);
		}
	}
}

void App::agregarRonda(info_ronda_t info_ronda){
	juegoCliente.agregarRonda(info_ronda);
}

void App::actualizar(){
	juegoCliente.actualizar();
    dibujador.determinarEstado();
    determinarMusica();
}

void App::determinarMusica() {
    if(juegoCliente.ganaronElJuego()){
        if(!estaReproduciendoMusicaGanadores){
            ReproductorMusica::getInstance()->ReproducirMusicaNivel(MUSICA_VICTORIA);
            estaReproduciendoMusicaGanadores = true;
        }
        terminoElJuego = true;
    }
    else if(juegoCliente.perdieronElJuego() && !terminoElJuego) {
        ReproductorMusica::getInstance()->ReproducirMusicaNivel(MUSICA_GAMEOVER);
        terminoElJuego = true;
    }
}

void App::dibujar() {
    dibujador.dibujar();
}

void App::agregarNivel(nivel_t nivel) {
    juegoCliente.agregarNivel(nivel);
}

void App::manejarEntrada(SDL_Keycode codigoEntrada) {
    if(codigoEntrada == SDLK_m){
        ReproductorMusica::getInstance()->cambiarMusica();
    }else if(codigoEntrada == SDLK_n){
        ReproductorMusica::getInstance()->cambiarSonidos();
    }else if(codigoEntrada == SDLK_t){
        presionoT = true;
    }else if(!comenzoElJuego && codigoEntrada == SDLK_RETURN){
        comenzoElJuego = true;
        dibujador.comenzoElJuego();
        ReproductorMusica::getInstance()->ReproducirMusicaNivel(MUSICA_NIVEL1);
    }
}

App::~App(){
	Log::getInstance()->mostrarMensajeDeInfo("Se cierra la aplicacion");
}
