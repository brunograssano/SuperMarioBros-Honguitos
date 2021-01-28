#ifndef SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEKOOPA_HPP_
#define SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEKOOPA_HPP_
#include <SDL2/SDL.h>
#include "Recorte.hpp"

class RecorteKoopa : public Recorte{

	public:
		RecorteKoopa();
        int obtenerAnchuraParaDibujarImagen(int tipo) override;
        int obtenerAlturaParaDibujarImagen(int tipo) override;
};




#endif /* SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEKOOPA_HPP_ */
