#ifndef TP_TALLER_DE_PROGRAMACION_FIUBA_CHISPA_HPP
#define TP_TALLER_DE_PROGRAMACION_FIUBA_CHISPA_HPP

#include "src/Server/modelo/Objetos/ObjetoFugaz.hpp"
#include "src/Server/modelo/PosicionFija.hpp"
#include "src/Server/sprites/SpriteChispa.hpp"
#include "src/Utils/Constantes.hpp"

class Chispa : public ObjetoFugaz{
    const int CICLOS_PARA_DESAPARECER = 20;
    public:
        explicit Chispa(const Posicion& posicionInicial, int direccion);
        void actualizar() override;
        efecto_t serializar() override;
        int obtenerPosicionX() override;
        bool debeDesaparecer() override;
        int tipoDeEfecto() override;
        ~Chispa() override;

        string obtenerColisionID() override;
        rectangulo_t obtenerRectangulo() override;
        bool debeColisionar() override;

    private:
        void inicializarMapasDeColision() override;
        int ciclos = 0;
        PosicionFija* posicion;
        Sprite* sprite;
};


#endif //TP_TALLER_DE_PROGRAMACION_FIUBA_CHISPA_HPP
