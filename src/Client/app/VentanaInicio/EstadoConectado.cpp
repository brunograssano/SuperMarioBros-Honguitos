#include "EstadoConectado.hpp"
#include <string>
using namespace std;
#include "src/Utils/log/Log.hpp"

#define ANCHO_PANTALLA 650
#define ALTO_PANTALLA 450
const SDL_Color COLOR_BLANCO = {255, 255, 255, 0xFF };

EstadoConectado::EstadoConectado(SDL_Renderer* renderer,SDL_Texture* fondoPantalla,TTF_Font* fuente,BotonConTexto* botonEnviar,BotonConTexto* cajaTextoUsuario,BotonConTexto* cajaTextoContrasenia){
    Log* log = Log::getInstance();
    this->renderer = renderer;
    this->fondoPantalla = fondoPantalla;
    this->fuente = fuente;
    this->texturaTextoUsuario = cargarTexturaTexto("Ingrese usuario:", COLOR_BLANCO, this->renderer, this->fuente);
    this->texturaTextoContrasenia = cargarTexturaTexto("Ingrese contrasenia:", COLOR_BLANCO, this->renderer,
                                                       this->fuente);
    if( this->texturaTextoUsuario == nullptr ){
        log->huboUnError("No se pudo crear la textura para el comando del usuario");
    }
    if( this->texturaTextoContrasenia == nullptr ){
        log->huboUnError("No se pudo crear la textura para el comando de la contraseña");
    }
    this->botonEnviar = botonEnviar;
    this->cajaTextoUsuario = cajaTextoUsuario;
    this->cajaTextoContrasenia = cajaTextoContrasenia;
}

void EstadoConectado::mostrarse(unsigned short jugadoresConectados, unsigned short jugadoresTotales){
    SDL_Texture* texturaCantidadJugadores = cargarTexturaTexto(
            "Conectados " + to_string(jugadoresConectados) + "/" + to_string(jugadoresTotales) + " jugadores",
            COLOR_BLANCO, this->renderer, this->fuente);
    SDL_SetRenderDrawColor( this->renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( this->renderer );

    SDL_Rect rectanguloCamara = {0, 0, ALTO_PANTALLA, ANCHO_PANTALLA};
    SDL_RenderCopy( this->renderer, this->fondoPantalla, &rectanguloCamara, nullptr);

    this->botonEnviar->mostrarse();

    renderizar(380,40,14,200,this->texturaTextoUsuario,renderer);

    this->cajaTextoUsuario->mostrarseCambiandoAncho();

    renderizar(380,120,14,250,this->texturaTextoContrasenia,renderer);

    this->cajaTextoContrasenia->mostrarseCambiandoAncho();

    if(texturaCantidadJugadores != nullptr ){
        renderizar(380,320,14,250,texturaCantidadJugadores,renderer);
    }

    destructorDeTexturas(texturaCantidadJugadores);
}

EstadoConectado::~EstadoConectado() {
    destructorDeTexturas(texturaTextoUsuario);
    destructorDeTexturas(texturaTextoContrasenia);
}
