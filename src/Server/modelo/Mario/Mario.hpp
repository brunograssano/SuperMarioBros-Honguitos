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

#include "src/Server/modelo/Colisionable.hpp"

class Mario : public Colisionable {

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

        void perderVida(void );
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

        rectangulo_t obtenerRectangulo() override;
        string obtenerColisionID() override;

		~Mario();

private:
        void inicializarMapasDeColision() override;
        void swapDeModificador(ModificadorMario *nuevoModificador);
        void impulsar();
		PosicionMovil* posicion;
		MovimientoMario* movimiento;
		SpriteMario * spriteMario;
		ModificadorMario* modificador;
		VidaMario* vidaMario;
		int puntos;
		int numeroJugador;
		bool estaConectadoElJugador;

};


#endif // SRC_SERVER_MODELO_MARIO_HPP_
