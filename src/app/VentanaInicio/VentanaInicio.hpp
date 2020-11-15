#ifndef SRC_APP_VENTANAINICIO_VENTANAINICIO_HPP_
#define SRC_APP_VENTANAINICIO_VENTANAINICIO_HPP_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
using namespace std;

typedef struct credencial{
	string nombre;
	string contrasenia;
}credencial_t;


class VentanaInicio{

	public:
		VentanaInicio();
		void obtenerEntrada();
		credencial_t obtenerCredenciales();
		~VentanaInicio();
	private:
		credencial_t credenciales;
		SDL_Texture* texturaTextoUsuario;
		SDL_Texture* texturaTextoContrasenia;
		SDL_Texture* usuarioIngresado;
		SDL_Texture* contraseniaIngresada;
		TTF_Font* fuente;
		SDL_Window* ventana;
		SDL_Renderer* renderer;
		SDL_Texture* cargoTextura(string textureText, SDL_Color textColor);
		void renderizar(int coordenadaX,int coordenadaY,int ancho,int alto,SDL_Texture* textura);
		bool manejarEntradaUsuario(SDL_Event evento,bool* terminar,string* textoIngresadoUsuario,string* textoIngresadoConstrasenia,string** entradaUsuario);
		void manejarEntradaContrasenia();


};



#endif /* SRC_APP_VENTANAINICIO_VENTANAINICIO_HPP_ */
