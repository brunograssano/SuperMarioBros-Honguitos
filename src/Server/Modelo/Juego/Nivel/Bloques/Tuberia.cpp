#include "Tuberia.hpp"
#include "src/Utils/Constantes.hpp"
#include "src/Server/Modelo/Juego/Posiciones/PosicionFija.hpp"

#define PIXEL_DESFASE 2

Tuberia::Tuberia(int posX, int tipo, int color) {
    posicion = PosicionFija(posX, 0);
    this->tipo = tipo;
    this->color = color;
    crearColisionables(posX, tipo);
}

void Tuberia::crearColisionables(int x, int tipoDeTuberia) {
    if(tipoDeTuberia == TUBERIA_CHICA){
        piezas.push_back(new PiezaDeTuberia(x, 0, ANCHO_TUBERIA_CHICA, ALTO_TUBERIA_CHICA));
    }else{
        piezas.push_back(new PiezaDeTuberia(x, 0, ANCHO_TUBERIA_CHICA, ALTO_TUBERIA_CHICA - PIXEL_DESFASE));
        piezas.push_back(new PiezaDeTuberia(x + ANCHO_TUBERIA_CHICA, 0, ANCHO_TUBERIA_CHICA - 2*PIXEL_DESFASE, ALTO_TUBERIA_GRANDE));
    }
}

bool Tuberia::colisionaCon(Tuberia *otraTuberia) {
    std::list<PiezaDeTuberia*> piezasOtraTuberia = otraTuberia->obtenerPiezas();
    bool colisionoUnaPieza = false;
    for(auto const& pieza : piezas){
        for(auto const& otraPieza : piezasOtraTuberia){
            colisionoUnaPieza = colisionoUnaPieza || colisionan(pieza->obtenerRectangulo(), otraPieza->obtenerRectangulo());
        }
    }
    return colisionoUnaPieza;
}

unsigned short Tuberia::obtenerPosicionX() const {
    return posicion.obtenerPosX();
}

entidad_t Tuberia::serializar(){
    return Serializable::serializar(posicion.obtenerPosX(), posicion.obtenerPosY(), tipo, color, TUBERIA, false);
}

void Tuberia::elevar(int y) {
    posicion = PosicionFija(posicion.obtenerPosX(), posicion.obtenerPosY() + y);
    for(auto& pieza: piezas){
        pieza->elevar(y);
    }
}

std::list<PiezaDeTuberia *> Tuberia::obtenerPiezas() {
    return piezas;
}
