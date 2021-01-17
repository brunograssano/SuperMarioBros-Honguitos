#include "Utils.hpp"
#include "Constantes.hpp"

bool esUnSonidoValido(sonido_t sonido){
    uint8_t  tipo = sonido.tipoSonido;
    return (tipo == SONIDO_SALTO                    ||
            tipo == SONIDO_AGARRAR_MONEDA           ||
            tipo == SONIDO_MATAR_GOOMBA             ||
            tipo == SONIDO_MATAR_KOOPA              ||
            tipo == SONIDO_APARECE_FLOR             ||
            tipo == SONIDO_AGARRA_POWERUP           ||
            tipo == SONIDO_MORIR                    ||
            tipo == SONIDO_LANZAR_BOLA_DE_FUEGO     ||
            tipo == SONIDO_LANZAR_CHISPA            ||
            tipo == SONIDO_REBOTE_BOLA_DE_FUEGO     ||
            tipo == SONIDO_EXPLOSION_BOLA_DE_FUEGO);
}
