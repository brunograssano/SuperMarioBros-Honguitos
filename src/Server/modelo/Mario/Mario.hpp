#ifndef SRC_SERVER_MODELO_MARIO_HPP_
#define SRC_SERVER_MODELO_MARIO_HPP_


#include "src/Server/modelo/Posicion.hpp"
#include "src/Utils/log/Log.hpp"
#include "src/Utils/Utils.hpp"

#include "MovimientoMario.hpp"
#include "VidaMario.h"
#include "Modificadores/ModificadorMario.hpp"
#include "Modificadores/SinModificador.hpp"
#include "Modificadores/MarioDeFuego.hpp"

class SpriteMario;
#include "src/Server/sprites/SpriteMario.hpp"

#include "src/Server/modelo/Objetos/Disparo.hpp"
#include "src/Server/modelo/Objetos/BolaDeFuego.hpp"
#include "src/Server/modelo/Objetos/Chispa.hpp"

class Mario{

	public:

		Mario(int numeroJugador);
		int obtenerPuntos() const;
		void agregarPuntos(int unosPuntos);
		void agregarMoneda();

		SpriteMario* obtenerSpite();
		int obtenerPosicionX();
		int obtenerPosicionY();
		bool estaConectado() const;
		bool estaQuietoX();
		bool estaEnElPiso();
		void actualizarPosicion();
		void reiniciarPosicion();
		
		void actualizarSaltarMario();
		void actualizarAgacharseMario();
		void actualizarIzquierdaMario();
		void actualizarDerechaMario();

        void perderVida();
        int obtenerVida();
        void hacerseDeFuego();
        Disparo* dispararFuego();

		jugador_t serializar(const char nombreJugador[MAX_NOMBRE], unsigned short idImagen);
		void desconectar(){
			estaConectadoElJugador = false;
		}
		void conectar(){
			estaConectadoElJugador = true;
		}
		void serArrastrado(int corrimiento);
		void actualizarMaximoX(int limite);
		void actualizarMinimoX(int limite);
		~Mario();

    private:
        void swapDeModificador(ModificadorMario *nuevoModificador);
		PosicionMovil* posicion;
		MovimientoMario* movimiento;
		SpriteMario * spriteMario;
		ModificadorMario* modificador;
		VidaMario* vidaMario;
		int puntos;
		int numeroJugador;
		bool estaConectadoElJugador;

		//todo: sólo para probar, cambiarlo por un Contador*
        int ciclos = 0;
};


#endif // SRC_SERVER_MODELO_MARIO_HPP_
