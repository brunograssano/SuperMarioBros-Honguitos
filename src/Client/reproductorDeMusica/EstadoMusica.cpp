#include "EstadoMusica.hpp"
#include "ReproductorMusica.hpp"

EstadoMusica* Suena::cambiar() {
    ReproductorMusica::getInstance()->pausarMusica();
    return new Muteada();
}

void Suena::reproducir(string nombreCancion) {
    ReproductorMusica::getInstance()->ponerMusica(nombreCancion);
}

EstadoMusica* Muteada::cambiar() {
    ReproductorMusica::getInstance()->reanudarMusica();
    return new Suena();
}

void Muteada::reproducir(string nombreCancion) {
    // No se reproduce nada
}
