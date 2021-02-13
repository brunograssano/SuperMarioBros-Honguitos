

#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEMARIOSALTANDO_HPP_
#define TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEMARIOSALTANDO_HPP_


#include "../Recorte.hpp"
#include <SDL2/SDL.h>
class RecorteMarioSaltando: public Recorte{

public:
    RecorteMarioSaltando();
    void actualizarSprite()override;
    SDL_Rect obtenerRecorte(int recorte)override;

private:
    int estadoActual;
    int ciclos;

};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_RECORTEMARIOSALTANDO_HPP_
