#ifndef SRC_CLIENT_APP_MANEJADORSDL_HPP_
#define SRC_CLIENT_APP_MANEJADORSDL_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
using namespace std;
#include<string>

void iniciarSDL();

void renderizar(int coordenadaX,int coordenadaY,int alto,int ancho,SDL_Texture* textura,SDL_Renderer* renderer);

SDL_Renderer* crearRenderer(SDL_Window* ventana);

SDL_Window* crearVentana(const char *titulo, int alto, int ancho);

void cargarIcono(SDL_Window* ventana);

SDL_Texture* cargoTextura(const string& texto, SDL_Color color,SDL_Renderer* renderer,TTF_Font* fuente);

void destructorDeTexturas(SDL_Texture* textura);

void terminarSDL();

#endif /* SRC_CLIENT_APP_MANEJADORSDL_HPP_ */
