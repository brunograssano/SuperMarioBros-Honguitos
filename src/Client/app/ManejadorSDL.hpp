#ifndef SRC_CLIENT_APP_MANEJADORSDL_HPP_
#define SRC_CLIENT_APP_MANEJADORSDL_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

void iniciarSDL();
void destructorDeTexturas(SDL_Texture* textura);
void terminarSDL();

#endif /* SRC_CLIENT_APP_MANEJADORSDL_HPP_ */
