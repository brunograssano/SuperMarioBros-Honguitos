#include "AplicacionCliente.hpp"
#include "../../Client/reproductorDeMusica/ReproductorMusica.hpp"
#include "src/Utils/Constantes.hpp"
#include "ManejadorSDL.hpp"
#include <list>

App* App::aplicacion = nullptr;

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

App::App(info_partida_t informacion, Cliente *cliente) {
    Log* log = Log::getInstance();
    this->cliente = cliente;

    ancho_pantalla = informacion.anchoVentana;
    alto_pantalla = informacion.altoVentana;
    inicializarSDL();

    cargadorTexturas = new CargadorTexturas(renderizador);

    for(int i=0; i<informacion.cantidadFondosNiveles; i++){
        //*Traerme el vector de mundos*// // TODO QUE SIGNIFICABA ESTO?
        this->direccionesNiveles[informacion.mundo+i] = string(informacion.direccionesFondoNiveles[i]);
    }

    cargadorTexturas->cargarTexturasNiveles(direccionesNiveles, renderizador, informacion.mundo);

    rectanguloCamara = { 0, 0, ancho_pantalla , alto_pantalla};

    juegoCliente = new JuegoCliente(informacion.cantidadJugadores,informacion.jugadores,informacion.idPropio,ancho_pantalla);

    sePusoMusicaInicio = false;
    sonoSalto = false;
    terminoElJuego = false;
    comenzoElJuego = false;
    errorServidor = false;
    estaReproduciendoMusicaGanadores = false;

    bool juegoInicializadoCorrectamente = true; // TODO SACAR ESTO
    dibujador = new Dibujadores(cargadorTexturas, renderizador, ancho_pantalla, alto_pantalla,juegoInicializadoCorrectamente);

    log->mostrarMensajeDeInfo("Inicio del juego");

}

void App::inicializarSDL(){
    ventanaAplicacion = crearVentana("Super Mario Bros",alto_pantalla,ancho_pantalla);
    renderizador = crearRenderer(ventanaAplicacion);
    cargarIcono(ventanaAplicacion);
}

void App::ocurrioUnErrorServidor(){
	errorServidor = true;
}

void App::actualizarServer(const Uint8 *keystate){

	if(!sePusoMusicaInicio){
		ReproductorMusica::getInstance()->ReproducirMusicaNivel(MUSICA_INICIO); //TODO: refactorizar a otro método.
		sePusoMusicaInicio = true;
	}

	if(!comenzoElJuego){
		if(keystate[SDL_SCANCODE_RETURN]){
			comenzoElJuego = true;
			ReproductorMusica::getInstance()->ReproducirMusicaNivel(MUSICA_NIVEL1); //TODO: refactorizar a otro método.
		}
	}
	else if(!terminoElJuego){
		entrada_usuario_t entradaUsuario = {false,false,false,false};
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

		if(keystate[SDL_SCANCODE_T]){
		    entradaUsuario.T = true;
		    se_movio = true;
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
	juegoCliente->agregarRonda(info_ronda);
}

void App::actualizar(){
	juegoCliente->actualizar();
    cargadorTexturas->revisarSiCambioNivel(direccionesNiveles[juegoCliente->obtenerMundoActual()]);
}

void App::dibujar(){

	if(this->errorServidor){
		dibujador->dibujarErrorServidor();
	}else if(!comenzoElJuego){
		dibujador->dibujarInicio();
	}else{
		if(juegoCliente->ganaronElJuego()){

			if(!this->estaReproduciendoMusicaGanadores){
				ReproductorMusica::getInstance()->ReproducirMusicaNivel(MUSICA_VICTORIA);
				estaReproduciendoMusicaGanadores = true;
			}
			dibujador->dibujarPantallaGanadores(juegoCliente);
			terminoElJuego = true;
		}
		else if(juegoCliente->perdieronElJuego()){
			if(!terminoElJuego){
				ReproductorMusica::getInstance()->ReproducirMusicaNivel(MUSICA_GAMEOVER);
				terminoElJuego = true;
			}
			dibujador->dibujarGameOver();
		}else if(!terminoElJuego){
			dibujador->dibujarJuego(&rectanguloCamara,juegoCliente);
		}
	}
}

void App::agregarNivel(nivel_t nivel) {
    juegoCliente->agregarNivel(nivel);
    // TODO logica para que se muestren las pantallas intermedias?
}

App::~App(){

	Log::getInstance()->mostrarMensajeDeInfo("Se cierra la aplicacion");

	SDL_DestroyRenderer( renderizador );
	SDL_DestroyWindow( ventanaAplicacion );

	delete dibujador;
	delete cargadorTexturas;
	delete ReproductorMusica::getInstance();
}
