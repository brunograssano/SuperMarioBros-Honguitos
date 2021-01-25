#include "EstadoDesconectado.hpp"
#define ANCHO_PANTALLA 650
#define ALTO_PANTALLA 450
const SDL_Color COLOR_NEGRO = { 0, 0, 0, 0xFF };

EstadoDesconectado::EstadoDesconectado(SDL_Renderer* renderer,TTF_Font* fuente) {
    this->renderer = renderer;
    this->fuente = fuente;
}

void EstadoDesconectado::mostrarse(unsigned short jugadoresConectados, unsigned short jugadoresTotales){
    SDL_RenderClear( this->renderer );

    SDL_Texture* texturaMensaje = cargarTexturaTexto("Ocurrio un error en la conexion con el Servidor.", COLOR_NEGRO,
                                                     this->renderer, this->fuente);
    SDL_Texture* texturaMensajeInfo = cargarTexturaTexto("Revise su archivo log en la carpeta \"/logs/\".", COLOR_NEGRO,
                                                         this->renderer, this->fuente);

    renderizar(20,ALTO_PANTALLA/2-80,40,ANCHO_PANTALLA-50, texturaMensaje, renderer);
    renderizar(20,ALTO_PANTALLA/2,40,ANCHO_PANTALLA-50, texturaMensajeInfo, renderer);
    destructorDeTexturas(texturaMensaje);
    destructorDeTexturas(texturaMensajeInfo);
}


