#ifndef SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEBLOQUE_HPP_
#define SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEBLOQUE_HPP_

#include "Recorte.hpp"
#include <SDL2/SDL.h>

class RecorteBloque : public Recorte{
	public:
	    RecorteBloque();
        int obtenerAnchuraParaDibujarImagen(int recorteX, int recorteY) override;
        int obtenerAlturaParaDibujarImagen(int recorteX, int recorteY) override;
};


#endif /* SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEBLOQUE_HPP_ */
