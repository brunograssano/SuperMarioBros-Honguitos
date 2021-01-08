#include "SpriteBolaDeFuego.hpp"

SpriteBolaDeFuego::SpriteBolaDeFuego(){
    this->direccionTextura = "resources/Imagenes/Objetos/BolaDeFuego.png";
    this->ciclos = 0;
    this->estadoActual = 0;
}
void SpriteBolaDeFuego::actualizarSprite() {

}

SDL_Rect SpriteBolaDeFuego::obtenerRectanguloActual() {
    return {0,0,0,0};
}