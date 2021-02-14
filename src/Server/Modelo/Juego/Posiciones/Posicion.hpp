#ifndef SRC_SERVER_MODELO_POSICION_HPP_
#define SRC_SERVER_MODELO_POSICION_HPP_


class Posicion{

	public:
		int obtenerPosX() const;
		int obtenerPosY() const;
		virtual ~Posicion() = default;

    protected:
		float posicionX{};
		float posicionY{};
		int minimoY{};

};


#endif /* SRC_SERVER_MODELO_POSICION_HPP_ */
