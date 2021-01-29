#ifndef SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEMONEDA_HPP_
#define SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEMONEDA_HPP_

#include <SDL2/SDL.h>
#include "Recorte.hpp"

class RecorteMoneda : public Recorte{
	public:
		RecorteMoneda();
        int obtenerAnchuraParaDibujarImagen(int recorteX, int recorteY) override;
        int obtenerAlturaParaDibujarImagen(int recorteX, int recorteY) override;
};



#endif /* SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEMONEDA_HPP_ */
