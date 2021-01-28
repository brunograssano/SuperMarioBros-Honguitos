#ifndef SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEMONEDA_HPP_
#define SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEMONEDA_HPP_

#include <SDL2/SDL.h>
#include "Recorte.hpp"

class RecorteMoneda : public Recorte{
	public:
		RecorteMoneda();
        int obtenerAnchuraParaDibujarImagen(int tipo) override;
        int obtenerAlturaParaDibujarImagen(int tipo) override;
};



#endif /* SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEMONEDA_HPP_ */
