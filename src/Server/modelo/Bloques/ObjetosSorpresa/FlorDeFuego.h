#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_FLORDEFUEGO_H
#define TP_TALLER_DE_PROGRAMACION_FIUBA_FLORDEFUEGO_H


#include "src/Server/modelo/Posicion.hpp"
#include "ObjetoSorpresa.hpp"

class FlorDeFuego : public ObjetoSorpresa{

    public:
        FlorDeFuego(int posicionBloque, int altoBloque);
        void usarse(Mario* mario)override;
    private:
        Posicion posicionFija;
        SDL_Rect recorte{};
        bool agarraronFlor;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_FLORDEFUEGO_H
