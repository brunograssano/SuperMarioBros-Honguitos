#ifndef SRC_SERVER_MODELO_BLOQUES_BLOQUE_HPP_
#define SRC_SERVER_MODELO_BLOQUES_BLOQUE_HPP_

#include "src/Server/Modelo/Juego/Serializable.hpp"
#include "src/Server/Modelo/Juego/Actualizable.hpp"
#include "ObjetosSorpresa/ObjetoSorpresa.hpp"
#include "ObjetosSorpresa/SinSorpresa.hpp"
#include "src/Server/Modelo/Juego/Colisionable.hpp"
#include "src/Utils/Utils.hpp"
#include "src/Server/Modelo/Juego/Sprites/SpriteBloque.hpp"

#define SORPRESA 0

class Bloque : public Colisionable, Serializable,Actualizable{
    public:
		~Bloque() override = default;
		void actualizar();
		int obtenerPosicionX();
		int obtenerPosicionY();

        virtual ObjetoSorpresa* colisionaronAbajo();
        virtual entidad_t serializar();
        std::string obtenerColisionID() override = 0;
        rectangulo_t obtenerRectangulo() override;
        bool debeColisionar() override;
        bool cambioElSprite();
        virtual void elevar(int y);

    protected:
        int tipoBloque{};
    	Posicion posicion;
    	SpriteBloque* spriteBloque{};
		static int normalizarCoordenadaIngresada(int coordenada);
        void inicializarMapasDeColision() override = 0;
};

#endif /* SRC_SERVER_MODELO_BLOQUES_BLOQUE_HPP_ */