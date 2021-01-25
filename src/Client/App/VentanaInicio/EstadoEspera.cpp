
#include "src/Utils/log/Log.hpp"
#include "EstadoEspera.hpp"
#define ANCHO_PANTALLA 650
#define ALTO_PANTALLA 450
const SDL_Color COLOR_VERDE = { 1, 152, 117, 0xFF };
const SDL_Color COLOR_BLANCO = {255, 255, 255, 0xFF };

EstadoEspera::EstadoEspera(SDL_Renderer* renderer,SDL_Texture* fondoPantalla,TTF_Font* fuente){
    this->renderer = renderer;
    this->fondoPantalla = fondoPantalla;
    this->fuente = fuente;
}

void EstadoEspera::mostrarse(unsigned short jugadoresConectados, unsigned short jugadoresTotales) {
    Log* log = Log::getInstance();

    SDL_RenderClear( this->renderer );

    SDL_Rect rectanguloCamara = {0, 0, ALTO_PANTALLA, ANCHO_PANTALLA};
    SDL_RenderCopy( this->renderer, this->fondoPantalla, &rectanguloCamara, nullptr);

    SDL_Texture* texturaMensajeCredencialesCorrectas = cargarTexturaTexto("Credenciales correctas", COLOR_VERDE,
                                                                          this->renderer, this->fuente);
    if(texturaMensajeCredencialesCorrectas == nullptr ){
        log->huboUnError("No se pudo crear la textura para el mensaje de credenciales correctas");
    }else{
        renderizar(375,150,14,250,texturaMensajeCredencialesCorrectas,renderer);
    }
    destructorDeTexturas(texturaMensajeCredencialesCorrectas);

    SDL_Texture* texturaMensajeEspera = cargarTexturaTexto("Esperando al resto de jugadores", COLOR_VERDE,
                                                           this->renderer, this->fuente);
    if(texturaMensajeEspera == nullptr ){
        log->huboUnError("No se pudo crear la textura para el mensaje de credenciales correctas");
    }else{
        renderizar(375,180,14,250,texturaMensajeEspera,renderer);
    }
    destructorDeTexturas(texturaMensajeEspera);

    SDL_Texture* texturaCantidadJugadores = cargarTexturaTexto(
            "Conectados " + to_string(jugadoresConectados) + "/" + to_string(jugadoresTotales) + " jugadores",
            COLOR_BLANCO, this->renderer, this->fuente);
    if(texturaCantidadJugadores != nullptr ){
        renderizar(380,320,14,250,texturaCantidadJugadores,renderer);
    }
    destructorDeTexturas(texturaCantidadJugadores);
}
