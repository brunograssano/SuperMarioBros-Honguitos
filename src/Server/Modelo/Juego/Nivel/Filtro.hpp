#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_FILTRO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_FILTRO_HPP

#include <list>
#include "src/Server/Modelo/Juego/Colisionable.hpp"
#include "src/Server/Modelo/Juego/Nivel/Bloques/Tuberia.hpp"
#include "src/Server/Modelo/Juego/Nivel/Bloques/Bloque.hpp"
#include "src/Server/Modelo/Juego/Nivel/Enemigos/Enemigo.hpp"
#include "src/Server/Modelo/Juego/Nivel/Moneda.hpp"


class Filtro {
    public:
        Filtro() = default;
        ~Filtro() = default;

        static std::list<Colisionable *> filtrarEnemigosEnEscena(const std::list<Enemigo *>& enemigos, rectangulo_t rectanguloEscena);
        static std::list<Colisionable *> filtrarMonedasEnEscena(const std::list<Moneda *>& monedas, rectangulo_t rectanguloEscena);
        static std::list<Colisionable *> filtrarBloquesEnEscena(const std::list<Bloque *>& bloques, rectangulo_t rectanguloEscena);
        static std::list<Colisionable *> filtrarObjetosEnEscena(const std::list<ObjetoFugaz *>& objetos, rectangulo_t rectanguloEscena);
        static std::list<Colisionable *> filtrarPiezasDeTuberiaEnEscena(const std::list<Tuberia *>& tuberias, rectangulo_t rectanguloEscena);
        static std::list<Colisionable *> filtrarPlataformasEnEscena(const list<Colisionable *>& plataformas, rectangulo_t rectanguloEscena);
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_FILTRO_HPP
