#ifndef SRC_CLIENT_APP_MANEJADORSDL_HPP_
#define SRC_CLIENT_APP_MANEJADORSDL_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include<string>

void iniciarSDL();

void renderizar(int coordenadaX,int coordenadaY,int alto,int ancho,SDL_Texture* textura,SDL_Renderer* renderer);

SDL_Renderer* crearRenderer(SDL_Window* ventana);

SDL_Window* crearVentana(const char *titulo, int alto, int ancho);

void cargarIcono(SDL_Window* ventana);

TTF_Font* cargarFuente(const std::string& direccion,int tamanio);

SDL_Texture* cargarTexturaTexto(const std::string& texto, SDL_Color color, SDL_Renderer* renderer, TTF_Font* fuente);

SDL_Texture* cargarTexturaImagen(const std::string& direccion, SDL_Renderer* renderizador);

SDL_Texture* intentarCarga(const std::string& descripcion, const std::string& direccion, SDL_Renderer* renderizador);

void destructorDeTexturas(SDL_Texture* textura);

void terminarSDL();

#endif /* SRC_CLIENT_APP_MANEJADORSDL_HPP_ */
