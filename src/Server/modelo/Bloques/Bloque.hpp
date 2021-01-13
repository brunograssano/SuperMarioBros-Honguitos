#ifndef SRC_SERVER_MODELO_BLOQUES_BLOQUE_HPP_
#define SRC_SERVER_MODELO_BLOQUES_BLOQUE_HPP_

#include <list>
#include <string>
using namespace std;

#include "ObjetosSorpresa/ObjetoSorpresa.hpp"
#include "ObjetosSorpresa/SinSorpresa.hpp"
#include "src/Server/modelo/Colisionable.hpp"

#include "../../../Utils/Utils.hpp"

#include "../PosicionFija.hpp"
#include "../../sprites/Sprite.hpp"
#include "../../sprites/SpriteSorpresa.hpp"
#include "../../sprites/SpriteLadrillo.hpp"

#define SORPRESA 0

class Bloque : public Colisionable{
    public:
		virtual ~Bloque()= default;
		int obtenerPosicionX();
		int obtenerPosicionY();
		Sprite* obtenerSprite();
		void ubicarEnPosicionDefault();
		virtual ObjetoSorpresa* colisionaronAbajo();
        virtual bloque_t serializar();
        string obtenerColisionID() override = 0;
        rectangulo_t obtenerRectangulo() override;
        bool debeColisionar() override;


protected:
        int tipoBloque{};
    	Posicion* posicion{};
    	Sprite* spriteBloque{};
		static int normalizarCoordenadaIngresada(int coordenada);
        void inicializarMapasDeColision() override = 0;
};

#endif /* SRC_SERVER_MODELO_BLOQUES_BLOQUE_HPP_ */