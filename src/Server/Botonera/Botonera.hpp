#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_BOTONERA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_BOTONERA_HPP

#include <map>
#include <list>
#include "src/Utils/Utils.hpp"

#define ID_TODOS_DETONANTES (-2)

class Botonera {
    public:
        static Botonera* getInstance();
        ~Botonera() = default;

        /* Inscribe que el detonante activo el sonido asociado a la claveSonidos */
        void agregarSonido(uint8_t claveSonido, int idDetonante);

        /*
         * Devuelve los sonidos activados entre llamados a este método.
         * Realiza un clear de la lista
         */
        std::list<sonido_t> obtenerSonidosDe(int idDetonante);

    private:
        static Botonera* botonera;
        explicit Botonera() = default;
        std::map<int, std::list<sonido_t>> sonidos;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_BOTONERA_HPP
