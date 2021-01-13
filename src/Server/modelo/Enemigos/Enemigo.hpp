#ifndef SRC_SERVER_MODELO_ENEMIGOS_ENEMIGO_HPP_
#define SRC_SERVER_MODELO_ENEMIGOS_ENEMIGO_HPP_

#include "../PosicionMovil.hpp"
#include <string>
#include "../../sprites/SpriteEnemigo.hpp"
#include "src/Utils/Utils.hpp"
class Mario;

#include "src/Server/modelo/Colisionable.hpp"


class Enemigo : public Colisionable{

	public:
        virtual ~Enemigo()= default;
        virtual enemigo_t serializar() =0 ;
        void morir(void* ptr = nullptr);
		int obtenerPosicionX();
		int obtenerPosicionY();
		virtual void agregarPosicion(int coordenadaX,int coordenadaY);
		virtual void actualizarPosicion();
        virtual bool sePuedeEliminar();
        string obtenerColisionID() override = 0;
        rectangulo_t obtenerRectangulo() override;
        bool debeColisionar() override;
        bool estaMuerto() const;

    protected:
        void cambiarOrientacion(void* ptr = nullptr);
        static float obtenerVelocidad();
        enemigo_t serializarEnemigo(int tipo);
		PosicionMovil* posicionActual{};
        SpriteEnemigo* spriteEnemigo{};
        float velocidadX{};
        int tipoColor{};
        void inicializarMapasDeColision() override;
        bool loMataron = false;
};


#endif /* SRC_SERVER_MODELO_ENEMIGOS_ENEMIGO_HPP_ */
