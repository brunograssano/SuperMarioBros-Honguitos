#include "EstadoMusica.hpp"
#include "ReproductorMusica.hpp"

Suena::Suena(string cancionAReproducir,string cancionQueSeReproduce){
    this->cancionAReproducir = cancionAReproducir;
    this->cancionQueSeReproduce = cancionQueSeReproduce;
}

EstadoMusica* Suena::cambiar() {
    ReproductorMusica::getInstance()->pausarMusica();
    return new Muteada(cancionAReproducir,cancionQueSeReproduce);
}

void Suena::reproducir(string nombreCancion) {
    if ((cancionQueSeReproduce == cancionAReproducir) && (!cancionQueSeReproduce.empty())){
        ReproductorMusica::getInstance()->reanudarMusica();
    }else{
        ReproductorMusica::getInstance()->ponerMusica(nombreCancion);
        ReproductorMusica::getInstance()->reanudarMusica();
        cancionQueSeReproduce = nombreCancion;
    }
}

Muteada::Muteada(string cancionAReproducir,string cancionQueSeReproduce){
    this->cancionAReproducir = cancionAReproducir;
    this->cancionQueSeReproduce = cancionQueSeReproduce;
}

EstadoMusica* Muteada::cambiar() {
    EstadoMusica* nuevoEstado = new Suena(cancionAReproducir,cancionQueSeReproduce);
    nuevoEstado->reproducir(cancionAReproducir);
    return nuevoEstado;
}

void Muteada::reproducir(string nombreCancion) {
    cancionAReproducir = nombreCancion;
}
