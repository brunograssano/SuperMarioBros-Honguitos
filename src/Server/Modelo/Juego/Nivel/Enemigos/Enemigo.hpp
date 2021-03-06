#ifndef SRC_SERVER_MODELO_ENEMIGOS_ENEMIGO_HPP_
#define SRC_SERVER_MODELO_ENEMIGOS_ENEMIGO_HPP_

#include <src/Server/Modelo/Juego/Serializable.hpp>
#include "src/Server/Modelo/Juego/Posiciones/PosicionMovil.hpp"
#include "src/Server/Modelo/Juego/Colisionable.hpp"
#include "src/Server/Modelo/Juego/Sprites/SpriteEnemigo.hpp"
#include "src/Utils/Utils.hpp"
class Mario;
#include "MovimientoEnemigo.hpp"
#define VELOCIDAD_EXTRA_DEFAULT 0.0

class Enemigo : public Colisionable,Serializable{

	public:
        ~Enemigo() override = default;
        virtual entidad_t serializar() = 0;
        void morir(void* ptr = nullptr);
		int obtenerPosicionX();
		int obtenerPosicionY();
		virtual void agregarPosicion(int coordenadaX,int coordenadaY);
		virtual void actualizarPosicion(rectangulo_t rectangulo);
        virtual bool sePuedeEliminar();
        std::string obtenerColisionID() override = 0;
        rectangulo_t obtenerRectangulo() override;
        void chocarPorDerechaCon(Colisionable *colisionable) override;
        void chocarPorIzquierdaCon(Colisionable *colisionable) override;
        void chocarPorAbajoCon(Colisionable* colisionable) override;
        bool debeColisionar() override;
        bool estaMuerto() const;

    protected:
        void empujarEnY(rectangulo_t rectanguloBloque, int direccion);
        void empujarEnX(rectangulo_t rectanguloBloque, int direccion);
        void inicializarMapasDeColision() override;
        void cambiarOrientacion();
        entidad_t serializarEnemigo(int tipo);
		PosicionMovil posicionActual = PosicionMovil(0,0);
        SpriteEnemigo* spriteEnemigo{};
        MovimientoEnemigo movimientoEnemigo = MovimientoEnemigo(VELOCIDAD_EXTRA_DEFAULT);
        int tipoColor{};
        bool loMataron = false;
        bool pisoBloque = false;
};


#endif /* SRC_SERVER_MODELO_ENEMIGOS_ENEMIGO_HPP_ */
