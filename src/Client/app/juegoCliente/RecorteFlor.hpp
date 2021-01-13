#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEFLOR_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEFLOR_HPP


#include <src/Client/app/juegoCliente/Recortes/Recorte.hpp>

class RecorteFlor : public Recorte{
    SDL_Rect obtenerRecorte(int recorte) override;
    int obtenerAltura() override;
    int obtenerAnchura() override;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEFLOR_HPP
