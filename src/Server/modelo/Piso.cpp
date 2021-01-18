#include "Piso.hpp"
#include "Plataforma.hpp"

#define COMIENZO_PISO 0
#define FIN_PISO 10000

Piso::Piso(int altoPiso) {
    alto = altoPiso;
}

void Piso::agregarPozo(int posicionPozo, int tipoPozo, int fondo) {
    auto pozo = Pozo(posicionPozo, tipoPozo, fondo);
    pozos.push_back(pozo);
}

void Piso::inicializar() {
    int comienzoPlataforma = COMIENZO_PISO;
    for(auto pozo:pozos){
        int comienzoPozo = pozo.obtenerPosicionX();
        if(comienzoPlataforma<comienzoPozo){
            plataformas.push_front(new Plataforma(comienzoPlataforma,comienzoPozo,alto));
        }
        comienzoPlataforma = comienzoPozo + ANCHO_POZO;
    }
    if(comienzoPlataforma<FIN_PISO){
        plataformas.push_front(new Plataforma(comienzoPlataforma,FIN_PISO,alto));
    }
}

list<Colisionable*> Piso::obtenerPiso() {
    return plataformas;
}

list<pozo_t> Piso::serializar() {
    list<pozo_t> pozosSerializados;
    for(auto pozo: pozos){
        pozo_t pozo_serializado = pozo.serializar();
        pozosSerializados.push_back(pozo_serializado);
    }
    return pozosSerializados;
}

Piso::~Piso() {
    for(auto plataforma:plataformas){
        delete plataforma;
    }
}

int Piso::obtenerAltura() const {
    return alto;
}

bool Piso::obtenerXRespawn(rectangulo_t rectanguloEscena, int* x) {
    *x = rectanguloEscena.x1;
    bool encontreAlguna = false;
    for(auto const& plataforma : plataformas){
        rectangulo_t rectanguloActual = plataforma->obtenerRectangulo();
        rectangulo_t interseccion;
        bool hayInterseccion = intersecarRectangulos(rectanguloActual, rectanguloEscena, &interseccion);
        if(hayInterseccion && (interseccion.w >= ANCHO_MARIO)){
            if(encontreAlguna && interseccion.x1  < *x){
                *x = interseccion.x1;
            }else if(!encontreAlguna){
                *x = interseccion.x1;
                encontreAlguna = true;
            }
        }
    }
    return encontreAlguna;
}

bool Piso::obtenerRespawn(rectangulo_t rectanguloEscena, Posicion* posicion){
    int x = 0;
    bool hayPiso = obtenerXRespawn(rectanguloEscena, &x);
    if(hayPiso){
        *posicion = PosicionFija(x, alto);
    }
    return hayPiso;
}