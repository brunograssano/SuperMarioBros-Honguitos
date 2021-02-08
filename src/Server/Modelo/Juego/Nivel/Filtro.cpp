#include "Filtro.hpp"

std::list<Colisionable *> Filtro::filtrarEnemigosEnEscena(const std::list<Enemigo *>& enemigos, rectangulo_t rectanguloEscena) {
    std::list<Colisionable*> listaRetorno;
    rectanguloEscena.x2 += RANGO_EXTRA_ENEMIGOS;
    rectanguloEscena.w += RANGO_EXTRA_ENEMIGOS;
    for(auto const& enemigo : enemigos){
        rectangulo_t rectanguloEnemigo = enemigo->obtenerRectangulo();
        if(colisionan(rectanguloEscena, rectanguloEnemigo)){
            listaRetorno.push_back(enemigo);
        }
    }
    return listaRetorno;
}

std::list<Colisionable *> Filtro::filtrarMonedasEnEscena(const std::list<Moneda *>& monedas, const rectangulo_t rectanguloEscena) {
    std::list<Colisionable*> listaRetorno;
    for(auto const& moneda : monedas){
        rectangulo_t rectanguloMoneda = moneda->obtenerRectangulo();
        if(colisionan(rectanguloEscena, rectanguloMoneda)){
            listaRetorno.push_back(moneda);
        }
    }
    return listaRetorno;
}

std::list<Colisionable *> Filtro::filtrarBloquesEnEscena(const std::list<Bloque *>& bloques, rectangulo_t rectanguloEscena) {
    std::list<Colisionable*> listaRetorno;
    for(auto const& bloque : bloques){
        rectangulo_t rectanguloBloque = bloque->obtenerRectangulo();
        if(colisionan(rectanguloEscena, rectanguloBloque)){
            listaRetorno.push_back(bloque);
        }
    }
    return listaRetorno;
}

std::list<Colisionable *> Filtro::filtrarObjetosEnEscena(const std::list<ObjetoFugaz *>& objetos, const rectangulo_t rectanguloEscena) {
    std::list<Colisionable*> listaRetorno;
    for(auto const& objeto : objetos){
        rectangulo_t rectanguloObjeto = objeto->obtenerRectangulo();
        if(colisionan(rectanguloEscena, rectanguloObjeto)){
            listaRetorno.push_back(objeto);
        }
    }
    return listaRetorno;
}

std::list<Colisionable *> Filtro::filtrarPiezasDeTuberiaEnEscena(const std::list<Tuberia *>& tuberias, rectangulo_t rectanguloEscena) {
    std::list<Colisionable*> listaRetorno;
    for(auto const& tuberia : tuberias){
        std::list<PiezaDeTuberia*> piezas = tuberia->obtenerPiezas();
        for(auto const& pieza : piezas){
            rectangulo_t rectanguloPieza = pieza->obtenerRectangulo();
            if(colisionan(rectanguloEscena, rectanguloPieza)){
                listaRetorno.push_back(pieza);
            }
        }
    }
    return listaRetorno;
}

std::list<Colisionable *> Filtro::filtrarPlataformasEnEscena(const std::list<Colisionable *>& plataformas, rectangulo_t rectanguloEscena) {
    std::list<Colisionable*> listaRetorno;
    for(auto const& plataforma : plataformas){
        rectangulo_t rectanguloPlataforma = plataforma->obtenerRectangulo();
        if(colisionan(rectanguloEscena, rectanguloPlataforma)){
            listaRetorno.push_back(plataforma);
        }
    }
    return listaRetorno;
}
