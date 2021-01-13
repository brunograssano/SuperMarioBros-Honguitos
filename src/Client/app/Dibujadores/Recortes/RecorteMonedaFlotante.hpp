#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEMONEDAFLOTANTE_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEMONEDAFLOTANTE_HPP


#include "Recorte.hpp"

class RecorteMonedaFlotante : public Recorte{
    static const int CANTIDAD_DE_RECORTES = 4;
    public:
        RecorteMonedaFlotante();
        SDL_Rect obtenerRecorte(int recorte) override;
        int obtenerAltura() override;
        int obtenerAnchura() override;
    private:
        SDL_Rect estadosPosibles[CANTIDAD_DE_RECORTES]{};
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEMONEDAFLOTANTE_HPP
