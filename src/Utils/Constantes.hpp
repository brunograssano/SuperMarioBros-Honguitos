#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_CONSTANTES_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_CONSTANTES_HPP
#include <string>

const int ANCHO_FONDO = 8177;
#define VALOR_POR_DEFECTO_ANCHO 800
#define VALOR_POR_DEFECTO_ALTO 600
#define TIEMPO_ESPERA_GAME_LOOP 5
#define IZQUIERDA 1
#define DERECHA 2
#define ARRIBA 3
#define ABAJO 4
#define MAX_CONEXIONES 4
#define SIN_JUGAR (-1)
#define LARGO_IP 20

//=======================================================//
//==================== COLISIONES =======================//
#define COLISION_ID_MARIO "Mario"
#define COLISION_ID_KOOPA "Koopa"
#define COLISION_ID_GOOMBA "Goomba"
#define COLISION_ID_MONEDA "Moneda"
#define COLISION_ID_LADRILLO "Ladrillo"
#define COLISION_ID_SORPRESA  "Sorpresa"
#define COLISION_ID_FLOR "Flor"
#define COLISION_ID_MONEDA_FLOTANTE "Moneda flotante"
#define COLISION_ID_BOLA_DE_FUEGO "Bola de fuego"
#define COLISION_ID_CHISPA "Chispa"
#define COLISION_ID_NADA "Nada"
#define COLISION_ID_PLATAFORMA "Plataforma"
#define COLISION_ID_PIEZA_TUBERIA "Pieza tuberia"


//=======================================================//
//====================== MEDIDAS ========================//
const int PUNTOS_KOOPA = 1000;
const int PUNTOS_GOOMBA = 500;
const int PUNTOS_POR_MONEDA = 50;
const int ANCHO_POZO = 200, ALTO_POZO = 65;
const int ALTO_MARIO = 80, ANCHO_MARIO = 40, ALTO_MARIO_AGACHADO = 55;
const int ALTO_ENEMIGOS = 40, ANCHO_ENEMIGOS = 40;
const int LARGO_BLOQUE = 40;
const int LARGO_MONEDA = 40;
const int ALTO_FLOR = 40, ANCHO_FLOR = 40;
const int ALTO_BOLA = 20, ANCHO_BOLA = 20;
const int ALTO_CHISPA = 44, ANCHO_CHISPA = 64;
const int ALTO_TUBERIA_CHICA = 90, ANCHO_TUBERIA_CHICA = 90;
const int ALTO_TUBERIA_GRANDE = ALTO_TUBERIA_CHICA*2, ANCHO_TUBERIA_GRANDE = ANCHO_TUBERIA_CHICA*2;



const uint8_t SIN_MODIFICADOR = 0, MODIFICADOR_FUEGO = 1;

#define TUBERIA_CHICA 0
#define TUBERIA_GRANDE 1

#define COLORES_BLOQUES_POSIBLES 7
#define ESTADOS_BLOQUE 5
#define ESTADOS_MONEDA 4
#define ESTADOS_GOOMBA 3
#define COLORES_GOOMBA_POSIBLES 4
#define ESTADOS_KOOPA 6
#define COLORES_KOOPA_POSIBLES 5


//=======================================================//
//====================== ENTIDADES ======================//
const uint8_t NADA = 0;
const uint8_t GOOMBA = 1;
const uint8_t KOOPA = 2;
const uint8_t BOLA_DE_FUEGO = 3;
const uint8_t CHISPA = 4;
const uint8_t FLOR = 5;
const uint8_t MONEDA_FLOTANTE = 6;
const uint8_t MONEDA = 7;
const uint8_t BLOQUE = 8;
const uint8_t TUBERIA = 9;
const uint8_t POZO = 10;
const uint8_t FONDO_POZO = 11;
const uint8_t MARIO_RECORTE = 12;

const int ENEMIGOS_RECORTE = 12;
const int EFECTOS_RECORTE = 13;


//=======================================================//
//====================== TEXTURAS =======================//
#define CLAVE_TEXTURA_POZO "Pozo"
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
#define CLAVE_TEXTURA_MARIO_SALTANDO "MarioSaltando"
#define CLAVE_TEXTURA_FONDO_POZO "FondoPozo"


//=======================================================//
//====================== MUSICA =========================//
#define MUSICA_VICTORIA "resources/Musica/MusicaVictoria.mp3"
#define MUSICA_GAMEOVER "resources/Musica/CoffinDance8Bits.mp3"
#define MUSICA_INICIO "resources/Musica/MusicaInicio.mp3"
#define MUSICA_NIVEL1 "resources/Musica/TemaNivel1.mp3"
#define MUSICA_MODO_DIEGO "resources/Musica/LiveisLife.mp3"

//=======================================================//
//====================== SONIDOS ========================//
const uint8_t NO_SONAR = 0;
const uint8_t SONIDO_SALTO = 1;
const uint8_t SONIDO_AGARRAR_MONEDA = 2;
const uint8_t SONIDO_MATAR_GOOMBA = 3;
const uint8_t SONIDO_MATAR_KOOPA = 4;
const uint8_t SONIDO_APARECE_FLOR = 5;
const uint8_t SONIDO_AGARRA_POWERUP = 6;
const uint8_t SONIDO_MORIR = 7;
const uint8_t SONIDO_LANZAR_BOLA_DE_FUEGO = 8;
const uint8_t SONIDO_LANZAR_CHISPA = 9;
const uint8_t SONIDO_REBOTE_BOLA_DE_FUEGO = 10;
const uint8_t SONIDO_EXPLOSION_BOLA_DE_FUEGO = 11;
const uint8_t SONIDO_LLEGAR_A_LA_META = 12;

#define DIRECCION_SONIDO_SALTO "resources/Musica/EfectosSonido/EfectoSalto.wav"
#define DIRECCION_SONIDO_AGARRAR_MONEDA "resources/Musica/EfectosSonido/AgarrarMoneda.wav"
#define DIRECCION_SONIDO_MUERTE_GOOMBA "resources/Musica/EfectosSonido/MarioMataGoomba.wav"
#define DIRECCION_SONIDO_MUERTE_KOOPA "resources/Musica/EfectosSonido/MarioPisaKoopa.wav"
#define DIRECCION_SONIDO_APARECE_PLANTA "resources/Musica/EfectosSonido/AparecePlanta.wav"
#define DIRECCION_SONIDO_MARIO_AGARRA_HONGO "resources/Musica/EfectosSonido/MarioAgarraHongo.wav"
#define DIRECCION_SONIDO_MARIO_MUERE "resources/Musica/EfectosSonido/MarioMorir.wav"
#define DIRECCION_SONIDO_MARIO_LANZA_FUEGO "resources/Musica/EfectosSonido/MarioLanzaFuego.wav"
#define DIRECCION_SONIDO_CHISPA "resources/Musica/EfectosSonido/Chispazo.wav"
#define DIRECCION_SONIDO_REBOTE "resources/Musica/EfectosSonido/ReboteBolaDeFuego.wav"
#define DIRECCION_SONIDO_EXPLOSION "resources/Musica/EfectosSonido/ExplosionBolaDeFuego.wav"
#define DIRECCION_SONIDO_PASAR_NIVEL "resources/Musica/EfectosSonido/PasarDeNivel.wav"

#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_CONSTANTES_HPP
