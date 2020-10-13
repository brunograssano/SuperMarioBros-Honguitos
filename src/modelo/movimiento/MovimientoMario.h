#ifndef SRC_MODELO_MOVIMIENTO_MOVIMIENTOMARIO_H_
#define SRC_MODELO_MOVIMIENTO_MOVIMIENTOMARIO_H_


class MovimientoMario{

	public:
		MovimientoMario();
		void aceleraraDerecha();
		void aceleraraIzquierda();
		void saltar();
		float calcularDesplazamientoHorizontal(float unidadDeTiempo);
		float calcularDesplazamientoVertical(float unidadDeTiempo);
		void aplicarCoeficienteDeRozamiento();
		void aplicarGravedad();
		void actualizarVelocidad();
		void setVelocidadY(int set){
			this->velocidadY = set;
		}
	private:
		float aceleracionX;
		float aceleracionY;
		float velocidadX;
		float velocidadY;
};


#endif /* SRC_MODELO_MOVIMIENTO_MOVIMIENTOMARIO_H_ */
