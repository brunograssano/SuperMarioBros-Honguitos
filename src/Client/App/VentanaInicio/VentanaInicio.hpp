#ifndef SRC_CLIENT_APP_VENTANAINICIO_VENTANAINICIO_HPP_
#define SRC_CLIENT_APP_VENTANAINICIO_VENTANAINICIO_HPP_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "BotonConTexto.hpp"
#include "src/Utils/Utils.hpp"
#include "EstadoVentana.hpp"

using namespace std;

class VentanaInicio{

	public:
		VentanaInicio(unsigned short jugadoresConectados, unsigned short jugadoresTotales);
		void obtenerEntrada();
		void imprimirMensajeError();
		void imprimirMensajeEspera();
		void actualizarJugadores(actualizacion_cantidad_jugadores_t actualizacion);
		void seMurioElServer();
		credencial_t obtenerCredenciales();
		~VentanaInicio();
	private:

        EstadoVentana* estadoVentana;
		bool ingresoIncorrectoCredenciales;
		string errorDeIngreso;
    bool murioElServer;

		unsigned short jugadoresTotales;
		unsigned short jugadoresConectados;

		actualizacion_cantidad_jugadores_t informacionJugadoresConectados{};
		credencial_t credenciales{};


		SDL_Texture* fondoPantalla = nullptr;

		TTF_Font* fuente;
		SDL_Window* ventana;
		SDL_Renderer* renderer;

		BotonConTexto* botonEnviar;
		BotonConTexto* cajaTextoUsuario;
		BotonConTexto* cajaTextoContrasenia;

		bool estaConectado(const string& nombre);
        void imprimirErrorIngreso();
		void ponerLosMarios();
		SDL_Texture* texturasMarios;

};



#endif /* SRC_CLIENT_APP_VENTANAINICIO_VENTANAINICIO_HPP_ */
