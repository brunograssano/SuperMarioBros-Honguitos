#ifndef SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEGOOMBA_HPP_
#define SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEGOOMBA_HPP_

#include <SDL2/SDL.h>
#include "Recorte.hpp"

class RecorteGoomba : public Recorte{
	public:
		RecorteGoomba();
        int obtenerAnchuraParaDibujarImagen(int tipo) override;
        int obtenerAlturaParaDibujarImagen(int tipo) override;
};



#endif /* SRC_CLIENT_APP_JUEGOCLIENTE_RECORTEGOOMBA_HPP_ */
