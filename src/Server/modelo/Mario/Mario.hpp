#ifndef SRC_SERVER_MODELO_MARIO_HPP_
#define SRC_SERVER_MODELO_MARIO_HPP_


#include "src/Server/modelo/Posicion.hpp"
#include "src/Utils/log/Log.hpp"
#include "src/Utils/Utils.hpp"

#include "MovimientoMario.hpp"
#include "VidaMario.hpp"
#include "Modificadores/ModificadorMario.hpp"
#include "Modificadores/SinModificador.hpp"
#include "Modificadores/MarioDeFuego.hpp"

class SpriteMario;

#include "src/Server/modelo/Objetos/ObjetoFugaz.hpp"
#include "src/Server/modelo/Objetos/BolaDeFuego.hpp"
#include "src/Server/modelo/Objetos/Chispa.hpp"

#include "src/Server/modelo/Colisionable.hpp"
#include "ManejadorDeSonidoMario.hpp"

const int ID_DEFAULT = 0;

class Mario : public Colisionable {

	public:
		explicit Mario(int numeroJugador);
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

		bool estaVivo();
        bool puedeAgarrarFlor();
        void perderVida(void* ptr = nullptr);
        int obtenerVida();
        void hacerseDeFuego();
        ObjetoFugaz* dispararFuego();

		jugador_t serializar(const char nombreJugador[MAX_NOMBRE], unsigned short idImagen);
		void desconectar();
		void conectar();
		void serArrastrado(int corrimiento);
		void actualizarMaximoX(int limite);
		void actualizarMinimoX(int limite);

        rectangulo_t obtenerRectangulo() override;
        string obtenerColisionID() override;
        bool debeColisionar() override;

        void chocarPorDerechaCon(Colisionable* colisionable) override;
        void chocarPorIzquierdaCon(Colisionable* colisionable) override;
        void chocarPorArribaCon(Colisionable* colisionable) override;
        void chocarPorAbajoCon(Colisionable* colisionable) override;

        void alternarModoTest();
        void nuevoPuntoDeReaparicion(Posicion puntoDeReaparicion);
        int obtenerID();
        ~Mario() override;

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

        PosicionFija posicionDeReaparicion = PosicionFija(0,0);
		PosicionMovil* posicion;
		MovimientoMario* movimiento;
		SpriteMario * spriteMario;
		ModificadorMario* modificador;
		VidaMario* vidaMario;
        ManejadorDeSonidoMario manejadorSonido = ManejadorDeSonidoMario(ID_DEFAULT);
        int ticksInmunidad;
		int puntos;
		int numeroJugador;
		bool estaConectadoElJugador;
        bool agarreUnaFlorEnEsteInstante;
        bool estaEnModoTest;
};

#endif // SRC_SERVER_MODELO_MARIO_HPP_