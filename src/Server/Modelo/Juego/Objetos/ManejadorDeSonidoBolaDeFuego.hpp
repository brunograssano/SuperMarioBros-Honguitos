#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_MANEJADORDESONIDOBOLADEFUEGO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_MANEJADORDESONIDOBOLADEFUEGO_HPP

#include "src/Server/Modelo/ManejadorDeSonido.hpp"

class ManejadorDeSonidoBolaDeFuego : public ManejadorDeSonido {
    public:
        explicit ManejadorDeSonidoBolaDeFuego(int idMario);
        void reproducirExplosion();
        void reproducirRebote();
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_MANEJADORDESONIDOBOLADEFUEGO_HPP
