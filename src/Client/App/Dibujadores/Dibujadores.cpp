#include "Dibujadores.hpp"
#include "DibujadoresFinales/DibujadorGameOver.hpp"
#include "DibujadoresJuego/DibujadorInicio.hpp"
#include "DibujadoresFinales/DibujadorGanadores.hpp"
#include "DibujadoresJuego/DibujadorJuego.hpp"
#include "DibujadoresError/DibujadorErrorServidor.hpp"
#include "DibujadoresFinales/DibujadorFinNivel.hpp"

#define DIBUJADOR_INICIO "Inicio"
#define DIBUJADOR_ERROR_SERVER "ErrorServer"
#define DIBUJADOR_JUEGO "Juego"
#define DIBUJADOR_GAMEOVER "GameOver"
#define DIBUJADOR_GANARON "Ganaron"
#define DIBUJADOR_PUNTOS_NIVEL "PuntosNivel"

Dibujadores::Dibujadores(char direccionesFondoNiveles[MAX_CANT_NIVELES][MAX_LARGO_NOMBRE_NIVEL],unsigned short cantidadFondosNiveles,
                         unsigned short mundo,unsigned short  anchoPantalla,unsigned short  altoPantalla,JuegoCliente *juegoCliente) {
    ventanaAplicacion = crearVentana("Super Mario Bros",altoPantalla,anchoPantalla);
    renderizador = crearRenderer(ventanaAplicacion);
    cargarIcono(ventanaAplicacion);
    for(int i=0; i<cantidadFondosNiveles; i++){
        direccionesNiveles[mundo+i] = string(direccionesFondoNiveles[i]);
    }
    this->cargadorTexturas = new CargadorTexturas(renderizador);
    this->cargadorTexturas->cargarTexturasNiveles(direccionesNiveles,renderizador,mundo);
    this->juegoCliente = juegoCliente;

    estadoActual = DIBUJADOR_INICIO;
    dibujadores[DIBUJADOR_INICIO] = new DibujadorInicio(cargadorTexturas, renderizador, anchoPantalla, altoPantalla);
    dibujadores[DIBUJADOR_ERROR_SERVER] = new DibujadorErrorServidor(cargadorTexturas, renderizador, anchoPantalla, altoPantalla);
    dibujadores[DIBUJADOR_JUEGO] = new DibujadorJuego(cargadorTexturas, renderizador, anchoPantalla, altoPantalla,juegoCliente);
    dibujadores[DIBUJADOR_GAMEOVER] = new DibujadorGameOver(cargadorTexturas, renderizador, anchoPantalla, altoPantalla,juegoCliente);
    dibujadores[DIBUJADOR_GANARON] = new DibujadorGanadores(cargadorTexturas, renderizador, anchoPantalla, altoPantalla,juegoCliente);
    dibujadores[DIBUJADOR_PUNTOS_NIVEL] = new DibujadorFinNivel(cargadorTexturas, renderizador, anchoPantalla, altoPantalla,juegoCliente);
}

void Dibujadores::dibujar(){
    dibujadores[estadoActual]->dibujar();
}

void Dibujadores::comenzoElJuego() {
    estadoActual = DIBUJADOR_JUEGO;
}

void Dibujadores::ocurrioErrorEnServidor() {
    estadoActual = DIBUJADOR_ERROR_SERVER;
}

void Dibujadores::agregarEventoADibujadores(SDL_Event eventoClick){
    dibujadores[estadoActual]->agregarEventoDeClick(eventoClick);
}

void Dibujadores::determinarEstado() {
    cargadorTexturas->revisarSiCambioNivel(direccionesNiveles[juegoCliente->obtenerMundoActual()]);
    if(juegoCliente->ganaronElJuego()){
        estadoActual = DIBUJADOR_GANARON;
    }else if(juegoCliente->perdieronElJuego()){
        estadoActual = DIBUJADOR_GAMEOVER;
    }else if(juegoCliente->hayQueMostrarPuntosDeNivel){
        estadoActual = DIBUJADOR_PUNTOS_NIVEL;
    }else if(estadoActual!=DIBUJADOR_ERROR_SERVER && estadoActual!=DIBUJADOR_INICIO){
        estadoActual = DIBUJADOR_JUEGO;
    }
}

Dibujadores::~Dibujadores(){
	for(const auto& parClaveDibujador:dibujadores){
	    delete parClaveDibujador.second;
	}
	delete cargadorTexturas;
    SDL_DestroyRenderer( renderizador );
    SDL_DestroyWindow( ventanaAplicacion );
}
