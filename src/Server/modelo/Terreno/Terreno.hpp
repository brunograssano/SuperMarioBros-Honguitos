#ifndef SRC_MODELO_MOVIMIENTO_TERRENO_TERRENO_H_
#define SRC_MODELO_MOVIMIENTO_TERRENO_TERRENO_H_


class Terreno {

	public:
		virtual ~Terreno(){};
		virtual float aplicarCoeficienteDeRozamiento(float velocidadX) = 0; //Declaro un método SubClassResponsibility
		virtual float obtenerImpulsoHorizontal(float aceleracion) = 0;
		virtual float obtenerImpulsoVertical(float fuerza) = 0;
        virtual float amortiguarVelocidad(float velocidadY) = 0;
};


#endif /* SRC_MODELO_MOVIMIENTO_TERRENO_TERRENO_H_ */
