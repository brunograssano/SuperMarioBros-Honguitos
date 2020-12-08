#ifndef SRC_CLIENT_GAMELOOP_HPP_
#define SRC_CLIENT_GAMELOOP_HPP_

#include <SDL2/SDL.h>

#include "../Utils/Utils.hpp"
#include "../Client/Cliente.hpp"
#include "app/AplicacionCliente.hpp"

class GameLoop{

	public:
		GameLoop();
		~GameLoop(){};

		bool inicializarAplicacion(info_partida_t informacion,Cliente* cliente);
		void seMurioElServer();
		void gameLoop();

	private:
		bool salir;

};

#endif /* SRC_CLIENT_GAMELOOP_HPP_ */
