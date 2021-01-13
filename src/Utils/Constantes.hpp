#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_CONSTANTES_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_CONSTANTES_HPP
#include <string>

const int ANCHO_FONDO = 8177;
#define IZQUIERDA 1
#define DERECHA 2
#define ARRIBA 3
#define ABAJO 4
#define MAX_CONEXIONES 4

#define COLISION_ID_MARIO "Mario"
#define COLISION_ID_KOOPA "Koopa"
#define COLISION_ID_GOOMBA "Goomba"
#define COLISION_ID_MONEDA "Moneda"
#define COLISION_ID_LADRILLO "Ladrillo"
#define COLISION_ID_SORPRESA  "Sorpresa"
#define COLISION_ID_FLOR "Flor"
#define COLISION_ID_MONEDA_FLOTANTE "Moneda flotante"
#define COLISION_ID_BOLA_DE_FUEGO "Nada"
#define COLISION_ID_CHISPA "Nada"
#define COLISION_ID_NADA "Nada"


const int PUNTOS_KOOPA = 1000;
const int PUNTOS_GOOMBA = 500;
const int PUNTOS_POR_MONEDA = 50;

const float PROPORCION_PISO_EN_IMAGEN = 0.1;
const int ALTO_MARIO = 80, ANCHO_MARIO = 40;
const int ALTO_ENEMIGOS = 40, ANCHO_ENEMIGOS = 40;
const int LARGO_BLOQUE = 40;
const int LARGO_MONEDA = 40;
const int ALTO_FLOR = 40, ANCHO_FLOR = 40;
const int ALTO_BOLA = 20, ANCHO_BOLA = 20;
const int ALTO_CHISPA = 44, ANCHO_CHISPA = 64;
const int GOOMBA = 1, KOOPA = 2;

#define CLAVE_TEXTURA_MONEDA "Moneda"
#define CLAVE_TEXTURA_FONDO_INICIO "FondoInicio"
#define CLAVE_TEXTURA_TITULO "Titulo"
#define CLAVE_TEXTURA_GAMEOVER "FondoGameOver"
#define CLAVE_TEXTURA_COFFIN_MARIO "Coffin"
#define CLAVE_TEXTURA_TUBERIAS "Tuberia"
#define CLAVE_TEXTURA_CORAZON "Corazon"
#define CLAVE_TEXTURA_BOLA_DE_FUEGO "BolaDeFuego"
#define CLAVE_TEXTURA_CHISPA "Chispa"
#define CLAVE_TEXTURA_FLOR "Flor"
#define CLAVE_TEXTURA_MONEDA_FLOTANTE "MonedaFlotante"
#define CLAVE_TEXTURA_BLOQUES "Bloques"
#define CLAVE_TEXTURA_GOOMBA "Goombas"
#define CLAVE_TEXTURA_KOOPAS "Koopas"
#define CLAVE_TEXTURA_PEACH_SALTANDO "PeachSaltando"
#define CLAVE_TEXTURA_TOAD_SALTANDO "ToadSaltando"
#define CLAVE_TEXTURA_YOSHI_SALTANDO "YoshiSaltando"

#define MUSICA_VICTORIA "resources/Musica/MusicaVictoria.mp3"
#define MUSICA_GAMEOVER "resources/Musica/CoffinDance8Bits.mp3"
#define MUSICA_INICIO "resources/Musica/MusicaInicio.mp3"
#define MUSICA_NIVEL1 "resources/Musica/TemaNivel1.mp3"

#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_CONSTANTES_HPP
