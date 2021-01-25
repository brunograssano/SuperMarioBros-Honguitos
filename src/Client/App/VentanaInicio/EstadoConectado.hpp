
#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_ESTADOCONECTADO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_ESTADOCONECTADO_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include "EstadoVentana.hpp"
#include "../ManejadorSDL.hpp"
#include "BotonConTexto.hpp"

class EstadoConectado: public EstadoVentana {
    public:
        EstadoConectado(SDL_Renderer* renderer,SDL_Texture* fondoPantalla,TTF_Font* fuente,BotonConTexto* botonEnviar,BotonConTexto* cajaTextoUsuario,BotonConTexto* cajaTextoContrasenia);
        void mostrarse(unsigned short jugadoresConectados, unsigned short jugadoresTotales) override;
        ~EstadoConectado() override;

    private:
        SDL_Renderer* renderer;
        SDL_Texture* fondoPantalla;
        TTF_Font* fuente;
        SDL_Texture* texturaTextoUsuario = nullptr;
        SDL_Texture* texturaTextoContrasenia = nullptr;
        BotonConTexto* botonEnviar;
        BotonConTexto* cajaTextoUsuario;
        BotonConTexto* cajaTextoContrasenia;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_ESTADOCONECTADO_HPP
