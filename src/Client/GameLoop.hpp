#ifndef SRC_CLIENT_GAMELOOP_HPP_
#define SRC_CLIENT_GAMELOOP_HPP_

#include "../Utils/Utils.hpp"
#include "../Client/Cliente.hpp"
#include "app/AplicacionCliente.hpp"

class GameLoop{

	public:
		GameLoop();
		~GameLoop();

		static bool inicializarAplicacion(info_partida_t informacion,Cliente* cliente);
		static void seMurioElServer();
		void gameLoop();

	private:
		bool salir;

};

#endif /* SRC_CLIENT_GAMELOOP_HPP_ */
