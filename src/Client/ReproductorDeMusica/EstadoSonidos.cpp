#include "EstadoSonidos.hpp"

EstadoSonidos* SuenanSonidos::cambiar(){
    return new SonidosMuteados();
}

void SuenanSonidos::reproducir(Mix_Chunk* efecto){
    Mix_PlayChannel( -1, efecto, 0 );
}

EstadoSonidos* SonidosMuteados::cambiar(){
    return new SuenanSonidos();
}

void SonidosMuteados::reproducir(Mix_Chunk* efecto){
    // No suena nada
}
