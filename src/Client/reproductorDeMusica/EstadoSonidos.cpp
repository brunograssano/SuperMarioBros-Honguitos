#include "EstadoSonidos.hpp"
#include "ReproductorMusica.hpp"

EstadoSonidos* SuenanSonidos::cambiar(){
    return new SonidosMuteados();
}

void SuenanSonidos::reproducir(string sonidoAReproducir){
    ReproductorMusica::getInstance()->reproducirSonido(sonidoAReproducir);
}

EstadoSonidos* SonidosMuteados::cambiar(){
    return new SuenanSonidos();
}

void SonidosMuteados::reproducir(string sonidoAReproducir){
    // No suena nada
}
