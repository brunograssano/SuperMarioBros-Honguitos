#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_FLORDEFUEGO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_FLORDEFUEGO_HPP

#include "ObjetoSorpresa.hpp"

#include "src/Server/Modelo/Juego/Mario/Mario.hpp"
#include "src/Server/Modelo/Juego/Posiciones/Posicion.hpp"
#include "src/Utils/Utils.hpp"

class FlorDeFuego : public ObjetoSorpresa{

    public:
        FlorDeFuego(int posicionBloque, int altoBloque);
        void usarse(Mario* mario)override;
        efecto_t serializar() override;
        void actualizar() override;
        int obtenerPosicionX() override;
        int tipoDeEfecto() override;

        string obtenerColisionID() override;
        rectangulo_t obtenerRectangulo() override;
        bool debeColisionar() override;

        void chocarPorDerechaCon(Colisionable* colisionable) override;
        void chocarPorIzquierdaCon(Colisionable* colisionable) override;
        void chocarPorArribaCon(Colisionable* colisionable) override;
        void chocarPorAbajoCon(Colisionable* colisionable) override;

        void sonar() override;

    private:
        void inicializarMapasDeColision() override;
        Posicion posicionFija;
        uint8_t color;
        void agarrar(void* ptr = nullptr);
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_FLORDEFUEGO_HPP
