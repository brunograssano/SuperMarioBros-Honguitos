
#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_COLISIONADOR_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_COLISIONADOR_HPP

class Colisionable;
#include "src/Utils/Utils.hpp"

#define SIN_CHOQUE 0
#define PRIMERO_DERECHA_SEGUNDO_IZQUIERDA 1
#define PRIMERO_IZQUIERDA_SEGUNDO_DERECHA 2
#define PRIMERO_ARRIBA_SEGUNDO_ABAJO 3
#define PRIMERO_ABAJO_SEGUNDO_ARRIBA 4

void chocar(Colisionable* colisionable1, Colisionable* colisionable2);
int tipoDeChoque(rectangulo_t rectangulo1, rectangulo_t rectangulo2);
bool esUnBloque(string idColisionable);

#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_COLISIONADOR_HPP
