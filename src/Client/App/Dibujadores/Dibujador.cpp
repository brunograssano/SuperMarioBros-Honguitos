
#include "src/Client/App/ManejadorSDL.hpp"
#include "Dibujador.hpp"

void Dibujador::renderizarTexto(SDL_Rect renderQuad, std::string textoAMostrar, SDL_Color color) {
    SDL_Rect* clip = nullptr;
    double angle = 0.0;
    SDL_Point* center = nullptr;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    SDL_SetRenderDrawColor(renderizador, colorDefault.r, colorDefault.g, colorDefault.b, colorDefault.a);

    SDL_Texture* texto = cargadorTexturas->cargarFuenteDeTextoATextura(textoAMostrar, renderizador, color);

    SDL_RenderCopyEx( renderizador, texto, clip, &renderQuad, angle, center, flip );
    destructorDeTexturas(texto);
}

