#ifndef SRC_APP_SPRITEMARIO_H_
#define SRC_APP_SPRITEMARIO_H_

class Mario;
#include "Sprite.hpp"
#include "src/Server/Modelo/Juego/Mario/Mario.hpp"
#include "src/Utils/Constantes.hpp"


class SpriteMario : public Sprite{

	public:
		SpriteMario();
		void actualizarSprite()override{};
		void actualizarSprite(Mario* mario);
        void actualizarSpriteMarioDerecha (Mario* mario);
		void actualizarSpriteMarioIzquierda(Mario* mario);
		void actualizarSpriteMarioSaltar();
        void actualizarSpriteMarioAgacharse();
        Posicion posicionManos();
        int direccionMirada();

private:
		int proximoEstado{};
		int contadorEvento{};
		int temporizadorMarioAgachado{};

		bool estaCorriendo();
		bool estaSaltando(Mario* mario, bool btnDerecho);
		bool estaAgachado(Mario* mario, bool btnDerecho);
		bool estaCambiandoDeDireccion(bool btnDerecho);

		bool estaCorriendo(Mario* mario);
		bool estaSaltando(Mario* mario);
		bool estaAgachado(Mario* mario);
		bool estaCambiandoDeDireccion(Mario* mario);

		bool controlDeFlujoSprite();
};

#endif /* SRC_APP_SPRITEMARIO_H_ */
