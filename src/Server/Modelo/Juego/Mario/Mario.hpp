#ifndef SRC_SERVER_MODELO_MARIO_HPP_
#define SRC_SERVER_MODELO_MARIO_HPP_

#include "MovimientoMario.hpp"
#include "ManejadorDeSonidoMario.hpp"
#include "Modificadores/MarioDeFuego.hpp"
class SpriteMario;
#include "src/Utils/Observable.hpp"
#include "src/Utils/Utils.hpp"
#include "src/Utils/log/Log.hpp"

class Mario: public Colisionable, public Observable{

	public:
		explicit Mario(int numeroJugador);
		int obtenerPuntos() const;
		void agregarPuntos(int unosPuntos);
		void agregarMoneda();

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

		bool estaVivo();
        bool puedeAgarrarFlor();
        void perderVida(void* ptr = nullptr);
        int obtenerVida();
        void hacerseDeFuego();
        int obtenerNumeroJugador() const;
        ObjetoFugaz* dispararFuego();

		mario_t serializar(unsigned short idImagen);
		void desconectar();
		void conectar();
		void serArrastrado(int corrimiento);
		void actualizarMaximoX(int limite);
		void actualizarMinimoX(int limite);

        rectangulo_t obtenerRectangulo() override;
        std::string obtenerColisionID() override;
        bool debeColisionar() override;

        void chocarPorDerechaCon(Colisionable* colisionable) override;
        void chocarPorIzquierdaCon(Colisionable* colisionable) override;
        void chocarPorArribaCon(Colisionable* colisionable) override;
        void chocarPorAbajoCon(Colisionable* colisionable) override;

        void alternarModoTest();
        void nuevoPuntoDeReaparicion(Posicion puntoDeReaparicion);
        int obtenerID();
        ~Mario() override;

    int8_t obtenerEstadoActual();

private:
        void empujarEnX(rectangulo_t rectanguloBloque,int direccion);
        void empujarEnY(rectangulo_t rectanguloBloque,int direccion);
        void hacerseDeFuego(void* pVoid);
        void inicializarMapasDeColision() override;
        void inicializarMapaMorirPorEnemigos();
        void desactivarMapaColisionesEnemigos();
        void agregarPuntos(void* puntos = nullptr);
        void swapDeModificador(ModificadorMario *nuevoModificador);
        void matarEnemigo(void* puntos = nullptr);

        PosicionFija posicionDeReaparicion;
		PosicionMovil* posicion;
		MovimientoMario* movimiento;
		SpriteMario * spriteMario;
		ModificadorMario* modificador;
		VidaMario* vidaMario;
        ManejadorDeSonidoMario manejadorSonido;
        int ticksInmunidad;
		int puntos;
		int numeroJugador;
		bool estaConectadoElJugador;
        bool agarreUnaFlorEnEsteInstante;
        bool estaEnModoTest;
};

#endif // SRC_SERVER_MODELO_MARIO_HPP_