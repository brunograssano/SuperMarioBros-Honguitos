#ifndef SRC_CLIENT_APP_VENTANAINICIO_VENTANAINICIO_HPP_
#define SRC_CLIENT_APP_VENTANAINICIO_VENTANAINICIO_HPP_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "BotonConTexto.hpp"
#include "../../../Utils/Utils.hpp"

using namespace std;

class VentanaInicio{

	public:
		VentanaInicio(unsigned short jugadoresConectados, unsigned short jugadoresTotales);
		void obtenerEntrada();
		void imprimirMensajeError();
		void imprimirMensajeEspera();
		void actualizarJugadores(actualizacion_cantidad_jugadores_t actualizacion);
		credencial_t obtenerCredenciales();
		~VentanaInicio();
	private:
		bool ingresoIncorrectoCredenciales;
		bool salaLlena;
		unsigned short jugadoresTotales;
		unsigned short jugadoresConectados;
		actualizacion_cantidad_jugadores_t informacionJugadoresConectados;
		credencial_t credenciales;
		SDL_Texture* texturaTextoUsuario = nullptr;
		SDL_Texture* texturaTextoContrasenia = nullptr;
		SDL_Texture* usuarioIngresado = nullptr;
		SDL_Texture* contraseniaIngresada = nullptr;
		SDL_Texture* texturaCantidadJugadores = nullptr;
		SDL_Texture* texturaMensajeCredencialesIncorrectas = nullptr;
		SDL_Texture* texturaMensajeCredencialesCorrectas = nullptr;
		SDL_Texture* texturaMensajeEspera = nullptr;
		SDL_Texture* texturaMensajeSalaLlena = nullptr;
		SDL_Texture* textoBotonEnviar = nullptr;
		SDL_Texture* fondoPantalla = nullptr;
		TTF_Font* fuente;
		SDL_Window* ventana;
		SDL_Renderer* renderer;
		BotonConTexto* botonEnviar;
		BotonConTexto* cajaTextoUsuario;
		BotonConTexto* cajaTextoContrasenia;
		SDL_Texture* cargoTextura(string textureText, SDL_Color textColor);
		void ponerLosMarios();
		void renderizar(int coordenadaX,int coordenadaY,int ancho,int alto,SDL_Texture* textura);
		bool manejarEntradaUsuario(SDL_Event evento,bool* terminar,string* textoIngresadoUsuario,string* textoIngresadoConstrasenia,string** entradaUsuario);
		void manejarEntradaContrasenia();

		SDL_Texture* texturasMarios;

		SDL_Texture* cargarTextura(std::string direccion, SDL_Renderer* renderizador);
		SDL_Texture* intentarCarga(std::string descripcion, std::string direccion, SDL_Renderer* renderizador);


};



#endif /* SRC_CLIENT_APP_VENTANAINICIO_VENTANAINICIO_HPP_ */
