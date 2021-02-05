#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_TUBERIA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_TUBERIA_HPP

#include <src/Server/Modelo/Juego/Serializable.hpp>
#include "src/Server/Modelo/Juego/Posiciones/Posicion.hpp"
#include "PiezaDeTuberia.hpp"

class Tuberia: public Serializable{

    public:
        Tuberia(int posicionX, int tipo, int color);
        bool colisionaCon(Tuberia *otraTuberia);
        unsigned short obtenerPosicionX() const;
        void elevar(int y);
        entidad_t serializar();
        std::list<PiezaDeTuberia*> obtenerPiezas();
    private:
        void crearColisionables(int x, int tipo);
        std::list<PiezaDeTuberia*> piezas;
        Posicion posicion;
        uint8_t tipo;
        uint8_t color;

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_TUBERIA_HPP
