#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_FLORDEFUEGO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_FLORDEFUEGO_HPP


#include "src/Server/modelo/Posicion.hpp"
#include "ObjetoSorpresa.hpp"
#include "src/Utils/Utils.hpp"

class FlorDeFuego : public ObjetoSorpresa{

    public:
        FlorDeFuego(int posicionBloque, int altoBloque);
        void usarse(Mario* mario)override;
        efecto_t serializar() override;
        void actualizar() override;
        int obtenerPosicionX() override;
    private:
        Posicion posicionFija;
        SDL_Rect recorte{};
        bool agarraronFlor;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_FLORDEFUEGO_HPP
