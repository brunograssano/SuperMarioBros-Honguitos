#ifndef SRC_APP_VENTANAINICIO_VENTANAINICIO_HPP_
#define SRC_APP_VENTANAINICIO_VENTANAINICIO_HPP_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
using namespace std;

typedef struct credenciales{
	string nombre;
	string contrasenia;
}credenciales_t;


class VentanaInicio{

	public:
		VentanaInicio();
		void obtenerEntrada(unsigned short jugadoresConectados, unsigned short jugadoresTotales);
		void imprimirMensajeError();
		void imprimirMensajeEspera(unsigned short cantJugadoresConectados, unsigned short cantJugadoresTotales);
		credenciales_t obtenerCredenciales();
		~VentanaInicio();
	private:
		bool ingresoIncorrectoCredenciales;
		credenciales_t credenciales;
		SDL_Texture* texturaTextoUsuario;
		SDL_Texture* texturaTextoContrasenia;
		SDL_Texture* usuarioIngresado;
		SDL_Texture* contraseniaIngresada;
		SDL_Texture* texturaCantidadJugadores;
		SDL_Texture* texturaMensajeCredencialesIncorrectas;
		SDL_Texture* texturaMensajeCredencialesCorrectas;
		TTF_Font* fuente;
		SDL_Window* ventana;
		SDL_Renderer* renderer;
		SDL_Texture* cargoTextura(string textureText, SDL_Color textColor);
		void renderizar(int coordenadaX,int coordenadaY,int ancho,int alto,SDL_Texture* textura);
		bool manejarEntradaUsuario(SDL_Event evento,bool* terminar,string* textoIngresadoUsuario,string* textoIngresadoConstrasenia,string** entradaUsuario);
		void manejarEntradaContrasenia();


};



#endif /* SRC_APP_VENTANAINICIO_VENTANAINICIO_HPP_ */
