#ifndef SRC_SERVER_SPRITES_SPRITE_HPP_
#define SRC_SERVER_SPRITES_SPRITE_HPP_

class Sprite{

	public:
		virtual void actualizarSprite() = 0;
		virtual ~Sprite()= default;
        virtual int obtenerEstadoActual() {
            return estadoActual;
        }

    protected:
		int ciclos = 0;
		int estadoActual = 0;
};


#endif /* SRC_SERVER_SPRITES_SPRITE_HPP_ */
