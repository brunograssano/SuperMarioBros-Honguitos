#ifndef SRC_SERVER_MODELO_BLOQUES_BLOQUE_HPP_
#define SRC_SERVER_MODELO_BLOQUES_BLOQUE_HPP_

#include <list>
#include <string>
using namespace std;

#include "ObjetosSorpresa/ObjetoSorpresa.h"
#include "ObjetosSorpresa/SinSorpresa.h"

#include "../../../Utils/Utils.hpp"

#include "../PosicionFija.hpp"
#include "../../sprites/Sprite.hpp"
#include "../../sprites/SpriteSorpresa.hpp"
#include "../../sprites/SpriteLadrillo.hpp"

#define SORPRESA 0

class Bloque{
    public:
		virtual ~Bloque()= default;
		int obtenerPosicionX();
		int obtenerPosicionY();
		Sprite* obtenerSprite();
		void ubicarEnPosicionDefault();
		virtual ObjetoSorpresa* colisionaronAbajo();
        virtual bloque_t serializar();

    protected:
        int tipoBloque{};
    	Posicion* posicion{};
    	Sprite* spriteBloque{};
		static int normalizarCoordenadaIngresada(int coordenada);
};

#endif /* SRC_SERVER_MODELO_BLOQUES_BLOQUE_HPP_ */