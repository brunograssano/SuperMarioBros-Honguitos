#include "AplicacionCliente.hpp"

#include <list>

App* App::aplicacion = nullptr;
const int SE_TERMINO_EL_TIEMPO = 0;
const int ALTO_VENTANA_MINIMO = 600,ANCHO_VENTANA_MINIMO = 800;

#define LIMITE_SALTO 1

App* App::getInstance(info_partida_t informacion, Cliente* cliente){
	if(aplicacion==nullptr){
		aplicacion= new App(informacion,cliente);
	}
	return aplicacion;
}

App* App::getInstance(){
		return aplicacion;
}

void App::inicializarSDL(Log* log){
	ventanaAplicacion = SDL_CreateWindow( "Super Mario Bros", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ancho_pantalla, alto_pantalla, SDL_WINDOW_SHOWN );
	if( ventanaAplicacion == NULL ){
		log->huboUnErrorSDL("No se pudo crear una ventana de SDL", SDL_GetError());
	}

	renderizador = SDL_CreateRenderer( ventanaAplicacion, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	if( renderizador == NULL ){
		log->huboUnErrorSDL("No se pudo crear un renderizador de SDL", SDL_GetError());
	}

    cargarIcono(ventanaAplicacion);
}

void App::ocurrioUnErrorServidor(){
	errorServidor = true;
}

void App::actualizarServer(const Uint8 *keystate){

	if(!sePusoMusicaInicio){
		ReproductorMusica::getInstance()->ReproducirMusicaNivel("resources/Musica/MusicaInicio.mp3"); //TODO: refactorizar a otro método.
		sePusoMusicaInicio = true;
	}

	if(!comenzoElJuego){
		if(keystate[SDL_SCANCODE_RETURN]){
			comenzoElJuego = true;
			ReproductorMusica::getInstance()->ReproducirMusicaNivel("resources/Musica/TemaNivel1.mp3"); //TODO: refactorizar a otro método.
		}
	}
	else if(!terminoElJuego){
		entrada_usuario_t entradaUsuario = {false,false,false,false};
		bool se_movio = false;
		if(keystate[SDL_SCANCODE_SPACE] || keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_W]){
			entradaUsuario.W = true;
			se_movio = true;

			int idPropio = juegoCliente->obtenerIDPropio(); // QUIZAS CONVIENE MOVERLO A ALGO QUE NOS DIGA EL SERVER SI HAY DESFASE
			map<int,jugador_t> jugadores = juegoCliente->obtenerJugadores();
			float posYJugador = jugadores[idPropio].mario.posY;
			if(posYJugador<=LIMITE_SALTO && !sonoSalto){
				ReproductorMusica::getInstance()->ReproducirSonidoSalto();
				sonoSalto = true;
			}
			else if(posYJugador>LIMITE_SALTO){
				sonoSalto = false;
			}
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

		if(se_movio){
            cliente->agregarMensajeAEnviar(ENTRADA,&entradaUsuario);
		}
	}
}

void App::agregarRonda(info_ronda_t info_ronda){
	juegoCliente->agregarRonda(info_ronda);
}

void App::actualizar(){
	juegoCliente->actualizar();
	cargadorTexturas->revisarSiCambioNivel(renderizador, direccionesNiveles[juegoCliente->obtenerMundoActual()]);
}

void App::dibujar(){

	if(this->errorServidor){
		dibujador->dibujarErrorServidor();
	}else if(!comenzoElJuego){
		dibujador->dibujarInicio();
	}else{
		if(juegoCliente->ganaronElJuego()){

			if(!this->estaReproduciendoMusicaGanadores){
				ReproductorMusica::getInstance()->ReproducirMusicaNivel("resources/Musica/MusicaVictoria.mp3");
				estaReproduciendoMusicaGanadores = true;
			}
			dibujador->dibujarPantallaGanadores(juegoCliente);
			terminoElJuego = true;
		}
		else if(juegoCliente->perdieronElJuego()){
			if(!terminoElJuego){
				ReproductorMusica::getInstance()->ReproducirMusicaNivel("resources/Musica/CoffinDance8Bits.mp3");
				terminoElJuego = true;
			}
			dibujador->dibujarGameOver();
		}else if(!terminoElJuego){
			dibujador->dibujarJuego(&rectanguloCamara,juegoCliente);
		}
	}
}

App::~App(){

	Log::getInstance()->mostrarMensajeDeInfo("Se cierra la aplicacion");

	SDL_DestroyRenderer( renderizador );
	SDL_DestroyWindow( ventanaAplicacion );

	delete dibujador;
	delete cargadorTexturas;
	delete ReproductorMusica::getInstance();
}
