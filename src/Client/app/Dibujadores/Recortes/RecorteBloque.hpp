#ifndef SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEBLOQUE_HPP_
#define SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEBLOQUE_HPP_

#include "Recorte.hpp"
#include <SDL2/SDL.h>

const int COLORES_BLOQUES_POSIBLES = 6, ESTADOS_BLOQUE = 5;

class RecorteBloque : public Recorte{
	public:
	    RecorteBloque();
};


#endif /* SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEBLOQUE_HPP_ */
