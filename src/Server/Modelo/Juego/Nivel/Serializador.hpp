#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_SERIALIZADOR_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_SERIALIZADOR_HPP


#include <list>
#include "src/Server/Modelo/Juego/Nivel/Piso/Piso.hpp"
#include "src/Server/Modelo/Juego/Nivel/Bloques/Tuberia.hpp"
#include "src/Server/Modelo/Juego/Nivel/Enemigos/Enemigo.hpp"
#include "src/Server/Modelo/Juego/Nivel/Bloques/Bloque.hpp"
#include "Moneda.hpp"

class Serializador {
public:
    void serializar(std::list<Bloque*> plataformas,info_ronda_t *ptrInfoRonda,bool (* deboAgregarlo)(void*, rectangulo_t), void* contexto);
    void serializar(std::list<Enemigo*> enemigos ,info_ronda_t *ptrInfoRonda,bool (* deboAgregarlo)(void*, rectangulo_t), void* contexto);
    void serializar(std::list<Moneda*> monedas ,info_ronda_t *ptrInfoRonda,bool (* deboAgregarlo)(void*, rectangulo_t), void* contexto);
    void serializar(std::list<ObjetoFugaz*> objetosFugaces ,info_ronda_t *ptrInfoRonda,bool (* deboAgregarlo)(void*, rectangulo_t), void* contexto);
    void serializar(std::list<Tuberia*> tuberias,nivel_t *nivel);
    void serializar(std::list<Bloque*> plataformas,nivel_t *nivel);
    void serializar(std::list<entidad_t> pozos,nivel_t *nivel);
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_SERIALIZADOR_HPP
