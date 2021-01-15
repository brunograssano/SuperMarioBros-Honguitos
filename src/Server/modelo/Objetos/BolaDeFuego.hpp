#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_BOLADEFUEGO_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_BOLADEFUEGO_HPP

#include <src/Server/modelo/PosicionFija.hpp>
#include "src/Server/modelo/Objetos/ObjetoFugaz.hpp"
#include "src/Server/modelo/PosicionMovil.hpp"
#include "src/Server/sprites/SpriteBolaDeFuego.hpp"

class Mario;

class BolaDeFuego : public ObjetoFugaz{
    public:
        explicit BolaDeFuego(const PosicionFija& posicionInicial, int direccion, float velocidadDeInercia, Mario* marioQueDisparo);

        void actualizar() override;
        efecto_t serializar() override;
        int obtenerPosicionX() override;
        bool debeDesaparecer() override;
        ~BolaDeFuego() override;

        string obtenerColisionID() override;
        rectangulo_t obtenerRectangulo() override;
        bool debeColisionar() override;
        void chocarPorAbajoCon(Colisionable* colisionable) override;


    private:
        void inicializarMapasDeColision() override;
        PosicionMovil* posicion;
        SpriteBolaDeFuego* sprite;
        float velocidadX;
        float velocidadY;
        float efecto_gravitacional = -0.1;
        int rebotes = 0;
        bool exploto;
        Mario* marioQueDisparo;
        void empujarY(rectangulo_t rectangulo);
        void explotar(void *pVoid);
        void rebotar(void *pVoid);
        void matarEnemigo(void *pVoid);
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_BOLADEFUEGO_HPP
