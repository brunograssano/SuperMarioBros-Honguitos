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
        virtual void morir();
		int obtenerPosicionX();
		int obtenerPosicionY();
		virtual void agregarPosicion(int coordenadaX,int coordenadaY);
		virtual void actualizarPosicion();
        virtual bool sePuedeEliminar();
        string obtenerColisionID() override = 0;
        rectangulo_t obtenerRectangulo() override;

	protected:
        static float obtenerVelocidad(){
            return (0.15 + ((rand() % 11) / 100)) * pow(-1,rand()%2);
        }
        enemigo_t serializarEnemigo(int tipo);
		PosicionMovil* posicionActual{};
        SpriteEnemigo* spriteEnemigo{};
        float velocidadX{};
        int tipoColor{};
        int puntos;
        void inicializarMapasDeColision() override = 0;

};


#endif /* SRC_SERVER_MODELO_ENEMIGOS_ENEMIGO_HPP_ */
