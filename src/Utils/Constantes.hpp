#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_CONSTANTES_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_CONSTANTES_HPP
#include <string>

const int ANCHO_FONDO = 8177;
#define IZQUIERDA 1
#define DERECHA 2
#define ARRIBA 3
#define ABAJO 4
#define MAX_CONEXIONES 4

const std::string COLISION_ID_MARIO = "Mario";
const std::string COLISION_ID_KOOPA = "Koopa";
const std::string COLISION_ID_GOOMBA = "Goomba";
const std::string COLISION_ID_MONEDA = "Moneda";
const std::string COLISION_ID_LADRILLO = "Ladrillo";
const std::string COLISION_ID_SORPRESA = "Sorpresa";
const std::string COLISION_ID_FLOR = "Flor";
const std::string COLISION_ID_MONEDA_FLOTANTE = "Moneda flotante";
const std::string COLISION_ID_BOLA_DE_FUEGO = "Nada";
const std::string COLISION_ID_CHISPA = "Nada";
const std::string COLISION_ID_NADA= "Nada";


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



#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_CONSTANTES_HPP
