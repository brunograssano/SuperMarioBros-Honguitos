#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_MANEJADORDESONIDOMARIO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_MANEJADORDESONIDOMARIO_HPP

#include <string>
#include <map>
#include "src/Server/Modelo/ManejadorDeSonido.hpp"


class ManejadorDeSonidoMario : public ManejadorDeSonido{
    public:
        explicit ManejadorDeSonidoMario(int idMario);
        void desactivarSonidoFlor();
        void activarSonidoFlor();
        void reproducirSonidoMuerte();
        void reproducirSonidoDisparo(int tipo);
        void reproducirSonidoSalto();
        void reproducirSonidoMoneda();
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_MANEJADORDESONIDOMARIO_HPP
