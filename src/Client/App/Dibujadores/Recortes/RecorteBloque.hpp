#ifndef SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEBLOQUE_HPP_
#define SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEBLOQUE_HPP_

#include "Recorte.hpp"
#include <SDL2/SDL.h>

class RecorteBloque : public Recorte{
	public:
	    RecorteBloque();
        int obtenerAnchuraParaDibujarImagen(int tipo) override;
        int obtenerAlturaParaDibujarImagen(int tipo) override;
};


#endif /* SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEBLOQUE_HPP_ */
