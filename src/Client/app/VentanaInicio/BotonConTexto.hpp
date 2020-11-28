#ifndef SRC_CLIENT_APP_VENTANAINICIO_BOTONCONTEXTO_HPP_
#define SRC_CLIENT_APP_VENTANAINICIO_BOTONCONTEXTO_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class BotonConTexto
{
    private:

    SDL_Rect rectangulo;

    SDL_Texture* texto;

    public:

    BotonConTexto( int posicionX, int posicionY, int ancho, int alto , SDL_Texture* texto);

    void cambiarTexto(SDL_Texture* texto);

    bool botonClickeado(SDL_Event evento);

    void mostrarse(SDL_Renderer* renderer);

    void mostrarseCambiandoAncho(SDL_Renderer* renderer, int nuevoAncho);

};

#endif
