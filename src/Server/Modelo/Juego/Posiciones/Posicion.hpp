#ifndef SRC_SERVER_MODELO_POSICION_HPP_
#define SRC_SERVER_MODELO_POSICION_HPP_


class Posicion{

	public:
		int obtenerPosX() const{
			return (int)this->posicionX;
		}

		int obtenerPosY() const{
			return (int)this->posicionY;
		}

		virtual ~Posicion() = default;

protected:
		float posicionX{};
		float posicionY{};
		int minimoY{};

};


#endif /* SRC_SERVER_MODELO_POSICION_HPP_ */
