#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ESTADODESCONECTADO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ESTADODESCONECTADO_HPP


#include "EstadoVentana.hpp"
#include <SDL.h>
#include "../ManejadorSDL.hpp"

class EstadoDesconectado : public EstadoVentana {
    public:
        EstadoDesconectado(SDL_Renderer* renderer,TTF_Font* fuente);
        void mostrarse(unsigned short jugadoresConectados, unsigned short jugadoresTotales) override;

    private:
        SDL_Renderer* renderer;
        TTF_Font* fuente;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ESTADODESCONECTADO_HPP
