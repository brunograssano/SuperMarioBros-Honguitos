#ifndef SRC_CLIENT_APP_VENTANAINICIO_BOTONCONTEXTO_HPP_
#define SRC_CLIENT_APP_VENTANAINICIO_BOTONCONTEXTO_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
using namespace std;

class BotonConTexto
{
    private:

    SDL_Rect rectangulo;
    string texto;
    SDL_Texture* texturaTexto;
    TTF_Font* fuente;
    SDL_Renderer* renderer;
    SDL_Texture* cargoTextura(string texto);

    public:

    BotonConTexto( int posicionX, int posicionY, int ancho, int alto , string texto,SDL_Renderer* renderer,TTF_Font* fuente);

    void cambiarTexto(string texto);

    bool botonClickeado(SDL_Event evento);

    void mostrarse();

    void mostrarseCambiandoAncho( int nuevoAncho);

};

#endif
