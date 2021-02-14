#include "EstadoMusica.hpp"
#include "ReproductorMusica.hpp"

Suena::Suena(std::string cancionAReproducir,std::string cancionQueSeReproduce){
    this->cancionAReproducir = cancionAReproducir;
    this->cancionQueSeReproduce = cancionQueSeReproduce;
}

EstadoMusica* Suena::cambiar() {
    ReproductorMusica::getInstance()->pausarMusica();
    return new Muteada(cancionAReproducir,cancionQueSeReproduce);
}

void Suena::reproducir(std::string nombreCancion) {
    cancionAReproducir = nombreCancion;
    if ((cancionQueSeReproduce == cancionAReproducir) && (!cancionQueSeReproduce.empty())){
        ReproductorMusica::getInstance()->reanudarMusica();
    }else{
        ReproductorMusica::getInstance()->ponerMusica(nombreCancion);
        ReproductorMusica::getInstance()->reanudarMusica();
        cancionQueSeReproduce = nombreCancion;
    }
}

Muteada::Muteada(std::string cancionAReproducir,std::string cancionQueSeReproduce){
    this->cancionAReproducir = cancionAReproducir;
    this->cancionQueSeReproduce = cancionQueSeReproduce;
}

EstadoMusica* Muteada::cambiar() {
    EstadoMusica* nuevoEstado = new Suena(cancionAReproducir,cancionQueSeReproduce);
    nuevoEstado->reproducir(cancionAReproducir);
    return nuevoEstado;
}

void Muteada::reproducir(std::string nombreCancion) {
    cancionAReproducir = nombreCancion;
}
