#ifndef SRC_APP_VENTANAINICIO_VENTANAINICIO_HPP_
#define SRC_APP_VENTANAINICIO_VENTANAINICIO_HPP_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
using namespace std;

class VentanaInicio{

public:
	VentanaInicio();
	void ObtenerEntrada();
	~VentanaInicio();
private:
	SDL_Texture* texturaTextoUsuario;
	SDL_Texture* texturaTextoContrasenia;
	SDL_Texture* usuarioIngresado;
	SDL_Texture* contraseniaIngresada;
	TTF_Font* fuente;
	SDL_Window* ventana;
	SDL_Renderer* renderer;
	SDL_Texture* cargoTextura(string textureText, SDL_Color textColor);
	void Renderizar(int coordenadaX,int coordenadaY,int ancho,int alto,SDL_Texture* textura);
};



#endif /* SRC_APP_VENTANAINICIO_VENTANAINICIO_HPP_ */
