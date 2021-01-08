#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ESTADOESPERA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ESTADOESPERA_HPP


#include <SDL_ttf.h>
#include <SDL.h>
#include "EstadoVentana.hpp"
#include "../ManejadorSDL.hpp"

class EstadoEspera : public EstadoVentana {
    public:
        EstadoEspera(SDL_Renderer* renderer,SDL_Texture* fondoPantalla,TTF_Font* fuente);
        void mostrarse(unsigned short jugadoresConectados, unsigned short jugadoresTotales) override;
    private:
        SDL_Renderer* renderer;
        SDL_Texture* fondoPantalla;
        TTF_Font* fuente;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ESTADOESPERA_HPP
